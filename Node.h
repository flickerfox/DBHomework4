#ifndef _NODE
#define _NODE

#include <iostream>
#include <vector>
#include "Edge.h"

using namespace std;

class Node
{
private:
	int Id;
	int Degree;
	string AuthorName;
	vector<int>AdjList;
	vector<int>EdgeList;
public:
	Node();
	virtual ~Node();

	void setId(int id);
	int getId();

	void setDegree(int degree);
	int getDegree();

	void setAuthorName(string authorname);
	string getAuthorName();

	void setAdjList(vector<int>adjlist);
	vector<int>getAdjList();

	void setEdgeList(vector<int>edgelist);
	vector<int>getEdgeList();
};
#endif