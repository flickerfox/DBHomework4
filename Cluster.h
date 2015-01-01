#ifndef _CLUSTER
#define _CLUSTER

#include<iostream>
#include"Node.h"

using namespace std;

class Cluster
{
private:
	vector<Node>VertexSet;
	vector<int>Dimension;
public:
	Cluster();
	virtual ~Cluster();
	
	void setVertexSet(vector<Node>vertexSet);
	vector<Node> getVertexSet();

	void setDimension(vector<int>dimension);
	vector<int> getDimension();
};

#endif