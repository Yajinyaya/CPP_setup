using namespace std;

#include <iostream>
#include <vector>

class TreeNode {
 public:
  int val = 0;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x) {
    val = x;
    left = right = nullptr;
  }
};

class FindAllTreePaths {
 public:
  static vector<vector<int>> findPaths(TreeNode *root, int sum) {
    vector<vector<int>> allPaths;
    // TODO: Write your code here
    vector<int> pathNodes;
    recursiveHelper(root, pathNode, sum, allPaths);
    
    return allPaths;
  }
  static void recursiveHelper(TreeNode *root, vector<int> &pathNodes, int sum, vector<vector<int>> allPaths){
      if (root == nullptr){
          return;
      }
      pathNodes.push_back(root->val);
      if (root->val == sum && root->left == nullptr && root->right == nullptr){
          allPaths.push_back(pathNodes);
      } else {
          recursiveHelper(root->left, pathNodes, sum - root->val, allPaths);
          recursiveHelper(root->right, pathNodes, sum - root->val, allPaths);
      }
      pathNodes.pop_back();
  }
};

int main(int argc, char *argv[]) {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(4);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  int sum = 23;
  vector<vector<int>> result = FindAllTreePaths::findPaths(root, sum);
  cout << "Tree paths with sum " << sum << ": " << endl;
  for (auto vec : result) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  }
}
