#ifndef TSPMODEL_H
#define TSPMODEL_H
#include <gurobi_c++.h>
#include "tspinstance.h"
#include "mygraphlib.h"
#include "tspcallback.h"

class TSPModel
{
    public:
        static double run(TSPInstance &instance, EdgeBoolMap &solution, int timeLimit);
};

#endif // TSPMODEL_H
