#ifndef _CLUSTER
#define _CLUSTER

#include<iostream>
#include"Node.h"

using namespace std;

class Cluster
{
private:
	vector<int>* VertexSet;
	vector<int>* Dimension;
	double Quality;
public:
	Cluster();
	virtual ~Cluster();
	
	void setVertexSet(vector<int>* vertexSet);
	vector<int>* getVertexSet();

	void setDimension(vector<int>* dimension);
	vector<int>* getDimension();

	void setQuality(double quality);
	double getQuality();
};

#endif