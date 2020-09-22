
#include <fstream>
#include "Tree.h"

Tree::Tree(const char* filename)
{
	std::ifstream inputFile(filename, std::ifstream::in);
		
	while (inputFile.good()) {
		char* buf = new char[256];
		inputFile.getline(buf, sizeof(buf), '{');
		inputFile.getline(buf, sizeof(buf), '"');
		inputFile.getline(buf, sizeof(buf), '"');
		std::cout << buf;
		inputFile.getline(buf, sizeof(buf), '"');
		inputFile.getline(buf, sizeof(buf), '"');
		std::cout << buf;
		inputFile.getline(buf, sizeof(buf), '}');
		delete[] buf;
	}
	
	inputFile.close();
}
