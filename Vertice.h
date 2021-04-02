#ifndef _VERTICE_H_
#define _VERTICE_H_
using namespace std;
#include <vector>
#include "Edge.h"
class Edge;
class Vertice{
  public:
    vector<Edge*> edges;
    int is_rec;
    int row_low;
    int row_high;
    int col_low;
    int col_high;
    int val;
    Vertice(int i_val, int i_row_low, int i_row_high, int i_col_low, int i_col_high, int i_is_rec);
 
    void add_edge(Edge *e);
};

#endif