/*
 * Node.cpp
 *
 *  Created on: 22.09.2020
 *      Author: gstsvetkov
 */

#include "Node.h"

Node::Node(Node* parent, void* data, node_types type) :
parent(parent), type(type)
{
	switch (type)
	{
	case INT:
		this->data = new int(*static_cast<int*>(data));
		break;
	case FLOAT:
		this->data = new float(*static_cast<float*>(data));
		break;
	case STRING:
		this->data = new std::string(*static_cast<std::string*>(data));
		break;
	default:
		break;
	}
}

Node::~Node()
{
	delete data;

	for (auto it : childs)
	{
		delete it;
	}
}


void Node::addChild(Node* childNode)
{
	childs.push_back(childNode);
}

const std::vector<Node*>& Node::getChilds()
{
	return childs;
}

std::ostream& operator<<(std::ostream& out, const Node& node)
{
		
	switch (node.type)
	{
	case INT:
		out << (*static_cast<int*>(node.data));
		break;
	case FLOAT:
		out << (*static_cast<float*>(node.data));
		break;
	case STRING:
		out << (*static_cast<std::string*>(node.data));
		break;
	default:
		return out;
		break;
	}
				
	return out;
}
