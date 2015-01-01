#include<iostream>
#include <fstream>
#include"Node.h"
#include"Edge.h"
#include "Graph.h"
#include "DBHomework.h"

Node** nodesList;
Edge** edgesList;

using namespace std;

void releaseMemory()
{
	for (int i = 0;i<779752;i++)
	{
		if (nodesList[i] != NULL)
		{
			delete nodesList[i];
		}
	}
	for (int i = 0;i<1050479;i++)
	{
		if (edgesList[i] != NULL)
		{
			delete edgesList[i];
		}
	}
	delete[] nodesList, edgesList;
}

int main()
{
	string path = "C:/programs/db4/dbhomework/";
	init();
	readAuthorFromFile(path);
	readPubFromFile(path);
	readRelationFromFile(path);

	releaseMemory();
}