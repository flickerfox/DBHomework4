#ifndef _GRAPH
#define _GRAPH

#include<iostream>
#include"Node.h"
#include"Edge.h"

extern Node* nodeList;
extern Edge* edgeList;

class Graph
{
private:
	vector<Node>NodeList;
	vector<Edge>EdgeList;
public:
	Graph();
	~Graph();

	void setNodeList(vector<Node>nodelist);
	vector<Node> getNodeList();

	void setEdgeList(vector<Edge>edgelist);
	vector<Edge> getEdgeList();
};



#endif