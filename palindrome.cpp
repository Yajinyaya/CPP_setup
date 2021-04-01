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


int is_prime(long long int input){
  if (input < 0){
    input = -input;
  }

  if ((input & 1) == 0){
    return input == 2;
  }

  long long int test = 3;
  while(test * test <= input){
    if (input % test == 0){
      return 0;
    }
    test += 2;
  }
  return 1;
}

long long int get_prime(long long int maximum){
  while (1){
    long long int rand_number = rand();
    long long int rand_num = rand_number % maximum;
    if (is_prime(rand_num)){
      return rand_num;
    }
  }
  return 0;
}


class Palindrome{

  vector<char> chars;
  vector<long long int> r;
  vector<long long int> a;

  vector<char> chars_rev;
  vector<long long int> r_rev;
  vector<long long int> a_rev;

  long long int str_len;
  vector<long long int> start_indexes;

  vector<long long int> lens;

  long long int N;
  long long int M;
  long long int p;
  public:
  long long int max_index = 0;
  long long int max_len = 0;
  long long int mistake_index = 0;
  long long int mistake_len_best = 0;
  int hash_equal(long long int i1, long long int j1, long long int i2, long long int j2){
    long long int hash_first = (a[j1+1] - a[i1] * r[j1+1 - i1]) % p;
    if (hash_first < 0){
      hash_first += p;
    }
    long long int new_i2 = str_len - j2 - 1;
    long long int new_j2 = str_len - i2;
    long long int hash_second = (a_rev[new_j2] - a_rev[new_i2] * r_rev[new_j2 - new_i2]) % p;
    if (hash_second < 0){
      hash_second += p;
    }

    return (hash_first == hash_second);
  }
  long long int get_longest_palin_no_center(long long int start, long long int end, 
                                     long long int max_radius, long long int min_radius){
    if (max_radius == 0){
      return 0;
    }
    if (start == end || max_radius <= min_radius ){
      return 0;
    }
    if (end + end - start >= str_len){
      return 0;
    }
   //1 2 1
    if (hash_equal(start, end-1, end + 1, end - start + end)){
  
     //not including end in palin
      if (end - start == max_radius){
        return max_radius;
      } else {
        
        return get_longest_palin_no_center((end - max_radius + start) / 2, end, max_radius, end - start - 1);
      }
    } else {
      long long int new_start = min((end + start) / 2, end - min_radius + 1);

      return get_longest_palin_no_center(new_start, end, end - start - 1, min_radius);

      // if (hash_equal(new_start, end - 1, end + 1, end - new_start + end)){
      //   return get_longest_palin_no_center((start + new_start)/2 + 1, end, max - 1);
      // } else {
      //   return get_longest_palin_no_center((end + new_start)/2 + 1, end, end - 1 - new_start);
      // }
      
    }

  } 
  long long int get_same_len_no_center(long long int start, long long int end, long long int max_radius, long long int min_radius, long long int mid){
    if (max_radius == 0){
      return 0;
    }
    if (start == end || max_radius <= min_radius ){
      return 0;
    }
    if (end + end - start >= str_len){
      return 0;
    }
   
    if (hash_equal(start, end-1, mid + mid - end + 1, mid + (mid - start))){
      if (end - start == max_radius){
        return max_radius;
      } else {
        return get_same_len_no_center((end - max_radius + start) / 2, end, max_radius, end - start -1, mid);
      }
    } else {
      long long int new_start = min((end + start) / 2, end - min_radius + 1);

      return get_same_len_no_center(new_start, end, end - start - 1, min_radius, mid);
    }
  }

  //start is the first half start index (inclusive)
//end is first half end index (exclusive)
//max is the max radius
//min is min radius (exclusive)
// a a b a a 
  
// a a a2 a a4 a a6 | a7
  long long int get_longest_palin_has_center(long long int start, long long int end, 
                                     long long int max_radius, long long int min_radius){
    if (max_radius == 0){
      return 0;
    }
    if (start == end || max_radius <= min_radius ){
      return 0;
    }
 
   //1 2 1
    if (hash_equal(start, end-1, end , end - start + end - 1)){
  
     //not including end in palin
      if (end - start == max_radius){
        return max_radius;
      } else {
        
        return get_longest_palin_has_center((end - max_radius + start) / 2, end, max_radius, end - start - 1);
      }
    } else {

      long long int new_start = min((end + start) / 2, end - min_radius + 1);

      return get_longest_palin_has_center(new_start, end, end - start - 1, min_radius);
    }

  }

  
  long long int get_same_len_has_center(long long int start, long long int end, long long int max_radius, long long int min_radius, long long int mid){
    if (max_radius == 0){
      return 0;
    }
    if (start == end || max_radius <= min_radius ){
      return 0;
    }

    if (hash_equal(start, end-1, mid + mid - end, mid + mid - start - 1)){
  
     //not including end in palin
      if (end - start == max_radius){
        return max_radius;
      } else {
        
        return get_same_len_has_center((end - max_radius + start) / 2, end, max_radius, end - start - 1, mid);
      }
    } else {

      long long int new_start = min((end + start) / 2, end - min_radius + 1);

      return get_same_len_has_center(new_start, end, end - start - 1, min_radius, mid);
    }

  }
  //a a a a a a
  long long int get_mistake_has_center(long long int has_center_radius, 
                                      long long int mid){
    if (mid - has_center_radius <= 0 || mid + has_center_radius >= str_len){
      return 0;
    }
    if (mid - has_center_radius == 1 || mid + has_center_radius == str_len - 1){
      return 1;
    }
    long long int max_addition_len = min(mid - has_center_radius - 1, str_len - (mid + has_center_radius) - 1);
    return 1 + get_same_len_has_center(mid - has_center_radius - 1 - max_addition_len, 
                            mid - has_center_radius - 1, max_addition_len, 0, mid);

  }
  //a a a b a a a
  long long int get_mistake_no_center(long long int no_center_radius, 
                                      long long int mid){
    if (mid - no_center_radius <= 0 || mid + no_center_radius >= str_len - 1){
      return 0;
    }
    if (mid - no_center_radius == 1 || mid + no_center_radius == str_len - 2){
      return 1;
    }
    long long int max_addition_len = min(mid - no_center_radius - 1, str_len - (mid + no_center_radius) - 2);
    return 1 + get_same_len_no_center(mid - no_center_radius - 1 - max_addition_len, 
                            mid - no_center_radius - 1, max_addition_len, 0, mid);


  }


  public:
  Palindrome(string input){
    str_len = input.size();
    copy(input.begin(), input.end(), back_inserter(chars));
    copy(input.begin(), input.end(), back_inserter(chars_rev));
    reverse(chars_rev.begin(), chars_rev.end());

    N = str_len * 8;
    M = 100 * 10 * N * log(5*N);
    p = get_prime(M); 
    r.push_back(1);
    r_rev.push_back(1);
    a.push_back(0);
    a_rev.push_back(0);
    

    for (long long int i = 1; i <= str_len; i++)
    {
      r.push_back((r[i - 1] * 256) % p);
      a.push_back((a[i - 1] * 256 + chars[i - 1]) % p);

      r_rev.push_back((r_rev[i - 1] * 256) % p);
      a_rev.push_back((a_rev[i - 1] * 256 + chars_rev[i - 1]) % p);

    }

    for (long long int i = 0; i < str_len; i++){
    
      long long int max_radius_no_center = min(i, str_len - i -1);
      long long int max_radius_has_center = min(i, str_len - i);


      long long int no_center_radius = get_longest_palin_no_center(i - max_radius_no_center, i, max_radius_no_center, 0);
      long long int has_center_radius = get_longest_palin_has_center(i - max_radius_has_center, i, max_radius_has_center, 0);

      long long int no_center_mistake_radius = get_mistake_no_center(no_center_radius, i);
      long long int has_center_mistake_radius = get_mistake_has_center(has_center_radius, i);

      if (no_center_mistake_radius > 0 && 2 * (no_center_mistake_radius + no_center_radius) + 1 > mistake_len_best){
        mistake_len_best = 2 * (no_center_mistake_radius + no_center_radius) + 1;
        mistake_index = i - (no_center_mistake_radius + no_center_radius);
      }
      
      if (has_center_mistake_radius > 0 && 2 * (has_center_mistake_radius + has_center_radius) > mistake_len_best){
        mistake_len_best = 2 * (has_center_mistake_radius + has_center_radius);
        mistake_index = i - (has_center_mistake_radius + has_center_radius);
      }
   

      long long int cur_max_len;
      long long int cur_max_index;
      if (no_center_radius >= has_center_radius){
        cur_max_len = no_center_radius * 2 + 1;
        cur_max_index = i - no_center_radius;
      } else {
        cur_max_len = has_center_radius * 2;
        cur_max_index = i - has_center_radius;
      }
      if (cur_max_len > max_len){
        max_len = cur_max_len;
        max_index = cur_max_index;
      }
      // cout << "i: " << i << " ";
      // cout << " no center: ";
      // cout << no_center_radius;
      // cout << " mistake: ";
      // cout << no_center_mistake_radius;
      // cout << " has center: ";
      // cout << has_center_radius;
      // cout << " mistake: ";
      // cout << has_center_mistake_radius;
      // cout << "  max_len : " << max_len << " max index: " << max_index << " mistake_len : " << mistake_len_best << " mistake_index: " << mistake_index;
      // cout << endl;
     
    }

    string resultOne;
    string resultTwo;
    for (int i = 0; i < max_len/2; i ++){
      resultOne.push_back(chars[max_index + i]);
      resultTwo.push_back(chars[max_index + max_len - 1 - i]);
    }
    if (resultOne.compare(resultTwo) != 0){
      max_index = -1;
      max_len = -1;
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
