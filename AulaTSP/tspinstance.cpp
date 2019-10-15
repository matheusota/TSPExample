#include "tspinstance.h"

TSPInstance::TSPInstance(Graph &g, NodePosMap &posx, NodePosMap &posy, EdgeValueMap &weight, int pn, int pm):
    g(g),
    posx(posx),
    posy(posy),
    weight(weight)
{
    this->n = pn;
    this->m = pm;
}
