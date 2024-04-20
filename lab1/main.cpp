#include "common.h"
#include "Vertexes.h"


int main()
{
	constexpr size_t c_count_vertex { 10 };

	std::string_view filename { "./data.txt" };

	LAB1::Vertexes<c_count_vertex> vertexes{ filename };

	vertexes.printHeader();
	vertexes.printSpanningTree();

	[[maybe_unused]] int c{ getchar() };

	return 0;
}