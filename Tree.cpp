
#include <fstream>
#include <sstream>
#include <cstring>
#include "Tree.h"


const char* NODE_DELIMS = "{}";
const char  NODE_DELIM_START = NODE_DELIMS[0];
const char  NODE_DELIM_END = NODE_DELIMS[1];

const char DATA_DELIM = ':';

const char* TYPE_POSSIBLE_SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
const char* VALUE_POSSIBLE_SYMBOLS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz""1234567890";

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

Node* Tree::CreateTree(Node* parent, std::string* buff)
{
	using namespace std;
	size_t nodePos = buff->find(NODE_DELIM_START);
	size_t dataDelimPos = buff->find(DATA_DELIM, nodePos);

	size_t valueTypePos = buff->find_first_of(TYPE_POSSIBLE_SYMBOLS, nodePos);
	size_t valueTypeStrLen = buff->find_first_not_of(TYPE_POSSIBLE_SYMBOLS, valueTypePos) - valueTypePos;

	size_t valuePos = buff->find_first_of(VALUE_POSSIBLE_SYMBOLS, dataDelimPos);
	size_t valueStrLen = buff->find_first_not_of(VALUE_POSSIBLE_SYMBOLS, valuePos) - valuePos;

	string valueType = buff->substr(valueTypePos, valueTypeStrLen);
	string value = buff->substr(valuePos, valueStrLen);

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
			float fValue = stod(value.c_str());
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

	cout << (*node) << endl;

	size_t offset = buff->find(NODE_DELIM_START) + 1;
	size_t nextDelim;
	static size_t delim_counter = 1;

	while (delim_counter)
	{
		nextDelim = buff->find_first_of(NODE_DELIMS, offset);
		offset = nextDelim + 1;

		if (buff->c_str()[nextDelim] == NODE_DELIM_START)
		{
			string childBuff = buff->substr(nextDelim, buff->size());
			delim_counter++;
			node->addChild(CreateTree(node, &childBuff));
			
		} 
		else
		{
			delim_counter--;
		}
	} 

	return node;
}

Tree::Tree(const char* filename)
{
	using namespace std;
	std::ifstream inputFile(filename, std::ifstream::in);

	string buff;
	ostringstream ss;
	ss << inputFile.rdbuf();
	buff = ss.str();

	CreateTree(nullptr, &buff);
}



