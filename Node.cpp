#include "Node.h"

Node::Node(){}
Node::~Node(){}


void Node::setId(int id)
{
	this->Id=id;
}

int Node::getId()
{
	return this->Id;
}
void Node::setDegree(int degree)
{
	this->Degree = degree;
}
int Node::getDegree()
{
	return this->Degree;
}

void Node::setAuthorName(string authorname)
{
	this->AuthorName = authorname;
}

string Node::getAuthorName()
{
	return this->AuthorName;
}

void Node:: setAdjList(vector<int>adjlist)
{
	this->AdjList = adjlist;
}
vector<int> Node::getAdjList()
{
	return this->AdjList;
}

void Node::setEdgeList(vector<int>edgelist)
{
	this->EdgeList = edgelist;
}
vector<int>Node::getEdgeList()
{
	return this->EdgeList;
}
