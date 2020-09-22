/*
 * Node.cpp
 *
 *  Created on: 22.09.2020
 *      Author: gstsvetkov
 */

#include "Node.h"


template<typename T>
Node<T>::Node(Node* parent, T& data):
parent(parent)
{
	this->data = new T(data);
}

template<typename T>
Node<T>::~Node()
{
	delete data;

	for (auto it : childs)
	{
		delete it;
	}
}

template<typename T>
void Node<T>::addChild(Node* childNode)
{
	childs.push_back(childNode);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& node)
{
	out << node.data << std::endl;
	return out;
}
