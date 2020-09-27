/*
 * Tree.h
 *
 *  Created on: 22.09.2020
 *      Author: gstsvetkov
 */

#ifndef __TREE_H_
#define __TREE_H_

#include <iostream>
#include "Node.h"

class Tree
{
public:
	Tree(const char* filename);
	

	friend std::ostream& operator<<(std::ostream& out, const Tree& node);
	friend std::fstream& operator<<(std::fstream& file, const Tree& node);
private:
	Node* CreateTree(Node* parent, std::string* buff);
	static void Serializetion(std::ostream* out, Node* root);
	static void Print(std::ostream* out, Node* root);

	Node* root;
};

#endif

