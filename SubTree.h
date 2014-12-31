#ifndef _SUBTREE
#define _SUBTREE

#include<iostream>
#include<vector>
#include"Node.h"

using namespace std;

class Subtree
{
private:
	vector<Node>VertexSet;
	vector<int>Dimension;
	vector<vector<Node> >CandiSet;
public:
	Subtree();
	virtual ~Subtree();

	void setVertexSet(vector<Node>vertexset);
	vec
};


#endif