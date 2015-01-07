#include "SubTree.h"


SubTree::SubTree()
{
	this->VertexSet=new vector<int>;
	this->Dimension=new vector<int>;
	this->CandiSet=new vector<vector<int> >;
}
SubTree::~SubTree()
{
	delete this->VertexSet;
	delete this->Dimension;
	delete this->CandiSet;
}

void SubTree::setVertexSet(vector<int>* vertexset)
{
	this->VertexSet = vertexset;
}

vector<int>* SubTree::getVertexSet()
{
	return this->VertexSet;
}

void SubTree::setDimension(vector<int>* dimension)
{
	this->Dimension = dimension;
}

vector<int>* SubTree::getDimension()
{
	return this->Dimension;
}

void SubTree::setCandiSet(vector<vector<int> >* candiset)
{
	this->CandiSet = candiset;
}
vector<vector<int> >* SubTree::getCandiSet()
{
	return this->CandiSet;
}