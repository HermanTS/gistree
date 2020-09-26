/*
 * Node.h
 *
 *  Created on: 22.09.2020
 *      Author: gstsvetkov
 */

#ifndef __NODE_H_
#define __NODE_H_

#include <vector>
#include <iostream>

enum node_types
{
	INT,
	FLOAT,
	STRING,
	MAX_TYPE,
};

class Node
{
public:
	Node(Node* parent , void* data, node_types type);
	~Node();


	void addChild(Node* childNode);

	friend std::ostream& operator<<(std::ostream& out, const Node& node);

private:
	Node* parent;
	std::vector<Node*> childs;

	void* data;
	node_types type;

};

#endif // !__NODE_H_

