#include"Edge.h"


Edge::Edge()
{
	this->NodeList = new vector<int>;
	this->Tag = new vector<bool>;
	this->Attribute = new vector<string>;
}
Edge::~Edge()
{
	delete this->NodeList;
	delete this->Tag;
	delete this->Attribute;
}


void Edge::setPubName(string pubname)
{
	this->pubName = pubname;
}

string Edge::getPubName()
{
	return this->pubName;
}

void Edge::setId(int id)
{
	this->Id = id;
}
int Edge::getId()
{
	return this->Id;
}

void Edge::setDe(int d)
{
	this->dimension = d;
}
void Edge::increaseDe(int d)
{
	this->dimension += d;
}
int Edge::getDe()
{
	return this->dimension;
}

void Edge::setNodeList(vector<int>* nodelist)
{
	this->NodeList = nodelist;
}
vector<int>* Edge::getNodeList()
{
	return this->NodeList;
}

void Edge::setTag(vector<bool>* tag)
{
	this->Tag = tag;
}
vector<bool>* Edge::getTag()
{
	return this->Tag;
}

void Edge::setAttribute(vector<string>* attribute)
{
	this->Attribute = attribute;
}
vector<string>* Edge::getAttribute()
{
	return this->Attribute;
}