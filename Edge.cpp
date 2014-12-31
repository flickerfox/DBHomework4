#include"Edge.h"


Edge::Edge(){}
Edge::~Edge(){}


void Edge::setId(int id)
{
	this->Id = id;
}
int Edge::getId()
{
	return this->Id;
}

void Edge::setNodeList(vector<int>nodelist)
{
	this->NodeList = nodelist;
}
vector<int> Edge::getNodeList()
{
	return this->NodeList;
}

void Edge::setTag(vector<bool>tag)
{
	this->Tag = tag;
}
vector<bool> Edge::getTag()
{
	return this->Tag;
}

void Edge::setAttribute(vector<string>attribute)
{
	this->Attribute = attribute;
}
vector<string> Edge::getAttribute()
{
	return this->Attribute;
}