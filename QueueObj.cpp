#include"QueueObj.h"

using namespace std;


Queueobj::Queueobj()
{
	//if (this->type == 0)
		this->subtree = new SubTree;
	//if (this->type == 1)
		this->cluster = new Cluster;
}

Queueobj::~Queueobj()
{
	//if (this->type == 0)
		delete this->subtree;
	//if (this->type == 1)
		delete this->cluster;
}

void Queueobj::setSubtree(SubTree* subtree)
{
	this->subtree = subtree;
	this->cluster = NULL;
}

SubTree* Queueobj::getSubtree()
{
	return this->subtree;
}

void Queueobj::setCluster(Cluster* cluster)
{
	this->cluster = cluster;
	this->subtree = NULL;
}

Cluster* Queueobj::getCluster()
{
	return this->cluster;
}

void Queueobj::setType(int type)
{
	this->type = type;
}
int Queueobj::getType()
{
	return this->type;
}
double Queueobj::getQuality()
{
	if (this->getType() == 0)
		return this->getSubtree()->getQuality();
	else
		return this->getCluster()->getQuality();
}