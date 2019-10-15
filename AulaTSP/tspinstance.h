#ifndef TSPINSTANCE_H
#define TSPINSTANCE_H
#include "mygraphlib.h"

class TSPInstance
{
    public:
        TSPInstance(Graph &g, NodePosMap &posx, NodePosMap &posy, EdgeValueMap &weight, int n, int m);
        int n, m;
        Graph &g;
        NodePosMap &posx;
        NodePosMap &posy;
        EdgeValueMap &weight;
};

#endif // TSPINSTANCE_H
