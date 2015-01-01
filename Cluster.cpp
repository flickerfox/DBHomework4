#include"Cluster.h"

Cluster::Cluster(){}
Cluster::~Cluster(){}

void Cluster::setVertexSet(vector<Node>vertexSet)
{
	this->VertexSet = vertexSet;
}

vector<Node> Cluster::getVertexSet()
{
	return this->VertexSet;
}

void Cluster::setDimension(vector<int>dimension)
{
	this->Dimension = dimension;
}
vector<int> Cluster::getDimension()
{
	return this->Dimension;
}