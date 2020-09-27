/*
 * main.c
 *
 *  Created on: 22.09.2020
 *      Author: gstsvetkov
 */

#include <iostream>
#include <cstring>

#include "Tree.h"

enum 
{
	INPUT_FILE,
	OUTPUT_FILE,
	NONE
};

const std::string USAGE = "usage: \ngistree -i filename -o filename\n";

int parceArg(char* argv)
{
	if (!strncmp(argv, "-i", sizeof("-i")))
		return INPUT_FILE;
	else if (!strncmp(argv, "-o", sizeof("-o")))
		return OUTPUT_FILE;
	else
		return -1;
}

int main(int argc, char** argv) 
{
	int rez = 0;

	std::string* inputFileName = nullptr;
	std::string* outFileName = nullptr;
	
	if (argc < 5)
		std::cout << "too few arguments" << std::endl << USAGE.c_str();
	else if (argc > 5)
		std::cout << "too many arguments" << std::endl << USAGE.c_str();

	for (int i = 1; i < argc; i+=2)
	{
		switch (parceArg(argv[i]))
		{
		case INPUT_FILE:
			inputFileName = new std::string(argv[i + 1]);
			break;
		case OUTPUT_FILE:
			outFileName = new std::string(argv[i + 1]);
			break;
		default:
			std::cout << "No valid input data" << std::endl;
			std::cout << USAGE.c_str();
			return 0;
			break;
		}
	}

	Tree tree(inputFileName->c_str());

	std::cout << tree;

	return rez;
}

