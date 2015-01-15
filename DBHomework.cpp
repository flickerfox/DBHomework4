#include<iostream>
#include <fstream>
#include<sstream>
#include<algorithm>
#include"Node.h"
#include"Edge.h"
#include "Graph.h"
#include "DBHomework.h"

Node** nodesList;
Edge** edgesList;
int edgeNum = 1050479;
int nodeNum = 779752;

int minnumNode = 2;
int minDimension = 1;
double minDensity=0.01;
int minsimilarity = 14;
double minRedundancy=0.5;

using namespace std;

void releaseMemory()
{
	for (int i = 0;i<nodeNum;i++)
	{
		if (nodesList[i] != NULL)
		{
			delete nodesList[i];
		}
	}
	for (int i = 0;i<edgeNum;i++)
	{
		if (edgesList[i] != NULL)
		{
			delete edgesList[i];
		}
	}
	delete[] nodesList, edgesList;
}

//bool pr(double s1, double s2)
//{
//	return s1 > s2;
//}
vector<int>* vectorUnio(vector<int> v1, vector<int> v2)//求并集  
{
	int i, j;
	i = j = 0;//定位到2个有序向量的头部  

	vector<int>* des=new vector<int>;
	//必有一个向量插入完成  
	if (v1.empty())
		des->assign(v2.begin(), v2.end());
	if (v2.empty())
		des->assign(v1.begin(), v1.end());
	else
	{
		while (i < v1.size() && j < v2.size())
		{
			if (v1[i] == v2[j])
			{
				//if (!ifDegreeZero(v1[i]))
				des->push_back(v1[i]);//相等则只压入容器一次，标记均后移一个位置，避免元素重复  
				i += 1;
				j += 1;
			}
			else if (v1[i] < v2[j])//不相等则压入较小元素，标记后移一个位置  
			{
				//if (!ifDegreeZero(v1[i]))
				des->push_back(v1[i]);
				i += 1;
			}
			else
			{
				//if (!ifDegreeZero(v1[i]))
				des->push_back(v2[j]);
				j += 1;
			}
		}
		while (i < v1.size())
		{
			des->push_back(v1[i]);
			i++;
		}
		while (j < v2.size())
		{
			des->push_back(v2[j]);
			j++;
		}
	}
	return des;
}
int main()
{
	//vector<int>a = test();
	string path = "C:/WBY/Study/数据库概论/数据集1/";
	//string path = "C:/WBY/Study/数据库概论/测试集/";
	init();
	readAuthorFromFile(path);
	readPubFromFile(path);
	readRelationFromFile(path);
	vector<Cluster>*result=new vector<Cluster>();	
	result=MiMAG(nodesList, edgesList);

//
	cout << result->size() << endl;
	
	/*vector<int> v;
	
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(6);
	
	vector<int> v2;
	
	v2.push_back(1);
	v2.push_back(4);
	v2.push_back(5);
	vector<int>*v3=new vector<int>;
	v3 = vectorUnio(v, v2);
	
	for (int i = 0; i < v3->size(); i++)
	{
		cout << (*v3)[i] << endl;
	}
	*/

	//for (int i = 0; i < v.size(); i++)
	//{
	//	cout << v[i] << endl;
	//}
	//vector<int>copy;
	//copy.assign(v.begin(), v.end());
	//for (int i = 0; i < copy.size(); i++)
	//{
	//	cout << copy[i] << endl;
	//}
	//cout << copy.capacity() << endl;
	releaseMemory();

}