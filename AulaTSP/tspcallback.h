#ifndef TSPCALLBACK_H
#define TSPCALLBACK_H
#include <gurobi_c++.h>
#include <utility>
#include <map>
#include "tspinstance.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mygraphlib.h"
#include <string>

class TSPCallback: public GRBCallback{
    private:
        const TSPInstance &instance;
        EdgeGRBVarMap &x;
        double (GRBCallback::*solution_value)(GRBVar);
        double eps;

    public:
        TSPCallback(TSPInstance &instance, EdgeGRBVarMap &x);
        void callback();
};

#endif // GUROBICUTSCALLBACK_H
