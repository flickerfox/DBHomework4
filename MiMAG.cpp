#include<iostream>
#include<sstream>
#include<algorithm>
#include"Edge.h"
#include"Node.h"
#include"SubTree.h"
#include"Graph.h"
#include"Cluster.h"
#include"DBHomework.h"
#include"QueueObj.h"

using namespace std;

bool pr(double s1, double s2)
{
	return s1 > s2;
}
bool qualitysort(Queueobj s1, Queueobj s2)
{
	return s1.getQuality() > s2.getQuality();
}

int graphDimension(Edge** edgelist)//整个图的维度一共多少
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

bool ifDegreeZero(int i)//判断某个点在所有维度上是否为孤立点
{
	vector<int>* degree =nodesList[i]->getDegree();
	int flag = 0;
	for (int i = 0; i < degree->size(); i++)
	{
		if (degree->at(i) != 0)
			flag = 1;
	}
	if (flag=0)
		return true;
	else
		return false;
}

SubTree* initSubTree(Node **nodelist, Edge **edgelist)//初始化subtree
{
	SubTree *subtree=new SubTree();
	int GDimension = graphDimension(edgelist);

	for (int i = 0; i < GDimension; i++)
	{
		subtree->getDimension()->push_back(i);
	}

	vector<vector<int> >* cand = new vector<vector<int> >();
	vector<int>* cand0=new vector<int>();
	for (int i = 0; i < nodeNum; i++)
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

vector<int> vectorIntersection(vector<int>v1, vector<int>v2)//求交集
{
	int i, j;
	i = j = 0;//定位到2个有序向量的头部  
	vector<int> des;
	des.clear();

	while (i < v1.size() && j < v2.size())
	{
		if (v1[i] == v2[j]) //相等则为交集的元素之一  
		{
			des.push_back(v1[i]);
			i += 1;
			j += 1;
		}
		else if (v1[i] < v2[j])   //不相等时，指示较小元素额标记加一  
		{
			i += 1;
		}
		else
		{
			j += 1;
		}
	}
	return des;
}

vector<int>* vectorUnion(vector<int> v1, vector<int> v2, vector<int>* des)//求并集  
{
	int i, j;
	i = j = 0;//定位到2个有序向量的头部  

	des->clear();
	//必有一个向量插入完成  
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

vector<int> findEdgeByNodes(int orig, int des)//通过两个点找到之间的边
{
	vector<int> result;
	vector<int>* edges = nodesList[orig]->getEdgeList();
	for (int i = 0; i < edges->size(); i++)
	{
		vector<int>* nodes = edgesList[edges->at(i)]->getNodeList();
		for (int j = 0; j < nodes->size(); j++)
		{
			if (des == nodes->at(j))
				result.push_back(edges->at(i));
		}
	}
	return result;
}

vector<int> degreeInVertices(vector<int>* VertexSet, int v)
{
	vector<int> resultdegre;
	for (int i = 0; i < VertexSet->size(); i++)
	{
		vector<int>numedge = findEdgeByNodes(VertexSet->at(i), v);//实体边
		if (numedge.size() == 0)
			break;
		if (resultdegre.size() == 0)
		{
			for (int s = 0; s < edgesList[numedge[0]]->getDe(); s++)
			{
				resultdegre.push_back(0);
			}
		}
		vector<bool>realtag;//为了满足论文的deg定义，为点的数量，也就是说某层两个点之间边再多，也只算一条。
		for (int j = 0; j < edgesList[numedge[0]]->getDe(); j++)
		{
			realtag.push_back(false);
		}
		for (int j = 0; j < numedge.size(); j++)
		{
			vector<bool>* Tag = edgesList[numedge[j]]->getTag();
			for (int k = 0; k < Tag->size(); k++)
			{
				if (Tag->at(k) == true)
				{
					realtag[k] = true;
					
				}
					//resultdegre[k] = resultdegre[k] + 1;
			}

		}
		for (int j = 0; j < realtag.size(); j++)//保证两个点每层最多只添加一条边，增加一度
		{
			if (realtag[j] == true)
				resultdegre[j] = resultdegre[j] + 1;
		}
	}
	return resultdegre;
}

vector<int>* stNeighbour(SubTree* subtree)//找到某个subtree的neighbour
{
	vector<int> *resultneighbour = new vector<int>();
	//cout << "Find Neighbour...." << endl;	
	vector<int> *temp = new vector<int>();
	for (int i = 0; i < subtree->getCandiSet()->size(); i++)
	{
		temp=vectorUnion(subtree->getCandiSet()->at(i), *temp, resultneighbour);
	}
	//cout << resultneighbour->size() << endl;

	return resultneighbour;
}

int findU(vector<int>* neighbour,SubTree* subtree)//找到U，待添加点
{
	int max = 0;
	int result = 0;
	for (int i = 0; i <neighbour->size(); i++)
	{
		if (subtree->getVertexSet()->size() == 0)
		{
			vector<int>* degree = nodesList[neighbour->at(i)]->getDegree();
			int tempmax = 0;
			for (int j = 0; j < subtree->getDimension()->size(); j++)
			{
				tempmax = tempmax + degree->at(j);
			}
			if (tempmax >= max)
			{
				max = tempmax;
				//result = nodesList[neighbour->at(i)]->getId();
				result = neighbour->at(i);
			}
		}
		else
		{
			int tempmax = 0;
			vector<int> tempdgree = degreeInVertices(subtree->getVertexSet(), neighbour->at(i));
			for (int j = 0; j<tempdgree.size(); j++)
			{
				tempmax = tempmax + tempdgree[j];
			}
			if (tempmax > max)
			{
				max = tempmax;
				result = neighbour->at(i);
			}
		}
	}
	return result;
}

void deleteNode(int u, vector<int>* cand)
{
	vector<int>::iterator itr = cand->begin();
	while (itr != cand->end())
	{
		if (*itr == u)
		{
			itr = cand->erase(itr);
		}
		else
			itr++;//这里迭代器会更新出错
	}
}

vector<int>* nodeExistDimension(int u, SubTree* subtree)//某个点在原先树的哪几层存在
{
	vector<int>*result = new vector<int>;
	vector<vector<int> >* CandiSet = subtree->getCandiSet();
	for (int i = 0; i < CandiSet->size(); i++)
	{
		vector <int>::iterator iter;
		iter = find(CandiSet->at(i).begin(), CandiSet->at(i).end(), u);
		if (iter != CandiSet->at(i).end())
		{
			result->push_back(i);
		}
		//bool result = iter == CandiSet->at(i).end() ? false : true;

	}
	return result;
}

double minVertexDensityDemension(vector<int>* vertexset,int demension)//一个点集在某个维度上的最小γ值
{
	double rO = 0.0;
	int min = 10000;
	for (int i = 0; i < vertexset->size(); i++)
	{
		vector<int> tempdgree = degreeInVertices(vertexset, vertexset->at(i));
		if (tempdgree[demension] < min)
			min = tempdgree[demension];
	}
	rO = (double)min / (double)(vertexset->size()-1);
	return rO;
}

vector<string> edgeSimilarity(vector<int>* edge,int demension)//在某个维度上的一组边是否满足相似度要求
{
	vector<string> similarity;
	vector<bool>* Tag = edgesList[edge->at(0)]->getTag();

	if (demension == 0&&Tag->at(0)==true)
	{
		string yearstring = edgesList[edge->at(0)]->getAttribute()->at(demension);
		stringstream ss;
		int minyear, maxyear;
		ss.clear();
		ss << yearstring;
		ss >> minyear;
		
		maxyear = minyear;
		for (int i = 0; i < edge->size(); i++)
		{
			int temp;
			yearstring = edgesList[edge->at(i)]->getAttribute()->at(demension);
			if (yearstring == "NULL")
			{
				similarity.push_back("-1");
				similarity.push_back("-1");
				return similarity;
			}
			ss.clear();
			ss << yearstring;
			ss >> temp;
			if (temp>maxyear)
				maxyear = temp;
			if (temp < minyear)
				minyear = temp;
		}
		if (maxyear>minyear + minsimilarity)
		{
			similarity.push_back("-1");
			similarity.push_back("-1");
		}
		else
		{
			string maxyearstring, minyearstring;
			ss.clear();
			ss << maxyear;
			ss >> maxyearstring;
			ss.clear();
			ss << minyear;
			ss >> minyearstring;
			similarity.push_back(maxyearstring);
			similarity.push_back(minyearstring);
		}
	}
	if (demension == 1&&Tag->at(1)==true)
	{
		bool flag = true;
		string journal = edgesList[edge->at(0)]->getAttribute()->at(demension);
		for (int i = 0; i < edge->size(); i++)
		{
			string temp;
			temp = edgesList[edge->at(i)]->getAttribute()->at(demension);
			if (journal.compare(temp) != 0)
				flag = false;
		}
		if (flag == true)
		{
			similarity.push_back(journal);
			similarity.push_back(journal);
		}
		else
		{
			similarity.push_back("-1");
			similarity.push_back("-1");
		}
	}
	
	return similarity;
}



void pruning(SubTree* subtree)//剪枝
{
	vector<int>* vertexset = subtree->getVertexSet();
	vector<vector<int> >* candiset = subtree->getCandiSet();
	vector<vector<string> >*subtreesimilar = new vector<vector<string> >;//保存树的每层最大最小的similarity值
	for (int i = 0; i < subtree->getDimension()->size(); i++)
	{
		vector<int>::iterator itr = (candiset->at(subtree->getDimension()->at(i))).begin();
		if (vertexset->size() == 0)
			break;
		if (vertexset->size() == 1)
		{
			while (itr != (candiset->at(subtree->getDimension()->at(i))).end())
			{
				vector<int>edges = findEdgeByNodes(vertexset->at(0), *itr);
				if (edges.size() == 0)
				{
					itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
				}
				else
				{
					int edgeflag = false;
					for (int j = 0; j < edges.size(); j++)
					{
						vector<bool>* tag=edgesList[edges[j]]->getTag();
						if (tag->at(subtree->getDimension()->at(i)) == true)//满足在指定维度至少有一条边存在
						{
							edgeflag = true;//加break
							break;
						}
					}				
					if (edgeflag = true)
					{
						vector<string> edgesimlar = edgeSimilarity(&edges, subtree->getDimension()->at(i));//两个点之间可能有很多边，他们之间是否满足相似度要求
						if (edgesimlar[0].compare("-1")!=0&&edgesimlar[1].compare("-1")!=0)//保证能加入的点都是满足相似度的点
							itr++;
						else
						{
							itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
						}
					}
					else
					{
						itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
					}
				}
			}
		}
		else if (vertexset->size()==2)
		{
			vector<int>edges = findEdgeByNodes(vertexset->at(0), vertexset->at(1));
			vector<string> edgesimlar = edgeSimilarity(&edges, subtree->getDimension()->at(i));
			//subtreesimilar->push_back(edgesimlar);
			if (subtree->getDimension()->at(i)==0)
			{
				string maxyearstr = edgesimlar[0];
				string minyearstr = edgesimlar[1];
				int maxyear;
				int minyear;
				stringstream ss;
				ss.clear();
				ss << maxyearstr;
				ss >> maxyear;
				ss.clear();
				ss << minyearstr;
				ss >> minyear;
				while (itr != (candiset->at(subtree->getDimension()->at(i))).end())
				{
					bool flag = false;//默认使得控制的属性也被排除
					int nextmax = maxyear;
					int nextmin = minyear;
					for (int j = 0; j < vertexset->size(); j++)
					{
						vector<int>edges = findEdgeByNodes(vertexset->at(j), *itr);
						for (int k = 0; k < edges.size(); k++)//两个点之间每层可能有多条边也是醉了
						{
							vector<string>* attribute = edgesList[edges[k]]->getAttribute();
							vector<bool>* tag = edgesList[edges[k]]->getTag();
							if (tag->at(subtree->getDimension()->at(i)) == true)
							{
								int year;
								ss.clear();
								ss << attribute->at(subtree->getDimension()->at(i));
								ss >> year;
								if (year >= (maxyear - minsimilarity) && year <= (minyear + minsimilarity))
								{
									flag = true;
									if (year > nextmax)
										nextmax = year;
									if(year < nextmin)
										nextmin = year;
								}
								else//两个点之间某一层上的所有边，有一条边的similarity不满足都不行，需要删除该点
								{
									flag = false;
									break;
								}
							}
						}
						if (flag == false)//和某一个点不满足similarity其他点也不必测试直接排除
							break;
					}
					if (flag == true)//满足similarity条件
					{
						itr++;
					}
					else//所有false情况删除
					{
						itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
					}
					//vector<string> nextsubtsimlar;
					//string nextmaxstr, nextminstr;
					//ss << nextmax;
					//ss >> nextmaxstr;
					//ss << nextmin;
					//ss >> nextminstr;
					//nextsubtsimlar.push_back(nextmaxstr);
					//nextsubtsimlar.push_back(nextminstr);
					//subtreesimilar->push_back(nextsubtsimlar);//第一层最大最小值放入subtree中保存	
				}
			}
			if (subtree->getDimension()->at(i) == 1)
			{
				string journal = edgesimlar[0];
				while (itr != (candiset->at(subtree->getDimension()->at(i))).end())
				{
					bool flag = false;//默认使得控制的属性也被排除
					for (int j = 0; j < vertexset->size(); j++)
					{
						vector<int>edges = findEdgeByNodes(vertexset->at(j), *itr);
						for (int k = 0; k < edges.size(); k++)//两个点之间每层可能有多条边也是醉了
						{
							vector<string>* attribute = edgesList[edges[k]]->getAttribute();
							vector<bool>* tag = edgesList[edges[k]]->getTag();
							if (tag->at(subtree->getDimension()->at(i)) == true)
							{
								string testjournal= attribute->at(subtree->getDimension()->at(i));
								if (testjournal==journal)
									flag = true;
								else//两个点之间某一层上的所有边，有一条边的similarity不满足都不行，需要删除该点
								{
									flag = false;
									break;
								}
							}
						}
						if (flag == false)//和某一个点不满足similarity其他点也不必测试直接排除
							break;
					}
					if (flag == true)//满足similarity条件
					{
						itr++;
					}
					else//所有false情况删除
					{
						itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
					}

				}
				//vector<string> nextsubtsimlar;			
				//nextsubtsimlar.push_back(journal);
				//nextsubtsimlar.push_back(journal);
				//subtreesimilar->push_back(nextsubtsimlar);//第一层最大最小值放入subtree中保存
				//subtree->setEdgesimilarity(subtreesimilar);
			}
			
		}
		else
		{
			vector<vector<string> >*subtreesimilar = subtree->getEdgesimilarity();
			if (subtree->getDimension()->at(i) == 0)
			{
				string maxyearstr = subtreesimilar->at(0)[0];
				string minyearstr = subtreesimilar->at(0)[1];
				int maxyear;
				int minyear;
				stringstream ss;
				ss.clear();
				ss << maxyearstr;
				ss >> maxyear;
				ss.clear();
				ss << minyearstr;
				ss >> minyear;
				while (itr != (candiset->at(subtree->getDimension()->at(i))).end())
				{
					bool flag = false;//默认使得控制的属性也被排除
					int nextmax = maxyear;
					int nextmin = minyear;
					for (int j = 0; j < vertexset->size(); j++)
					{
						vector<int>edges = findEdgeByNodes(vertexset->at(j), *itr);
						for (int k = 0; k < edges.size(); k++)//两个点之间每层可能有多条边也是醉了
						{
							vector<string>* attribute = edgesList[edges[k]]->getAttribute();
							vector<bool>* tag = edgesList[edges[k]]->getTag();
							if (tag->at(subtree->getDimension()->at(i)) == true)
							{
								int year;
								ss.clear();
								ss << attribute->at(subtree->getDimension()->at(i));
								ss >> year;
								if (year >= (maxyear - minsimilarity) && year <= (minyear + minsimilarity))
								{
									flag = true;
									if (year > nextmax)
										nextmax = year;
									if (year < nextmin)
										nextmin = year;
								}
								else//两个点之间某一层上的所有边，有一条边的similarity不满足都不行，需要删除该点
								{
									flag = false;
									break;
								}
							}
						}
						if (flag == false)//和某一个点不满足similarity其他点也不必测试直接排除
							break;
					}
					if (flag == true)//满足similarity条件
					{
						itr++;
					}
					else//所有false情况删除
					{
						itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
					}
				}
			}
			if (subtree->getDimension()->at(i) == 1)
			{
				string journal = subtreesimilar->at(1)[0];
				while (itr != (candiset->at(subtree->getDimension()->at(i))).end())
				{
					bool flag = false;//默认使得控制的属性也被排除
					for (int j = 0; j < vertexset->size(); j++)
					{
						vector<int>edges = findEdgeByNodes(vertexset->at(j), *itr);
						for (int k = 0; k < edges.size(); k++)//两个点之间每层可能有多条边也是醉了
						{
							vector<string>* attribute = edgesList[edges[k]]->getAttribute();
							vector<bool>* tag = edgesList[edges[k]]->getTag();
							if (tag->at(subtree->getDimension()->at(i)) == true)
							{
								string testjournal = attribute->at(subtree->getDimension()->at(i));
								if (testjournal == journal)
									flag = true;
								else//两个点之间某一层上的所有边，有一条边的similarity不满足都不行，需要删除该点
								{
									flag = false;
									break;
								}
							}
						}
						if (flag == false)//和某一个点不满足similarity其他点也不必测试直接排除
							break;
					}
					if (flag == true&&vertexset->size()>=minnumNode)//满足similarity条件并满足节点数
					{
						vector<int> alldegree = degreeInVertices(vertexset, *itr);
						int itdegree = alldegree[subtree->getDimension()->at(i)];
						double rO = (double)itdegree / (double)(candiset->at(subtree->getDimension()->at(i))).size();
						if (rO<minDensity)//density不满足的点需要删除
						{
							itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
						}
						else
							itr++;
					}
					else//所有false情况删除
					{
						itr = (candiset->at(subtree->getDimension()->at(i))).erase(itr);
					}

				}
			}
		}
	}
	vector<int>::iterator itr = subtree->getDimension()->begin();
	while (itr != subtree->getDimension()->end())
	{
		vector<int> candi = candiset->at(*itr);
		if (candi.size() == 0)
			itr = subtree->getDimension()->erase(itr);
		else
			itr++;
	}
	
}

vector<int> edgesForVertices(vector<int> vertices)
{
	vector<int>result;
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = i + 1; j < vertices.size(); j++)
		{
			vector<int> edges = findEdgeByNodes(vertices[i], vertices[j]);
			result.insert(result.end(), edges.begin(), edges.end());
		}
	}
	return result;
}

vector<int> getEdgeInDemension(vector<int>edge,int dem)
{
	vector<int>result;
	for (int j = 0; j < edge.size(); j++)
	{
		vector<bool>*tag = edgesList[edge[j]]->getTag();
		if (tag->at(dem) == true)
		{
			result.push_back(edge[j]);
		}
	}
	return result;
}

double ovlmin(SubTree* subtree, Cluster* cluster)//算冗余度下届的情况
{
	double result;
	int O = subtree->getVertexSet()->size();
	vector<int> intersectionvex = vectorIntersection(*(subtree->getVertexSet()), *(cluster->getVertexSet()));//找到公共点集
	vector<int>intersectedge=edgesForVertices(intersectionvex);//所有的点集交集的边的数量

	for (int i = 0; i < subtree->getDimension()->size(); i++)
	{
		double tempmin = 10.0;
		vector<int>unionvexdim = *(subtree->getVertexSet());
		unionvexdim.insert(unionvexdim.end(), subtree->getCandiSet()->at(subtree->getDimension()->at(i)).begin(), subtree->getCandiSet()->at(subtree->getDimension()->at(i)).end());
		//上面一行求树点集与在该层上的候选集的并集
		vector<int>unionvex_intersect_dim = vectorIntersection(unionvexdim, *(cluster->getVertexSet()));
		//在于cluster的集合做交集
		vector<int>union_dimedges = edgesForVertices(unionvexdim);
		vector<int>union_dimedges_intersect = edgesForVertices(unionvex_intersect_dim);
		
		int numedges_intersect_dim = getEdgeInDemension(intersectedge, subtree->getDimension()->at(i)).size();
		//算出交集在这一层上的边|Ei(O交O')|，下面类似
		vector<int>union_dimedges_dim = getEdgeInDemension(union_dimedges, subtree->getDimension()->at(i));
		vector<int>union_dimedges_intersect_dim = getEdgeInDemension(union_dimedges_intersect, subtree->getDimension()->at(i));
		sort(union_dimedges_dim.begin(), union_dimedges_dim.end());
		sort(union_dimedges_intersect_dim.begin(), union_dimedges_intersect_dim.end());

		vector<int>intersect_result = vectorIntersection(union_dimedges_dim, union_dimedges_intersect_dim);
		int k = union_dimedges_dim.size() - intersect_result.size();

		int maxnumerator = 0;
		if (((O*O + O) / 4) - numedges_intersect_dim - k > 0)
			maxnumerator = ((O*O + O) / 4) - numedges_intersect_dim - k;
		int numerator = numedges_intersect_dim + maxnumerator;
		int denominator = numerator + k;
		tempmin = (double)numerator / (double)denominator;
		if (tempmin < result)
			result = tempmin;
	}

	return result;
}

vector<double> r_i_max_n_imaxCal(SubTree* subtree,int dem)
{
	vector<double>result;
	double r_i_max = 1.0;
	double n_i_max;
	vector<int>* vertex = subtree->getVertexSet();
	vector<int>* unionvertex = new vector<int>;
	vectorUnion(*vertex, subtree->getCandiSet()->at(dem), unionvertex);
	int min = 10000;
	for (int i = 0; i < vertex->size(); i++)
	{
		vector<int> tempdgree = degreeInVertices(unionvertex, vertex->at(i));
		if (tempdgree[dem] < min)
			min = tempdgree[dem];
	}

	int min_deg = min;
	double tempr_i_max = (double)min_deg / (double)vertex->size();
	if (tempr_i_max < r_i_max)
		r_i_max = tempr_i_max;
	result.push_back(r_i_max);

	n_i_max = min_deg / 0.5 + 1.0;
	if (n_i_max>(double)unionvertex->size())
		n_i_max = (double)unionvertex->size();
	result.push_back(n_i_max);
	return result;
}

double qestQuality(Queueobj* obj)
{
	double result = 0;
	if (obj->getType() == 0)//树的quality计算
	{
		SubTree* subtree = (obj->getSubtree());
		vector<double>r_i_max;
		vector<double>n_i_max;
		for (int i = 0; i < subtree->getDimension()->size(); i++)
		{
			vector<double>r_i_max_n_imax= r_i_max_n_imaxCal(subtree, subtree->getDimension()->at(i));
			r_i_max.push_back(r_i_max_n_imax[0]);
			n_i_max.push_back(r_i_max_n_imax[1]);
		}
		sort(r_i_max.begin(), r_i_max.end(),pr);//降序排列
		sort(n_i_max.begin(), n_i_max.end(),pr);
		for (int j = 0; j < subtree->getDimension()->size(); j++)
		{
			double sum_r_i_max = 0;
			for (int k = 0; k < j + 1; k++)
			{
				sum_r_i_max = sum_r_i_max + r_i_max[k];
			}
			double temp = sum_r_i_max * n_i_max[j];
			if (result < temp)
				result = temp;
		}
		return result;
	}
	else//计算cluster的质量
	{
		Cluster* cluster = (obj->getCluster());
		if (cluster->getVertexSet()->size() < minnumNode&&cluster->getDimension()->size() < minDimension)
			return -1;
		else
		{
			double rdensity = 0.0;
			for (int i = 0; i < cluster->getDimension()->size(); i++)
			{
				rdensity = rdensity + minVertexDensityDemension(cluster->getVertexSet(), cluster->getDimension()->at(i));		
			}
			rdensity = rdensity / cluster->getDimension()->size();
			double Q = rdensity*cluster->getVertexSet()->size()*cluster->getDimension()->size();
			return Q;
		}
	}
}

double calQuality(Queueobj* obj, vector<Cluster>* resultcluster)
{
	if (obj->getType() == 0)//树的quality计算
	{
		SubTree* subtree = (obj->getSubtree());
		if (subtree->getDimension()->size() == 0)
			return -1;
		else
		{
			bool flag = true;
			for (int i = 0; i < resultcluster->size(); i++)
			{
				if (ovlmin(subtree, &resultcluster->at(i)) >= minRedundancy)
				{
					flag = false;
					break;
				}
			}
			if (flag = false)
				return -1;
			else
			{
				double result = qestQuality(obj);
				return result;
			}
		}
	}
	else//cluster的计算
	{
		double result = qestQuality(obj);
		return result;
	}
}

bool redundancyBetweenCluster(Cluster* origcluster, Cluster* descluster)//前面是否是后面的冗余
{
	bool flag = false;

	vector<int>* oridimension = origcluster->getDimension();
	vector<int> origedges = edgesForVertices(*origcluster->getVertexSet());

	vector<int>* desdimension = descluster->getDimension();
	vector<int>desedges = edgesForVertices(*descluster->getVertexSet());

	vector<int> intersecdimension = vectorIntersection(*oridimension, *desdimension);
	double overlap = 0;
	for (int i = 0; i < intersecdimension.size(); i++)
	{
		vector<int> orig_edges_dim = getEdgeInDemension(origedges, intersecdimension[i]);
		vector<int>des_edges_dim = getEdgeInDemension(desedges, intersecdimension[i]);
		vector<int>intersect_edges_dim = vectorIntersection(orig_edges_dim, des_edges_dim);
		overlap = overlap + (double)intersect_edges_dim.size() / (double)origedges.size();
	}
	if (overlap / (double)oridimension->size() >= minRedundancy)
		flag = true;
	return flag;
}




bool ifAddCluster(Cluster* cluster, vector<Queueobj >* queue, vector<Cluster>* resultcluster)
{
	if (cluster->getVertexSet()->size() >= minnumNode)
	{
		bool flag = true;
		for (int i = 0; i < resultcluster->size(); i++)
		{
			if (redundancyBetweenCluster(cluster, &resultcluster->at(i)) == false)
			{
				flag = false;
				break;
			}
		}
		if (flag == true)
		{
			Queueobj* obj = new Queueobj;
			obj->setCluster(cluster);
			obj->setType(1);
			double quality = calQuality(obj, resultcluster);
			obj->getCluster()->setQuality(quality);
			queue->push_back(*obj);
			return true;
		}	
		return false;
	}	
	return false;
}



void expandSubtree(SubTree* subtree, int u, vector<Queueobj >* queue, vector<Cluster>* resultcluster)
{
	SubTree* nexttree = new SubTree();
	bool ifcluster = false;
	vector<int>vertex = *subtree->getVertexSet();
	vertex.push_back(u);
	nexttree->setVertexSet(&vertex);


	vector<int>* origindimension = subtree->getDimension();
	vector<int> nextdimension =*nodeExistDimension(u,subtree);
	//cout << nextdimension->size() << endl;
	nexttree->setDimension(&nextdimension);
	vector<vector<string> >*subtreesimilar=subtree->getEdgesimilarity();
	vector<vector<int> >* nextcandiset = new vector<vector<int> >;	
	for (int i = 0; i < nextdimension.size(); i++)
	{
		if (subtree->getVertexSet()->size() == 2)//结点为二初始化similar
		{
			if (nextdimension[i] == 0)//0层时
			{
				vector<int> edgelist = findEdgeByNodes(subtree->getVertexSet()->at(0), u);
				int maxyear = 0;
				int minyear = 10000;
				stringstream ss;
				for (int k = 0; k < edgelist.size(); k++)
				{
					vector<bool>* tag = edgesList[edgelist[k]]->getTag();
					vector<string>* attribute = edgesList[edgelist[k]]->getAttribute();
					if (tag->at(nextdimension[i]) == true)
					{
						string yearstr = attribute->at(nextdimension[i]);
						int year;
						ss.clear();
						ss << yearstr;
						ss >> year;
						if (year>maxyear)
							maxyear = year;
						if (year < minyear)
							minyear = year;
					}
				}
				string maxyearstr, minyearstr;
				ss.clear();
				ss << maxyear;
				ss >> maxyearstr;
				ss.clear();
				ss << minyear;
				ss >> minyearstr;
				vector<string>similar0;
				similar0.push_back(maxyearstr);
				similar0.push_back(minyearstr);
				subtreesimilar->push_back(similar0);
			}
			if (nextdimension[i] == 1)//1层时
			{
				vector<int> edgelist = findEdgeByNodes(subtree->getVertexSet()->at(0), u);
				string journal;
				for (int k = 0; k < edgelist.size(); k++)
				{
					vector<bool>* tag = edgesList[edgelist[k]]->getTag();
					vector<string>* attribute = edgesList[edgelist[k]]->getAttribute();
					if (tag->at(nextdimension[i]) == true)
					{
						journal = attribute->at(nextdimension[i]);
						break;
					}
				}
				vector<string>similar1;
				similar1.push_back(journal);
				similar1.push_back(journal);
				subtreesimilar->push_back(similar1);
			}
			subtree->setEdgesimilarity(subtreesimilar);//设定subtree的smilar值
		}
		if (subtree->getVertexSet()->size() >= 3)//当结点有了三个时需要更新similarity数据
		{
			if (nextdimension[i] == 0)//0层时 一层journal已经定死
			{
				vector<string> similar0 = subtreesimilar->at(nextdimension[i]);
				string maxyearstr = similar0[0];
				string minyearstr = similar0[1];
				int maxyear, minyear;
				stringstream ss;
				ss.clear();
				ss << maxyearstr;
				ss >> maxyear;
				ss.clear();
				ss << minyearstr;
				ss >> minyear;

				for (int j = 0; j < subtree->getVertexSet()->size(); j++)
				{
					vector<int> edgelist = findEdgeByNodes(subtree->getVertexSet()->at(j), u);
					for (int k = 0; k < edgelist.size(); k++)
					{
						vector<bool>* tag = edgesList[edgelist[k]]->getTag();
						vector<string>* attribute = edgesList[edgelist[k]]->getAttribute();
						if (tag->at(nextdimension[i]) == true)
						{
							string yearstr = attribute->at(nextdimension[i]);
							int year;
							ss.clear();
							ss << yearstr;
							ss >> year;
							if (year>maxyear)
								maxyear = year;
							if (year < minyear)
								minyear = year;
						}
					}
				}
				ss.clear();
				ss << maxyear;
				ss >> maxyearstr;
				ss.clear();
				ss << minyear;
				ss >> minyearstr;
				similar0[0] = maxyearstr;
				similar0[1] = minyearstr;
				subtreesimilar->at(nextdimension[i]) = similar0;
			}
			
		}

		vector<int> candii;//******************************
		for (int j = 0; j < origindimension->size(); j++)
		{
			if (nextdimension[i] == origindimension->at(j))
			{
				vector<int> temp = subtree->getCandiSet()->at(origindimension->at(j));
				candii.assign(temp.begin(), temp.end());
				//cout <<"原来的size" <<candii.size() << endl;
				if (candii.size()!=0)
					deleteNode(u, &candii);
				if (nextcandiset->size() < nextdimension[i])//补上缺失的某一层的空candi站位
				{
					vector<int> temp;
					nextcandiset->push_back(temp);
				}
				nextcandiset->push_back(candii);
				cout << "现在的size" << candii.size() << endl;
				break;
			}
			else
			{
				if (nextcandiset->size() < nextdimension[i])//补上缺失的某一层的空candi站位
				{
					vector<int> temp;
					nextcandiset->push_back(temp);
				}
			}
			
		}
		
	}
	nexttree->setCandiSet(nextcandiset);

	
	Cluster *cluster = new Cluster;
	vector<int>cluster_vertex;
	cluster_vertex = *nexttree->getVertexSet();
	cluster->setVertexSet(&cluster_vertex);

	vector<int>cluster_dim;
	cluster_dim = nextdimension;
	cluster->setDimension(&cluster_dim);

	ifAddCluster(cluster, queue,resultcluster);//是否添加到queue中

	SubTree* remaintree = new SubTree;//再nexttree剪枝之前将candiset保存
	vector<int>remaintree_vertex;
	remaintree_vertex = *subtree->getVertexSet();
	remaintree->setVertexSet(&remaintree_vertex);
	vector<vector<int> >remaintree_candiset = *nextcandiset;
	remaintree->setCandiSet(&remaintree_candiset);
	vector<int>remaintree_dim = *subtree->getDimension();
	remaintree->setDimension(&remaintree_dim);
	

	pruning(remaintree);//剪枝
	pruning(nexttree);//剪枝


	Queueobj* nexttreeobj = new Queueobj;
	nexttreeobj->setSubtree(nexttree);
	nexttreeobj->setType(0);
	double nttree_quality = calQuality(nexttreeobj, resultcluster);
	if (nttree_quality > 0)//是否将nexttree加入到队列中
	{
		nexttreeobj->getSubtree()->setQuality(nttree_quality);
		queue->push_back(*nexttreeobj);
	}

	Queueobj* remaintreeobj = new Queueobj;
	remaintreeobj->setSubtree(remaintree);
	remaintreeobj->setType(0);
	double remaintree_quality = calQuality(remaintreeobj, resultcluster);
	if (remaintree_quality > 0)
	{
		remaintreeobj->getSubtree()->setQuality(remaintree_quality);
		queue->push_back(*remaintreeobj);
	}
}

vector<Cluster>* MiMAG(Node **nodelist, Edge **edgelist)//主算法
{
	vector<Cluster>* ResultCluster=new vector<Cluster>();
	vector<Queueobj >* Queue = new vector<Queueobj >();
	SubTree *RootSTree=new SubTree();
	RootSTree = initSubTree(nodelist, edgelist);

	SubTree *NextSTree = new SubTree();
	vector<int>* Neighbour=new vector<int>();
	Neighbour=stNeighbour(RootSTree);
	int u = findU(Neighbour, RootSTree);
	cout <<"id："<< u << endl;
	expandSubtree(RootSTree, u, Queue,ResultCluster);
	/*vector<int>* degree  = nodelist[u]->getDegree();
	for (int l = 0; l < nodeNum; l++)
	{
	if (nodelist[l] != NULL)
	{
	vector<int>* degree = nodelist[l]->getDegree();
	if (degree->at(0) != degree->at(1))
	cout << degree->at(1)-degree->at(0) << endl;
	}
	}*/
	while (Queue->size() != 0)
	{
		sort(Queue->begin(), Queue->end(), qualitysort);
		vector<Queueobj >::iterator itr = Queue->begin();
		if ((itr)->getType() == 0)
		{
			SubTree* newtree = new SubTree;
			newtree = (itr)->getSubtree();
			Neighbour = stNeighbour(newtree);
			u = findU(Neighbour, newtree);
			expandSubtree(newtree, u, Queue, ResultCluster);
		}
		else
		{
			Cluster*cluster = new Cluster;
			bool flag = true;
			cluster = (itr)->getCluster();
			for (int i = 0; i < ResultCluster->size(); i++)
			{
				if (redundancyBetweenCluster(cluster, &ResultCluster->at(i)) == false)
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				ResultCluster->push_back(*cluster);
			}
		}
		Queue->erase(itr);
	}
	

	return ResultCluster;
}






