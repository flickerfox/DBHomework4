#include "Node.h"

Node::Node()
{
	this->Degree = new int[2];
	this->Degree[0] = Degree[1] = 0;
	this->AdjList = new vector<int>;
	this->EdgeList = new vector<int>;
}

Node::~Node()
{
	delete AdjList;
	delete EdgeList;
}


void Node::setId(int id)
{
	this->Id=id;
}

int Node::getId()
{
	return this->Id;
}
void Node::setDegree(int* degree)
{
	this->Degree = degree;
}
int* Node::getDegree()
{
	return this->Degree;
}

void Node::increaseDegree(int inc)
{
	this->Degree[0] += inc;
	this->Degree[1] += inc;
}

void Node::setAuthorName(string authorname)
{
	this->AuthorName = authorname;
}

string Node::getAuthorName()
{
	return this->AuthorName;
}

void Node:: setAdjList(vector<int>* adjlist)
{
	this->AdjList = adjlist;
}
vector<int>* Node::getAdjList()
{
	return this->AdjList;
}

void Node::setEdgeList(vector<int>* edgelist)
{
	this->EdgeList = edgelist;
}
vector<int>* Node::getEdgeList()
{
	return this->EdgeList;
}
