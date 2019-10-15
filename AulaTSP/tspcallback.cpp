#include "tspcallback.h"

TSPCallback::TSPCallback(TSPInstance &instance, EdgeGRBVarMap &x): instance(instance), x(x){
    eps = 0.0001;
}

// subtour elimination
void TSPCallback::callback(){
     // integer solution
    if (where == GRB_CB_MIPSOL)
        solution_value = &TSPCallback::getSolution;
    // fractional solution
    else if ((where == GRB_CB_MIPNODE) && (getIntInfo(GRB_CB_MIPNODE_STATUS) == GRB_OPTIMAL)){
        solution_value = &TSPCallback::getNodeRel;
    }
    else{
        return;
    }

    try {
        // get variables value
        EdgeValueMap varsValue(instance.g);
        for(EdgeIt e(instance.g); e != INVALID; ++e){
            varsValue[e] = (this->*solution_value)(x[e]);
//            cout << "x[" << instance.g.id(instance.g.u(e)) << "][" << instance.g.id(instance.g.v(e)) <<
//                    "] = " << varsValue[e] << endl;
        }

        // now we get the minimum cut between the root(0) and all other vertices
        CutMap cut(instance.g);
        double cutValue;
        Node s = instance.g.nodeFromId(0);

        for(NodeIt v(instance.g); v != INVALID; ++v){
            if(instance.g.id(v) != 0){
                // find a mincut between s and v
                cutValue = MinCut(instance.g, varsValue, s, v, cut);

                // violated cut
                if(cutValue < 2 - eps){
                    // add corresponding constraint
                    GRBLinExpr expr = 0;

                    for(EdgeIt e(instance.g); e != INVALID; ++e){
                        if((cut[instance.g.u(e)] == cut[s] && cut[instance.g.v(e)] == cut[v]) ||
                                (cut[instance.g.v(e)] == cut[s] && cut[instance.g.u(e)] == cut[v])){

                            //cout << "x[" << instance.g.id(instance.g.u(e)) << "][" << instance.g.id(instance.g.v(e)) << "] + ";
                            expr += x[e];
                        }
                    }

                    //cout << " >= 2" << endl;
                    addLazy(expr >= 2);
                }
            }
        }
    } catch (GRBException e) {
        cout << "Error number: " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
      } catch (...) {
        cout << "Error during callback**" << endl;
    }
}
