#include <iostream>
#include<string>
#include <fstream>
#include "Edge.h"
#include "Node.h"
using namespace std;

bool init(string path)
{
	ifstream inputFile(path+"dblp_author.txt", ios::in);
	if (!inputFile)
	{
		return false;
	}

	string line;
	while(!inputFile.eof())                                         //�Ȱ��������ݶ���һ���ַ���������
	{
		inputFile>>line;
	}
}