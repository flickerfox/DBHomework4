#include"Graph.h"

Graph::Graph(){}
Graph::~Graph(){};

void Graph::setNodeList(vector<Node>nodelist)
{
	this->NodeList = nodelist;
}
vector<Node> Graph::getNodeList()
{
	return this->NodeList;
}

void Graph::setEdgeList(vector<Edge>edgelist)
{
	this->EdgeList = edgelist;
}
vector<Edge> Graph::getEdgeList()
{
	return this->EdgeList;
}