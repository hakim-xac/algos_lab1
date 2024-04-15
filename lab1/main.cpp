#include "common.h"
#include "Vertexes.h"


int main()
{
	constexpr size_t c_count_vertex { 10 };

	std::string_view filename { "./data.txt" };

	LAB1::Vertexes<c_count_vertex> vertexes{ filename };

	if (vertexes.isLoad() == false)
	{
		std::cerr << "Error: can not load data from file!\n";
		return 1;
	}

	std::cout << "cost: " << vertexes.getCost() << "\n";

	vertexes.printSpanningTree();

	return 0;
}