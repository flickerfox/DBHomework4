#include<iostream>
#include <fstream>
#include"Node.h"
#include"Edge.h"
#include "DBHomework.h"

using namespace std;

extern Node* nodeList;
extern Edge* edgeList;

int main()
{
	nodeList = new Node[38489];
	edgeList = new Edge[43948];

	init("C:/study/Êý¾Ý¿â¸ÅÂÛ/618506165_6_Project4/dblp/dblp-article");

	delete[] nodeList, edgeList;
}