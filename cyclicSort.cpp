using namespace std;

#include <iostream>
#include <vector>

class CyclicSort {
 public:
  static void sort(vector<int> &nums) {
      int index = 0;
      while (index < nums.size()){
          int trueIndex = nums[index] - 1;
          if (trueIndex != index){
              swap(nums, index, trueIndex);
          }else{
              ++index;
          }
      }
      
  }
  private:
    static void swap(vector<int> &nums, int i, int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
};