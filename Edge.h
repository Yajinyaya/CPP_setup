#ifndef _EDGE_H_
#define _EDGE_H_
using namespace std;
class Vertice;
class Edge{
  public:
    Vertice *parent;
    Vertice *child;
    
    long long int capacity;
    long long int reverse_capacity;

    Edge (Vertice *i_parent, Vertice *i_child);
    Edge(){

    }
};
#include "Vertice.h"

#endif