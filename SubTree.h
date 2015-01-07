#ifndef _SUBTREE
#define _SUBTREE

#include<iostream>
#include<vector>


using namespace std;

class SubTree
{
private:
	vector<int>* VertexSet;
	vector<int>* Dimension;
	vector<vector<int> >* CandiSet;
public:
	SubTree();
	virtual ~SubTree();

	void setVertexSet(vector<int>* vertexset);
	vector<int>* getVertexSet();

	void setDimension(vector<int>* dimension);
	vector<int>* getDimension();

	void setCandiSet(vector<vector<int> >* candiset);
	vector<vector<int> >* getCandiSet();

};


#endif