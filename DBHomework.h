#ifndef _DBHOMEWORK
#define _DBHOMEWORK

#include <string>
#include <vector>
#include "Edge.h"
#include "Node.h"
#include "Cluster.h"

extern Node** nodesList;
extern Edge** edgesList;

extern int edgeNum;
extern int nodeNum;

extern int minnumNode;
extern int minDimension;
extern double minDensity;
extern int minsimilarity;
extern double minRedundancy;

using namespace std;

void init();
bool readAuthorFromFile(string path);
bool readPubFromFile(string path);
bool readRelationFromFile(string path);
vector<Cluster>* MiMAG(Node **nodelist, Edge **edgelist);
#endif


