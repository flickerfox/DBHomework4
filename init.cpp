#include <iostream>
#include<string>
#include <fstream>
#include "Edge.h"
#include "Node.h"
#include "DBHomework.h"
using namespace std;

void init()
{
	nodesList = new Node*[779752];
	edgesList = new Edge*[1050479];

	for (int i = 0;i<779752;i++)
	{ 
		nodesList[i] = NULL;
	}
	for (int i = 0;i<1050479;i++)
	{
		edgesList[i] = NULL;
	}	
}

bool readAuthorFromFile(string path)
{
	ifstream inputFile(path+"dblp_author_new.txt", ios::in);
	if (!inputFile)
	{
		return false;
	}

	string line;
	while(true)                                         
	{
		getline(inputFile, line, '\n');

		if (line == "") break;

		size_t iPos=line.find(":");
		string authorIDStr=line.substr(0,iPos);
		int authorID = atoi(authorIDStr.c_str());
		string authorName=line.substr(iPos+1,line.length()-iPos-1);

		Node* author = new Node;
		author->setId(authorID);
		author->setAuthorName(authorName);
		nodesList[authorID] = author;
	}

	return true;
}

bool readPubFromFile(string path)
{
	ifstream inputFileInfo(path+"dblp_pubInfo_new.txt", ios::in);
	ifstream inputFileName(path+"dblp_pubName_new.txt", ios::in);
	if (!inputFileInfo || !inputFileName)
	{
		return false;
	}

	string lineInfo, lineName;
	while(true)                                         
	{
		getline(inputFileInfo, lineInfo, '\n');
		getline(inputFileName, lineName, '\n');

		if (lineInfo == "" || lineName == "")
			break;

		size_t iPos=lineInfo.find(":");
		string pubIDStr=lineInfo.substr(0,iPos);
		int pubID = atoi(pubIDStr.c_str());
		string pubInfo=lineInfo.substr(iPos+1,lineInfo.length()-iPos-1);
		size_t iPos1=pubInfo.find(":");
		string pubInfo1=pubInfo.substr(0,iPos1);
		string pubInfoLast=pubInfo.substr(iPos1+1,lineInfo.length()-iPos1-1);
		size_t iPos2=pubInfoLast.find(":");
		string pubInfo2=pubInfoLast.substr(0,iPos2);
		string pubInfo3=pubInfoLast.substr(iPos2+1,lineInfo.length()-iPos2-1);

		size_t iPosName=lineName.find(":");
		pubIDStr=lineName.substr(0,iPosName);
		if (pubID != atoi(pubIDStr.c_str())) 
			return false;
		string pubName=lineName.substr(iPosName+1,lineName.length()-iPosName-1);

		Edge* pub = new Edge;
		pub->setId(pubID);
		pub->setPubName(pubName);
		pub->setDe(0);
		if (pubInfo1 != "null")	//year
		{
			pub->getTag()->push_back(true);
			pub->getAttribute()->push_back(pubInfo1);
			pub->increaseDe(1);
		}
		//if (pubInfo2 != "null")	//month
		//{
		//	pub.getTag().push_back(true);
		//	pub.getAttribute().push_back(pubInfo2);
		//	pub.increaseDe(1);
		//}
		if (pubInfo3 != "null")	//journal
		{
			pub->getTag()->push_back(true);
			pub->getAttribute()->push_back(pubInfo3);
			pub->increaseDe(1);
		}
		edgesList[pubID] = pub;
	}

	return true;
}

bool readRelationFromFile(string path)
{
	ifstream inputFile(path+"dblp_relation_new.txt", ios::in);
	if (!inputFile)
	{
		return false;
	}

	vector<int>** relationList = new vector<int>*[1050479];
	for (int i = 0;i < 1050479;i++)
	{
		relationList[i] = NULL;
	}
	string line;
	while(true)                                         
	{
		getline(inputFile, line, '\n');

		if (line == "")
			break;

		size_t iPos=line.find(":");
		string authorIDStr=line.substr(0,iPos);
		int authorID = atoi(authorIDStr.c_str());
		string pubIDStr=line.substr(iPos+1,line.length()-iPos-1);
		int pubID = atoi(pubIDStr.c_str());

		if (relationList[pubID] == NULL)
			relationList[pubID] = new vector<int>;
		relationList[pubID]->push_back(authorID);	// 添加同一个publication的作者
	}

	for (int i = 0;i < 1050479;i++)	//遍历publication
	{
		if (relationList[i] != NULL)
		{
			for (int j = 0;j < relationList[i]->size()-1;j++)	//遍历publication中的author
			{
				edgesList[i]->getNodeList()->push_back(relationList[i]->at(j));	//添加edge里的nodelist
				for (int k = j+1;k < relationList[i]->size();k++)	//添加node里的相关信息（每个关系的两个点都添加）
				{
					nodesList[relationList[i]->at(j)]->getAdjList()->push_back(relationList[i]->at(k));
					nodesList[relationList[i]->at(j)]->getEdgeList()->push_back(i);
					nodesList[relationList[i]->at(j)]->increaseDegree(1);

					nodesList[relationList[i]->at(k)]->getAdjList()->push_back(relationList[i]->at(j));
					nodesList[relationList[i]->at(k)]->getEdgeList()->push_back(i);
					nodesList[relationList[i]->at(k)]->increaseDegree(1);
				}
			}
			
			delete relationList[i];
		}
	}
	delete[] relationList;

	return true;
}