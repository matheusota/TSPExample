#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H
#include "mygraphlib.h"
#include <string>
#include <vector>

class GraphViewer
{
    private:
        static vector<string> colors;

    public:
        static void viewSolution(Graph &g, NodePosMap &posx, NodePosMap &posy, EdgeBoolMap &solution, string title);
};

#endif // GRAPHVIEWER_H
