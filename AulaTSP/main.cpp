#include "main.h"

int main(int argc, char *argv[]){
    Graph g;
    NodePosMap posx(g);
    NodePosMap posy(g);
    EdgeValueMap weight(g);
    int n, m;

    // read parameters from command line
    Params params;
    readCheckParams(params, argc, argv);

    // read instance from file
    readInstance(g, posx, posy, weight, n, m, params.inputFile);
    TSPInstance instance(g, posx, posy, weight, n, m);

    // solve it
    EdgeBoolMap solution(g);

    auto started = chrono::high_resolution_clock::now();
    double solCost = TSPModel::run(instance, solution, params.timeLimit);
    auto done = chrono::high_resolution_clock::now();

    int time = chrono::duration_cast<chrono::milliseconds>(done-started).count();
    cout << "Solution cost: " << solCost << endl;
    cout << "Time to solve: " << to_string(time) << "ms" << endl;

    // visualize
    if(params.visualize){
        stringstream stream;
        stream << fixed << setprecision(2) << solCost;
        string costString = stream.str();
        GraphViewer::viewSolution(g, posx, posy, solution,
            params.inputFile + "    ->    Cost: " + costString + "  Time: " + to_string(time) + "ms");
    }
    return 0;
}

// read argv params
void readCheckParams(Params &params,int argc, char *argv[])
{
    params.timeLimit  = 3600;
    params.inputFile  = "";
    params.visualize = false;

    // Read
    for(int i = 1; i < argc; i++){
        const string arg(argv[i]);
        string next;

        if((i+1) < argc){
            next = string(argv[i+1]);
        }
        else{
            next = string("");
        }

        if(arg.find("-t") == 0 && next.size() > 0){
            params.timeLimit = atoi(next.c_str());
            i++;
            continue;
        }

        if(arg.find("-i") == 0 && next.size() > 0){
            params.inputFile = next;
            i++;
            continue;
        }

        if(arg.find("-v") == 0){
            params.visualize = true;
            continue;
        }

        cerr << "Invalid parameter." << endl;
        exit(1);
    }

    // Check
    if(params.inputFile == ""){
        cerr << "Input file should be specified" << endl;
        exit(1);
    }
}

// read file and create corresponding graph
void readInstance(Graph &g, NodePosMap &posx, NodePosMap &posy, EdgeValueMap &weight, int &n, int &m, string filename){
    // Read the graph (only nodes and edges)
    GraphTable GT(filename, g);
    n = GT.getNNodes();
    m = GT.getNEdges();

    // get weights, terminals and positions
    GT.GetColumn("weight", weight);
    GT.GetNodeCoordinates("posx", posx, "posy", posy);


//    cout << "vertices" << endl;
//    for(NodeIt v(g); v != INVALID; ++v){
//        cout << g.id(v) << endl;
//    }
//    cout << "edges" << endl;
//    for(EdgeIt e(g); e != INVALID; ++e){
//        cout << "(" << g.id(g.u(e)) << "," << g.id(g.v(e)) << ")" << endl;
//    }
}
