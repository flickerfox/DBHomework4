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

vector<int> test()
{
	vector<int>*my=new vector<int>;
	(*my).push_back(1);
	return *my;
}
int main()
{
	//vector<int>a = test();
	string path = "C:/WBY/Study/数据库概论/数据集1/";
	init();
	readAuthorFromFile(path);
	readPubFromFile(path);
	readRelationFromFile(path);
	vector<Cluster>*result=new vector<Cluster>();
	result=MiMAG(nodesList, edgesList);

	//vector<int> v;
	//v.push_back(1);
	//v.push_back(2);
	//v.push_back(3);
	//v.push_back(4);
	//vector<int>::iterator itr = v.begin();
	//while (itr != v.end())
	//{
	//	if (*itr == 1)
	//	{
	//		itr = v.erase(itr);
	//	}
	//	else
	//		itr++;//这里迭代器会更新出错
	//}

	//for (int i = 0; i < v.size(); i++)
	//{
	//	cout << v[i] << endl;
	//}
	//cout << v.capacity() << endl;
	releaseMemory();

}