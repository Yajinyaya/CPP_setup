/**
 * @brief The algorithm runs in O(n). The summary of the algorithm is as follows
 * 1. For input of n unmbers, find k, which is the number of outputs + 1, 
 * where 2^k is the greatest power of 2 that is at most n. The cost is O(logn), 
 * as each time rank is multiplied by 2.
 * 2. Then in the for loops, We know from lecture that quickselect has expected 
 * running time of O(n). The find_ith_element is performing the quickselect 
 * to find ith element by randomly selecting a pivot and partition, continuing 
 * on the half that the desired median is in. Since the ranks to be found are 
 * multiples of 2, if we start from the largest rank, and keep finding the 
 * following ranks from the array that has already been partitioned, the 
 * running time would be half of the previous round as the length of input is 
 * halfed.Therefore T(n) = O(n) + O(n/2) +..... = O(n), as it's root dominated
 * 
 */
using namespace std;
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
/**
 * @brief after partition, the new index for the value originally at index
 * 
 * @param v 
 * @param index pivot
 * @param start 
 * @param end 
 * @return int 
 */
int partition(vector<int>&v, int index, int start, int end){
  int partition_value = v[index];
  int cur_index = start;
  int result_index = index;
  for (int i = start; i < end; i ++){
    if (v[i] < partition_value){
      if (v[cur_index] == partition_value){
        result_index = i;
      }
      swap(v[cur_index], v[i]);
      cur_index++;
      
    }
    
  }

  swap(v[cur_index], v[result_index]);
  return cur_index;
}
/**
 * @brief 
 * 
 * @param v 
 * @param start inclusive
 * @param end exclusive
 * @param i 
 * @return the index of ith element
 */
int find_ith_element(vector<int> &v, int start, int end, int index){
  if (start == end - 1 && start == index){
    return start;
  }
  int pivot_index;
  if (start == end - 1){
    pivot_index = 0;
  }{
    pivot_index = start + rand() % (end - start - 1);

  }
  int pivot_new_location = partition(v, pivot_index, start, end);
  if (pivot_new_location == index){
    return pivot_new_location;
  } else if (pivot_new_location > index){
    return find_ith_element(v, start, pivot_new_location, index);
  } else {
    return find_ith_element(v, pivot_new_location + 1, end, index);
  }
  
}

int main() {
  string num_string;
  getline(cin, num_string);
  int num_input = stoi(num_string, nullptr, 0);
  vector<int> input;
  vector<int> output;
  for (int i = 0; i < num_input; i++){
    int value;
    cin >> value;
    input.push_back(value);
  }

  int rank = 1;
  vector<int> result_ranks;
  while (rank <= num_input){
    result_ranks.push_back(rank);
    rank *= 2;
  }

  int end = num_input;
  for (long long unsigned int i = 0; i < result_ranks.size(); i++){
    int cur_mid = result_ranks[result_ranks.size() - 1 - i];
    int mid_index = find_ith_element(input, 0, end, cur_mid - 1);
    
    output.push_back(input[mid_index]);
    end = cur_mid;
  }

  cout << output.size()-1 << endl;

  for (long long unsigned int i = 0; i < output.size(); i ++){
    cout << output[output.size() - i - 1] << " ";
  }
  cout << endl;
  return 0;
}
