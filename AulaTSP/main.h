#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include "tspinstance.h"
#include "mygraphlib.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include "graphviewer.h"
#include "tspmodel.h"

using namespace std;

typedef struct structParams
{
    int timeLimit;
    string inputFile;
    bool visualize;
    //string    outputFile;
} Params;

void readCheckParams(Params &params, int argc, char *argv[]);
void readInstance(Graph &dg, NodePosMap &dposx, NodePosMap &dposy, EdgeValueMap &weight, int &n, int &m, string filename);
#endif // MAIN_H
