/**
 * @brief 
 * Used the fingerprinting string matching algorithm mentioned in recitation 4, 
 * so that all string comparisons are in O(1) after a O(n) initialization.
 * Then at each index, the algo will try to find the longest palindrome where 
 * that index is the middle point. There are two cases, odd length palindrome and 
 * even length palindrome. They are computed separetely without hurting the overall
 * Big O run time. To find the longest palindrome at a index, binary search is 
 * used. If the longest possible palindrome is not a palindrome, it will try 
 * 1/2 the length. If 1/2 the length is too large, 1/4 would be checked.
 * If 1/2 the length is not too large, 3/4 would be checked....
 * Since string comparison is O(1), this step takes O(logn).
 * There are in total O(n) indexes, therefore in total of O(nlogn) work.
 * 
 * Additionally, to make it las vegas, if the string output at the end is not 
 * a palindrome, in which case the hash collides, a new run of the algorithm 
 * would be initialized and a new prime would be used. The expected run time is
 * still O(nlogn), as the error probability is very low and a new run is still in 
 * O(nlogn).
 */
using namespace std;
#include <iostream>
#include <queue>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>
#include "Edge.h"
#include "Vertice.h"

Vertice::Vertice(int i_val, int i_row_low, int i_row_high, int i_col_low, int i_col_high, int i_is_rec){
  if (i_is_rec){
    is_rec = i_is_rec;
    row_low = i_row_low;
    row_high = i_row_high;
    col_low = i_col_low;
    col_high = i_col_high;
    val = i_val;
  } else {
    is_rec = 0;
    val = i_val;
  }
  edges = new vector<Edge *>;
}


void Vertice::add_edge(Edge *e){
  (*edges).push_back(e);
}


Edge::Edge(Vertice *i_parent, Vertice *i_child){
  parent = i_parent;
  child = i_child;
  capacity = 1;
  reverse_capacity = 0;
}

class Graph{
public:
  vector<Vertice*> row_vertices;
  vector<Vertice*> rec_vertices;
  vector<Vertice*> col_vertices;
  Vertice *s;
  Vertice *t;
  int result = 0;

  int get_aug_path(Vertice *cur, vector<Edge*> &path, vector<bool> &discovered){
    
    if (cur == t){
      return 1;
    }
    if (discovered[cur->val]){
      return -1;
    }
    discovered[cur->val] = true;
    for (int i = 0; i < (*(cur->edges)).size(); i++){
      Edge *e = (*(cur->edges))[i];
      
      if (e->parent == cur && e->capacity > 0){
        e->capacity = 0;
        e->reverse_capacity = 0;
        path.push_back(e);
        if (get_aug_path(e->child, path, discovered) < 0)
        {
          path.pop_back();
          e->capacity = 1;
          e->reverse_capacity = 0;
          continue;
        } else {
        e->capacity = 0;
        e->reverse_capacity = 1;
        return 1;
        } 
      }else if (e->child == cur &&  e->reverse_capacity  > 0){
        e->capacity = 0;
        e->reverse_capacity = 0;
        path.push_back(e);
        if (get_aug_path(e->parent, path, discovered) < 0){
          path.pop_back();
          e->capacity = 0;
          e->reverse_capacity = 1;
          continue;
        } else {
          e->capacity = 1;
          e->reverse_capacity = 0;
          return 1;
        }
      }
    }
    return -1;
  }
  Graph(int n, int k, vector<int> &rec_row_low, vector<int> &rec_row_high, vector<int> &rec_col_low, vector<int> &rec_col_high)
  {
    int index = 0;
    for (int i = 0; i < n; i ++){
      Vertice *new_row_v= new Vertice(index, -1, -1, -1, -1, 0);
      index++;
      row_vertices.push_back(new_row_v);
      Vertice *new_col_v = new Vertice(index, -1, -1, -1, -1, 0);
      index++;
      col_vertices.push_back(new_col_v);
    }
    for (int i = 0; i < rec_row_low.size(); i ++){
      Vertice *new_rec_v = new Vertice(index, rec_row_low[i], rec_row_high[i], rec_col_low[i], rec_col_high[i], 1);
      index++;
      rec_vertices.push_back(new_rec_v);
    }
    s = new Vertice(index, 0, 0, 0, 0, 0);
    index++;
    t = new Vertice(index, 0, 0, 0, 0, 0);
    for (int i = 0; i < row_vertices.size(); i ++){
      Vertice *v = row_vertices[i];
      Edge *e = new Edge(s, v);
      (*s).add_edge(e);
      (*v).add_edge(e);
    }
     
    for (int i = 0; i < col_vertices.size(); i ++){
      Vertice *v = col_vertices[i];
      Edge *e = new Edge(v, t);
      (*v).add_edge(e);
      (*t).add_edge(e);
    }
    for (int i = 0; i < rec_vertices.size(); i ++){
      Vertice *v = rec_vertices[i];
      for (int i = (*v).row_low; i <= (*v).row_high; i++){
        Edge *e = new Edge(row_vertices[i], v);
        (*row_vertices[i]).add_edge(e);
        (*v).add_edge(e);
      }
      for (int i = (*v).col_low; i <= (*v).col_high; i++){
        Edge *e = new Edge(v,col_vertices[i]);
        (*col_vertices[i]).add_edge(e);
        (*v).add_edge(e);
      }
    }
    vector<Edge*> path;
    vector<bool> discovered(index + 1, false);
    while(get_aug_path(s, path, discovered) > 0){
      fill(discovered.begin(), discovered.end(), false);
      path.clear();
    }
    for (int i = 0; i < (*(*s).edges).size(); i ++){
      Edge *e = (*(*s).edges)[i];
      if (e->capacity == 0 && e->parent == s)
      {
        result++;
      }
    }
  }
};



//4 4 1213
int main(int argc, char *argv[]) {
  string input;
  int n;
  int k;
  vector<int> rec_row_low;
  vector<int> rec_row_high;
  vector<int> rec_col_low;
  vector<int> rec_col_high;
  cin >> n;
  cin >> k;
  for (int i = 0; i < k; i ++){
    int row_low;
    int row_high;
    int col_low;
    int col_high;
    cin >> row_low;
    cin >> col_low;
    cin >> row_high;
    cin >> col_high;
    rec_row_low.push_back(row_low);
    rec_row_high.push_back(row_high);
    rec_col_low.push_back(col_low);
    rec_col_high.push_back(col_high);
  }

  Graph g(n, k, rec_row_low, rec_row_high, rec_col_low, rec_col_high);
  cout << g.result;
 
  return 0;
}
