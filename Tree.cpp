
#include <fstream>
#include <sstream>
#include <cstring>
#include <exception>
#include "Tree.h"


const char* NODE_DELIMS = "{}";
const char  NODE_DELIM_START = NODE_DELIMS[0];
const char  NODE_DELIM_END = NODE_DELIMS[1];

const char DATA_DELIM = ':';

const char* TYPE_POSSIBLE_SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
const char* VALUE_POSSIBLE_SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz""1234567890.";

using namespace std;

node_types ReadType(const char* str)
{
	if (!strncmp(str, "int", sizeof("int")))
		return node_types::INT;
	else if (!strncmp(str, "float", sizeof("float")))
		return node_types::FLOAT;
	else if (!strncmp(str, "string", sizeof("string")))
		return node_types::STRING;
	else
		return node_types::MAX_TYPE;
}

size_t findEndOfNode(std::string* buff)
{
	int delim_counter = 1;
	size_t offset = 0;
	while (delim_counter)
	{
		size_t nextDelim = buff->find_first_of(NODE_DELIMS, offset + 1);
		
		if (buff->c_str()[nextDelim] == NODE_DELIM_START)
			delim_counter++;
		else
			delim_counter--;

		offset = nextDelim;
	}
	
	return offset;	
}

Node* Tree::CreateTree(Node* parent, std::string* buff)
{
	string nodeBuff(buff->c_str());

	// create node
	size_t nodePos = nodeBuff.find(NODE_DELIM_START);
	size_t dataDelimPos = nodeBuff.find(DATA_DELIM, nodePos);

	size_t valueTypePos = nodeBuff.find_first_of(TYPE_POSSIBLE_SYMBOLS, nodePos);
	size_t valueTypeStrLen = nodeBuff.find_first_not_of(TYPE_POSSIBLE_SYMBOLS, valueTypePos) - valueTypePos;

	size_t valuePos = nodeBuff.find_first_of(VALUE_POSSIBLE_SYMBOLS, dataDelimPos);
	size_t valueStrLen = nodeBuff.find_first_not_of(VALUE_POSSIBLE_SYMBOLS, valuePos) - valuePos;

	string valueType = nodeBuff.substr(valueTypePos, valueTypeStrLen);
	string value = nodeBuff.substr(valuePos, valueStrLen);

	Node* node;
	node_types nodeType = ReadType(valueType.c_str());
	switch (nodeType)
	{
		case node_types::INT:
		{
			int iValue = stoi(value.c_str());
			node = new Node(parent, &iValue, nodeType);
			break;
		}
		case node_types::FLOAT:
		{
			float fValue = stof(value.c_str());
			node = new Node(parent, &fValue, nodeType);
			break;
		}
		case node_types::STRING:
		{
			node = new Node(parent, &value, nodeType);
			break;
		}
		default:
			node = new Node(parent, &value, nodeType);
			break;
	}


	// find end of node or childs
	size_t delim_counter = 1;
	size_t offset = nodePos;
		
	while (delim_counter)
	{
		size_t nextDelim = nodeBuff.find_first_of(NODE_DELIMS, offset + 1);

		if (nodeBuff.c_str()[nextDelim] == NODE_DELIM_START)
		{
			delim_counter++;
			string childBuff = nodeBuff.substr(nextDelim, nodeBuff.size());
			node->addChild(CreateTree(node, &childBuff));

			offset = nextDelim + findEndOfNode(&childBuff);
		}
		else
		{
			delim_counter--;
		}		
	}
	
	return node;
}

void Tree::Serializetion(std::ostream* out, Node* root)
{
	auto& outstream = *out;
	static int tabs_counter = 0;
	tabs_counter++;

	string spases;

	for (int i = 1; i < tabs_counter; i++)
		spases += "    ";

	outstream << spases << "{" << endl;


	outstream << spases <<"\"" << root->getTypeStr() << "\" : \"" << *root << "\"" << endl;

	for (auto it : root->getChilds())
		Serializetion(out, it);

	outstream << spases << "}" << endl;
	tabs_counter--;
}

void Tree::Print(std::ostream* out, Node* root)
{
	auto& outstream = *out;
	static int tabs_counter = 0;
	tabs_counter++;

	string spases;

	for (int i = 1; i < tabs_counter; i++)
		spases += (tabs_counter - i) > 1? "|" : "└";


	outstream << spases << *root <<  endl;

	for (auto it : root->getChilds())
		Print(out, it);

	tabs_counter--;
}

Tree::Tree(const char* filename)
{
	std::ifstream inputFile(filename, std::ifstream::in);

	string buff;
	ostringstream ss;
	ss << inputFile.rdbuf();
	buff = ss.str();

	root = CreateTree(nullptr, &buff);
}



std::ostream& operator<<(std::ostream& out, const Tree& tree)
{
	tree.Print(&out, tree.root);
	
	return out;
}

std::fstream& operator<<(std::fstream& file, const Tree& tree)
{
	tree.Serializetion(&file, tree.root);
	
	return file;
}
