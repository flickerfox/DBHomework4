#ifndef _QUEUEOBJ
#define _QUQUEOBJ

#include<iostream>
#include"SubTree.h"
#include"Cluster.h"

using namespace std;

class Queueobj
{
private:
	SubTree* subtree;
	Cluster* cluster;
	int type;//0ÊÇsubtree£¬1ÊÇcluster
public :
	Queueobj();
	virtual ~Queueobj();

	void setSubtree(SubTree* subtree);
	SubTree* getSubtree();
	void setCluster(Cluster* cluster);
	Cluster* getCluster();
	void setType(int type);
	int getType();

	double getQuality();
};


#endif