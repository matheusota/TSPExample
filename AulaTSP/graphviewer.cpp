#include "graphviewer.h"

// just some colors that we can use
vector<string> GraphViewer::colors = {"Gray", "Red", "Blue", "Magenta", "Orange", "Green", "Pink", "Brown", "Purple", "Yellow",
                            "Cyan", "Olive", "Beige", "Lime", "Mint", "Teal", "Navy", "Lavender"};

void GraphViewer::viewSolution(Graph &g, NodePosMap &posx, NodePosMap &posy, EdgeBoolMap &solution, string title){
    // assign names to the nodes
    NodeStringMap nodeNames(g);
    for(NodeIt v(g); v != INVALID; ++v){
        nodeNames[v] = "\"" + to_string(g.id(v)) + "\"";
    }

    // set graph attributes for the visualizer
    GraphAttributes GA(g, nodeNames, posx, posy);

    GA.SetDefaultNodeAttrib("color = Black width = 0.5 height = 0.5 fixedsize = true style = bold fontsize = 15");
    GA.SetDefaultEdgeAttrib("color = Invis");

    // color edges of the solution
    for(EdgeIt e(g); e != INVALID; ++e){
        if(solution[e]){
            GA.SetColor(e, "Black");
        }
    }

    // set graph title
    GA.SetLabel(title);

    // view graph
    GA.View();
}
