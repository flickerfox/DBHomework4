#ifndef _EDGE
#define _EDGE

#include<iostream>
#include<vector>

using namespace std;

class Edge
{
private:
	int Id;
	string pubName;
	int dimension;
	vector<int>* NodeList;
	vector<bool>* Tag;
	vector<string>* Attribute;
public:
	Edge();
	virtual ~Edge();

	void setPubName(string pubname);
	string getPubName();
	void setId(int id);
	int getId();
	void setDe(int d);
	int getDe();
	void increaseDe(int d);

	void setNodeList(vector<int>* nodelist);
	vector<int>* getNodeList();

	void setTag(vector<bool>* tag);
	vector<bool>* getTag();

	void setAttribute(vector<string>* attribute);
	vector<string>* getAttribute();
};

#endif
