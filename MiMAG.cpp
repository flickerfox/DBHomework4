#include<iostream>
#include<algorithm>
#include"Edge.h"
#include"Node.h"
#include"SubTree.h"
#include"Graph.h"
#include"Cluster.h"

using namespace std;

int graphDimension(Edge** edgelist)
{
	for (int i = 0; i < 200; i++)
	{
		if (edgelist[i] != NULL)
		{
			return edgelist[i]->getDe();
		}
	}
	return 0;
}

bool ifDegreeZero(int i)
{
	int* degree =nodesList[i]->getDegree();
	if (degree[0] == 0 && degree[1] == 0)
		return false;
	else
		return false;
}

SubTree* initSubTree(Node **nodelist, Edge **edgelist)
{
	SubTree *subtree=new SubTree();
	int GDimension = graphDimension(edgelist);

	for (int i = 0; i < GDimension; i++)
	{
		subtree->getDimension()->push_back(i);
	}

	vector<vector<int> >* cand = new vector<vector<int> >();
	vector<int>* cand0=new vector<int>();
	for (int i = 0; i < 779752; i++)
	{
		if (nodelist[i] != NULL)
		{
			cand0->push_back(nodelist[i]->getId());
		}
	}
	for (int i = 0; i < GDimension; i++)
	{
		vector<int>* candi=new vector<int>();
		candi->assign(cand0->begin(), cand0->end());
		cand->push_back(*candi);
	}
	subtree->setCandiSet(cand);

	return subtree;


}

vector<int>* vectorUnion(vector<int> v1, vector<int> v2, vector<int>* des)//�󲢼�  
{
	int i, j;
	i = j = 0;//��λ��2������������ͷ��  

	des->clear();
	//����һ�������������  
	if (v1.empty())
		des->assign(v2.begin(), v2.end());
	if (v2.empty())
		des->assign(v1.begin(),v1.end());
	else
	{
		while (i < v1.size() && j < v2.size())
		{
			if (v1[i] == v2[j])
			{
				if (!ifDegreeZero(v1[i]))
					des->push_back(v1[i]);//�����ֻѹ������һ�Σ���Ǿ�����һ��λ�ã�����Ԫ���ظ�  
				i += 1;
				j += 1;
			}
			else if (v1[i] < v2[j])//�������ѹ���СԪ�أ���Ǻ���һ��λ��  
			{
				if (!ifDegreeZero(v1[i]))
					des->push_back(v1[i]);
				i += 1;
			}
			else
			{
				if (!ifDegreeZero(v1[i]))
					des->push_back(v2[j]);
				j += 1;
			}
		}
	}
	return des;
}

vector<int>* stNeighbour(SubTree* subtree)
{
	vector<int> *resultneighbour = new vector<int>();
	cout << "Find Neighbour...." << endl;	
	vector<int> *temp = new vector<int>();
	for (int i = 0; i < subtree->getCandiSet()->size(); i++)
	{
		temp=vectorUnion(subtree->getCandiSet()->at(i), *temp, resultneighbour);
	}
	cout << resultneighbour->size() << endl;

	return resultneighbour;
}

int findU(vector<int>* neighbour,SubTree* subtree)
{
	int max = 0;
	for (int i = 0; i < neighbour->size(); i++)
	{

	}
	return max;
}

vector<Cluster>* MiMAG(Node **nodelist, Edge **edgelist)
{
	vector<Cluster>* ResultCluster=new vector<Cluster>();
	SubTree *RootSTree=new SubTree();
	RootSTree = initSubTree(nodelist, edgelist);

	SubTree *NextSTree = new SubTree();
	vector<int>* Neighbour=new vector<int>();
	Neighbour=stNeighbour(RootSTree);
	

	return ResultCluster;
}




//int findNeighbour()


