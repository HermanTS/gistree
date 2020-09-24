
#include <fstream>
#include <sstream>
#include <cstring>
#include "Tree.h"

enum types
{
	INT,
	FLOAT,
	STRING,
	MAX_TYPE,
};

types ReadType(const char* str)
{
	if (!strncmp(str, "int", sizeof("int")))
		return INT;
	else if (!strncmp(str, "float", sizeof("float")))
		return FLOAT;
	else if (!strncmp(str, "string", sizeof("string")))
		return STRING;
	else
		return MAX_TYPE;
}

Tree::Tree(const char* filename)
{
	using namespace std;
	std::ifstream inputFile(filename, std::ifstream::in);
	
	string buff;
	ostringstream ss;
	ss << inputFile.rdbuf(); 
	buff = ss.str();
	
}

