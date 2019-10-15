#include "tspmodel.h"

double TSPModel::run(TSPInstance &instance, EdgeBoolMap &solution, int timeLimit){
    // gurobi stuff
    EdgeGRBVarMap x(instance.g);
    GRBEnv env = GRBEnv();
    GRBModel model = GRBModel(env);
    model.set(GRB_StringAttr_ModelName, "TSP");
    model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE);
    model.set(GRB_DoubleParam_MIPGap, 0.0001);
    model.getEnv().set(GRB_IntParam_LazyConstraints, 1); // must set to use branch-and-cut

    // initialize gurobi variables
    for (EdgeIt e(instance.g); e != INVALID; ++e) {
        x[e] = model.addVar(0.0, 1.0, instance.weight[e], GRB_BINARY,
                "x[" + to_string(instance.g.id(instance.g.u(e))) + "," + to_string(instance.g.id(instance.g.v(e))) + "]");
    }
    model.update();

    // Add degree constraint for each vertex
    for(NodeIt v(instance.g); v != INVALID; ++v){
        GRBLinExpr expr = 0;
        for (IncEdgeIt e(instance.g, v); e != INVALID; ++e){
            expr += x[e];
        }
        model.addConstr(expr == 2);
    }
    model.update();

    // bound the execution time
    model.getEnv().set(GRB_DoubleParam_TimeLimit, timeLimit);

    // set callback
    TSPCallback cb = TSPCallback(instance, x);
    model.setCallback(&cb);

    //gurobi tries to solve the LP
    model.optimize();
    model.update();

    //reached time limit
    if(model.get(GRB_IntAttr_Status) == 9){
        return -1;
    }

    //founded optimal solution
    else{
        double cost = 0.0;

        for(EdgeIt e(instance.g); e != INVALID; ++e){
            if(x[e].get(GRB_DoubleAttr_X) > 0.9){
                cost += instance.weight[e];
                solution[e] = true;
            }
            else{
                solution[e] = false;
            }
        }

        return cost;
    }
}
