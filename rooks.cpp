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
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>


class Vertice{
  public:
    vector<Edge> edges;
    int is_rec;
    int row_low;
    int row_high;
    int col_low;
    int col_high;
    int val;
    Vertice(int i_val, int i_row_low, int i_row_high, int i_col_low, int i_col_high, int i_is_rec){
      if (i_is_rec){
        is_rec = i_is_rec;
        row_low = i_row_low;
        row_high = i_row_high;
        col_low = i_col_low;
        col_high = i_col_high;
      } else {
        is_rec = 0;
        val = i_val;
      }
    }
    Vertice(){
      ;
    }

    void add_edge(Edge edge){
      edges.push_back(edge);
    }
};
class Edge{
  public:
    Vertice parent;
    Vertice child;
    
    long long int capacity;
    long long int reverse_capacity;
    
    Edge(Vertice i_parent, Vertice i_child){
      parent = i_parent;
      child = i_child;
      capacity = 1;
      reverse_capacity = 0;
    }
    Edge(){
      ;
    }
};
class Graph{
public:
  vector<Vertice> all_vertices;
  vector<Vertice> row_vertices;
  vector<Vertice> rec_vertices;
  vector<Vertice> col_vertices;
  Vertice s;
  Vertice t;
   has_pos_edge(Vertice v){
    
  }
  int get_aug_path(Vertice cur, vector<edge> &path){
    for (Edge e:cur.edges){
      if (e.parent == cur && e.capacity > 0){
        e.capacity = 0;
        e.reverse_capacity = 1;
        path.push_back(e);
        if (get_aug_path(e.child, path) < 0){
          path.
        }
      } || e.child == cur &&  e.reverse_capacity  > 0)
      {
        int temp = e.capacity;
        e.capacity = e.reverse_capacity;
        e.reverse_capacity = temp;
        path.push_back(e);
      }
    }
  }
  Graph(int n, int k, vector<int> rec_row_low, vector<int> rec_row_high, vector<int> rec_col_low, vector<int> rec_col_high)
  {
    for (int i = 0; i < n; i ++){
      Vertice new_row_v(i, 0, -1, -1, -1, -1);
      row_vertices.push_back(new_row_v);
      all_vertices.push_back(new_row_v);
      Vertice new_col_v(i, 0, -1, -1, -1, -1);
      col_vertices.push_back(new_col_v);
      all_vertices.push_back(new_col_v);
    }
    for (int i = 0; i < rec_row_low.size(); i ++){
      Vertice new_rec_v(-1, 1, rec_row_low[i], rec_row_high[i], rec_col_low[i], rec_col_high[i]);
      rec_vertices.push_back(new_rec_v);
      all_vertices.push_back(new_rec_v);
    }
    Vertice s(0, 0, 0, 0, 0, 0);
    Vertice t(0, 0, 0, 0, 0, 0);
    all_vertices.push_back(s);
    all_vertices.push_back(t);
    for (auto v:row_vertices){
      Edge row_edge(s, v);
      s.add_edge(row_edge);
      v.add_edge(row_edge);
    }
    for(auto v:col_vertices){
      Edge col_edge(v, t);
      v.add_edge(col_edge);
      t.add_edge(col_edge);
    }
    for (auto v : rec_vertices)
    {

      for (int i = v.row_low; i <= v.row_high; i++){
        Edge row_edge(row_vertices[i], v);
        row_vertices[i].add_edge(row_edge);
        v.add_edge(row_edge);
      }
      for (int i = v.col_low; i <= v.col_high; i++){
        Edge col_edge(v,col_vertices[i]);
        col_vertices[i].add_edge(col_edge);
        v.add_edge(col_edge);
      }
    }
  }
};



//4 4 1213
int main(int argc, char *argv[]) {
  srand(time(0));
  string input;
  getline(cin, input);
  Palindrome palin(input);
 
  while (true){
    if (palin.max_index == -1){
      Palindrome new_palin(input);
      palin = new_palin;
      continue;
    }
    break;
  }
  //cout << palin.max_index << " " << palin.max_len  << endl;
  cout << palin.max_index << " " << palin.max_len << " " << palin.mistake_index << " " <<palin.mistake_len_best << endl;

}
