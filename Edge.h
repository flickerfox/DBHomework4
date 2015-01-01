#ifndef _EDGE
#define _EDGE

#include<iostream>
#include<vector>
#include "Node.h"
using namespace std;

class Edge
{
private:
	int Id;
	vector<int>NodeList;
	vector<bool>Tag;
	vector<string>Attribute;
public:
	Edge();
	virtual ~Edge();

	void setId(int id);
	int getId();

	void setNodeList(vector<int>nodelist);
	vector<int> getNodeList();

	void setTag(vector<bool>tag);
	vector<bool> getTag();

	void setAttribute(vector<string>attribute);
	vector<string> getAttribute();
};

#endif
