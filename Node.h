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

template<typename T>
class Node
{
public:
	Node(Node* parent ,T& data);
	~Node();

	void addChild(Node* childNode);

	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const Node<T>& node);
private:
	T* data;
	Node* parent;
	std::vector<Node*> childs;
};

#endif // !__NODE_H_

