#ifndef _SUBTREE
#define _SUBTREE

#include<iostream>
#include<vector>
#include"Node.h"

using namespace std;

class SubTree
{
private:
	vector<Node>VertexSet;
	vector<int>Dimension;
	vector<vector<Node> >CandiSet;
public:
	SubTree();
	virtual ~SubTree();

	void setVertexSet(vector<Node>vertexset);
	vector<Node> getVertexSet();

	void setDimension(vector<int>dimension);
	vector<int> getDimension();

	void setCandiSet(vector<vector<Node> >candiset);
	vector<vector<Node> > getCandiSet();

};


#endif