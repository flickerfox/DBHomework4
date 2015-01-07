#ifndef _INIT
#define _INIT

#include <string>
#include <vector>
#include "Edge.h"
#include "Node.h"
#include "Cluster.h"

extern Node** nodesList;
extern Edge** edgesList;

using namespace std;

void init();
bool readAuthorFromFile(string path);
bool readPubFromFile(string path);
bool readRelationFromFile(string path);
vector<Cluster>* MiMAG(Node **nodelist, Edge **edgelist);
#endif


