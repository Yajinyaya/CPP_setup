using namespace std;
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <math.h>

int is_prime(long long int input){
  if (input & 1 == 0){
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
long long int get_prime(long long int max){
  while (1){
    long long int rand_num = urand() % max;
    if (is_prime(rand_num)){
      return rand_num;
    }
  }
  return 0;
}
int hash_equal(vector<char> &chars, vector<long long int> &r, vector<long long int> &a,
              long long int i1, long long int i2, long lon){
  
}
//4 4 1213
int main(int argc, char *argv[]) {
  string input;
  getline(cin, input);
  long long int str_len = input.length;
  vector<char> chars(input.begin(), input.end());
  vector<long long int> r(str_len, 0);
  vector<long long int> a(str_len, 0);

  vector<long long int> start_indexes(str_len, 0);

  vector<long long int> lens(str_len, 0);

  long long int N = str_len * 8;
  long long int M = 10 * N * log(5N);
  vector<long long int> primes;
  for (int i = 0; i < 10; i++){
    
  }
    r[0] = 1;
  a[0] = 0;
  for (long long int i = 1; i < str_len; i++)
  {
    r[i] = (r[i - 1] * 256) % p;
    a[i] = (a[i - 1] * 256 + chars[i - 1]) % p;
  }



  for (auto c :first_line){
    if (c == ' '){
      int val = std::stoi(word, nullptr, 0);
      if (len == 0){
        len = val;
      } else {
        num_op = val;
      }

      word = "";

    } else {
      word = word + c;
    }
  }
  num_op = std::stoi(word, nullptr, 0);
  first_line = "";
  for (int i = 0; i < num_op; i++)
  {
    std::getline(std::cin, first_line);
    ops.push_back(stoi(first_line, nullptr, 0));
    first_line = "";
  }
  root = new TreeNode(0);
  root->index_offset = 0;
  map.push_back(root);
  for (int i = 1; i < len; i ++){
    map.push_back(insert(root, i));
    root = root->right;
  }

  for (int i = 0; i < num_op; i++){
    std::cout << blockswap(map, ops[i], len) << std::endl;
  }
}
