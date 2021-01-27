using namespace std;

#include <iostream>
#include <queue>

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

class LevelOrderTraversal {
 public:
  static vector<vector<int>> traverse(TreeNode *root) {
    vector<vector<int>> result;
    if (root == nullptr){
        return result;
    }
    queue<TreeNode *> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        vector<int> currentLevel;
        for (int i = 0; i < size; i++){
            TreeNode *currentNode = q.front();
            q.pop();
            currentLevel.push_back(q->val);
            if (currentNode->left != nullptr){
                q.push(currentNode->left);
            }
            if (currentNode->right != nullptr){
                q.push(currentNode->right);
            }
        }
        result.push_back(currentLevel);
    }
    return result;
  }
};

int main(int argc, char *argv[]) {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  vector<vector<int>> result = LevelOrderTraversal::traverse(root);
  cout << "Level order traversal: ";
  for (auto vec : result) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  }
}
