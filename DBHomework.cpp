#include<iostream>
#include <fstream>
#include"Node.h"
#include"Edge.h"
#include "Graph.h"
#include "DBHomework.h"

Node* nodesList;
Edge* edgesList;

using namespace std;

int main()
{
	nodesList = new Node[38489];
	edgesList = new Edge[43948];

	init("C:/study/Êý¾Ý¿â¸ÅÂÛ/618506165_6_Project4/dblp/dblp-article");

	delete[] nodesList, edgesList;
}