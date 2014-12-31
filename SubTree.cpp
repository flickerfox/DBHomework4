#include "SubTree.h"


SubTree::SubTree(){}
SubTree::~SubTree(){}

void SubTree::setVertexSet(vector<Node>vertexset)
{
	this->VertexSet = vertexset;
}

vector<Node> SubTree::getVertexSet()
{
	return this->VertexSet;
}

void SubTree::setDimension(vector<int>dimension)
{
	this->Dimension = dimension;
}

vector<int> SubTree::getDimension()
{
	return this->Dimension;
}

void SubTree::setCandiSet(vector<vector<Node> >candiset)
{
	this->CandiSet = candiset;
}
vector<vector<Node> > SubTree::getCandiSet()
{
	return this->CandiSet;
}