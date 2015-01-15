#include"Cluster.h"

Cluster::Cluster()
{
	this->VertexSet = new vector<int>;
	this->Dimension = new vector<int>;
}
Cluster::~Cluster()
{
	delete VertexSet;
	delete Dimension;
}

void Cluster::setVertexSet(vector<int>* vertexSet)
{
	this->VertexSet = vertexSet;
}

vector<int>* Cluster::getVertexSet()
{
	return this->VertexSet;
}

void Cluster::setDimension(vector<int>* dimension)
{
	this->Dimension = dimension;
}
vector<int>* Cluster::getDimension()
{
	return this->Dimension;
}
void Cluster::setQuality(double quality)
{
	this->Quality = quality;
}
double Cluster::getQuality()
{
	return this->Quality;
}