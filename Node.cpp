#include "Node.h"

Node::Node()
{
	this->Degree = new vector<int>;
	for (int i = 0; i < 2;i++)
		this->Degree->push_back(0);
	this->AdjList = new vector<int>;
	this->EdgeList = new vector<int>;
}

Node::~Node()
{
	delete Degree;
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
void Node::setDegree(vector<int>* degree)
{
	this->Degree = degree;
}
vector<int>* Node::getDegree()
{
	return this->Degree;
}

void Node::increaseDegree(int inc,int demension)
{
	
	this->Degree->at(demension) += inc;
	//this->Degree->at(1) += inc;
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
