#ifndef __LAB1_KHAS_ALGOS
#define __LAB1_KHAS_ALGOS

#include "common.h"

namespace LAB1 {

	struct Edge {
		std::array<size_t, 2> vertex;
		size_t weight;
		friend bool operator < (const Edge& lhs, const Edge& rhs);
		friend std::ostream& operator << (std::ostream& out, const Edge& edge);
	};

	template <size_t COUNT_VERTEX>
	class Vertexes
	{

	public:

		constexpr Vertexes(std::string_view filename) noexcept;

		//-------------------------

		[[nodiscard]] size_t getCost() const noexcept;

		//-------------------------

		void printSpanningTree() const noexcept;

		//-------------------------

		[[nodiscard]] size_t isLoad() const noexcept;

		//-------------------------

	private: // functions

		[[nodiscard]] size_t findSet(size_t value);

		//-------------------------

		void calculateSpanningTree();

		//-------------------------

		void unionSets(size_t lhs, size_t rhs);

		//-------------------------

		[[nodiscard]] std::set<Edge> loadEdgeToSet();

		//-------------------------

	private: // fields

		std::array<size_t, COUNT_VERTEX> _parent{};
		std::array<size_t, COUNT_VERTEX> _rank{};
		size_t							 _cost{};
		bool							 _is_load{};
		std::string_view				 _filename{};
		std::vector<Edge>				 _spanning_tree{};
		std::set<Edge>					 _data_set{};
	};
}

//===========================

namespace LAB1
{
	//---------------------------------------------------

	inline bool operator < (const Edge& lhs, const Edge& rhs)
	{
		return lhs.weight < rhs.weight;
	}

	//---------------------------------------------------

	inline std::ostream& operator << (std::ostream& out, const Edge& edge)
	{
		out << "Vertexes2: [ " << edge.vertex[0] << ", " << edge.vertex[1] << " ]\n";
		out << "weight: " << edge.weight << "\n";
		out << "-------------\n";
		return out;
	}

	//---------------------------------------------------
	//---------------------------------------------------

	template <size_t COUNT_VERTEX>
	constexpr
		Vertexes<COUNT_VERTEX>::Vertexes(std::string_view filename) noexcept
		: _parent{ COUNT_VERTEX }
		, _rank{ COUNT_VERTEX }
		, _cost{ 0 }
		, _filename{ filename }
		, _spanning_tree{ }
	{
		std::iota(std::begin(_parent), std::end(_parent), size_t{});
		std::fill(std::begin(_rank), std::end(_rank), size_t{});
		_data_set = loadEdgeToSet();

		if (_is_load)
			calculateSpanningTree();
	}

	//---------------------------------------------------

	template <size_t COUNT_VERTEX>
	[[nodiscard]]
	size_t
		Vertexes<COUNT_VERTEX>::getCost() const noexcept
	{
		return _cost;
	}

	//---------------------------------------------------

	template <size_t COUNT_VERTEX>
	void Vertexes<COUNT_VERTEX>::printSpanningTree() const noexcept
	{
		std::cout << "print spanning tree:\n";
		for (auto&& elem : _spanning_tree)
		{
			std::cout << elem;
		}
	}

	//---------------------------------------------------

	template <size_t COUNT_VERTEX>
	[[nodiscard]]
	size_t
		Vertexes<COUNT_VERTEX>::isLoad() const noexcept
	{
		return _is_load;
	}

	//---------------------------------------------------

	template <size_t COUNT_VERTEX>
	[[nodiscard]]
	size_t
		Vertexes<COUNT_VERTEX>::findSet(size_t value)
	{
		if (value == _parent[value])
			return value;

		return _parent[value] = findSet(_parent[value]);
	}

	//---------------------------------------------------


	template <size_t COUNT_VERTEX>
	void Vertexes<COUNT_VERTEX>::calculateSpanningTree()
	{
		for (auto&& elem : _data_set)
		{
			if (findSet(elem.vertex[0]) != findSet(elem.vertex[1]))
			{
				_cost += elem.weight;
				_spanning_tree.emplace_back(elem);
				unionSets(elem.vertex[0], elem.vertex[1]);
			}
		}
	}

	//---------------------------------------------------


	template <size_t COUNT_VERTEX>
	void Vertexes<COUNT_VERTEX>::unionSets(size_t lhs, size_t rhs) {
		lhs = findSet(lhs);
		rhs = findSet(rhs);
		if (lhs != rhs) {
			if (_rank[lhs] < _rank[rhs])
				std::swap(lhs, rhs);

			_parent[rhs] = lhs;

			if (_rank[lhs] == _rank[rhs])
				++_rank[lhs];
		}
	}

	//---------------------------------------------------

	template <size_t COUNT_VERTEX>
	[[nodiscard]]
	std::set<Edge>
		Vertexes<COUNT_VERTEX>::loadEdgeToSet()
	{
		std::ifstream data_from_file{ _filename.data() };
		if (data_from_file.is_open() == false)
		{
			std::cerr << "Error: can not open the data file!\n";
			return {};
		}

		std::set<Edge> data_set;

		for (size_t i{ 0 }; i < COUNT_VERTEX; ++i)
		{
			for (size_t j{ }, skeep{ i + 1 }; j < skeep; ++j)
			{
				int32_t tmp{};
				data_from_file >> tmp;
			}

			for (size_t j{ i + 1 }; j < COUNT_VERTEX; ++j)
			{
				size_t tmp{};
				data_from_file >> tmp;

				data_set.emplace(Edge{
					.vertex = { i, j },
					.weight = tmp
					});
			}
		}

		_is_load = true;

		return data_set;
	}

	//---------------------------------------------------
}

#endif