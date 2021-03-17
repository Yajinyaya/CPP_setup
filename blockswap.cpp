#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <math.h>

class TreeNode {
 public:
  long long int index_offset = 0;
  long long int real_val = 0;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
  TreeNode(long long int x) {
    real_val = x;
    left = right = parent = nullptr;
  }
};

TreeNode *insert(TreeNode *node,long long int val){
  
  if (node->index_offset < val){
    if (node->right == nullptr){
      TreeNode *new_node = new TreeNode(val);
      node->right = new_node;
      new_node->index_offset = 1;
      new_node->parent = node;
      return new_node;
    } else {
      return insert(node->right, val);
    }
  } else {
    if (node->left == nullptr){
      TreeNode *new_node = new TreeNode(val);
      node->left = new_node;
      new_node->index_offset = 1;
      new_node->parent = node;
      return new_node;
    } else{
      return insert(node->left, val);
    }
  }
  
}

void rotate_right(TreeNode *parent, TreeNode *child){
  long long int new_parent_index_offset = child->index_offset + parent->index_offset;
  long long int orig_child_offset = child->index_offset;
  TreeNode *grandparent = parent->parent;
  child->index_offset = new_parent_index_offset;
  parent->index_offset -= new_parent_index_offset;
  child->parent = grandparent;
  if (child->right != nullptr){
    child->right->parent = parent;
    child->right->index_offset += orig_child_offset;
  }
  parent->left = child->right;
  parent->parent = child;
  child->right = parent;
  if (grandparent != nullptr){
    if (grandparent->left == parent){
      grandparent->left = child;
    } else {
      grandparent->right = child;
    }
  }
}
void rotate_left(TreeNode *parent, TreeNode *child){
  long long int new_parent_index_offset = child->index_offset + parent->index_offset;
  long long int orig_child_offset = child->index_offset;

  TreeNode *grandparent = parent->parent;
  child->index_offset = new_parent_index_offset;
  parent->index_offset -= new_parent_index_offset;
  child->parent = grandparent;
  if (child->left != nullptr){
    child->left->parent = parent;
    child->left->index_offset += orig_child_offset;
  }
  parent->right = child->left;
  parent->parent = child;
  child->left = parent;
  if (grandparent != nullptr){
    if (grandparent->left == parent){
      grandparent->left = child;
    } else {
      grandparent->right = child;
    }
  }
}
void zig(TreeNode *root, TreeNode *child){
  if (child == root->left){
    rotate_right(root, child);
  } else {
    rotate_left(root, child);
  }
}
void zig_zag(TreeNode *grandparent, TreeNode* grandchild){
  if (grandchild == grandchild->parent->right){
    rotate_left(grandchild->parent, grandchild);
    rotate_right(grandparent, grandchild);
  } else {
    rotate_right(grandchild->parent, grandchild);
    rotate_left(grandparent, grandchild);
  }

}
void zig_zig(TreeNode *grandparent,TreeNode *parent, TreeNode *grandchild){
  if (grandchild == parent->left){
    rotate_right(grandparent, parent);
    rotate_right(parent, grandchild);
  } else {
    rotate_left(grandparent, parent);
    rotate_left(parent, grandchild);
  }
}


TreeNode *splay(TreeNode *node){
  if (node->parent == nullptr){
    return node;
  } 
  if (node->parent->parent == nullptr){
    zig(node->parent, node);
    return node;
  } else{
    TreeNode *grandparent = node->parent->parent;
    TreeNode *parent = node->parent;
    if ((grandparent->right == parent && parent->right == node) 
    ||  (grandparent->left == parent && parent->left == node)){
      zig_zig(grandparent, parent, node);
      return splay(node);
    } else{
      zig_zag(grandparent, node);
      return splay(node);
    } 

  }
}
int blockswap(std::vector<TreeNode *> &map, int val, int len){
  TreeNode *target = map[val];
  int result = 0;
  if (target == nullptr){
    std::cout << "find failed" << std::endl;
    return -1;
  } 
  target = splay(target);
  result = target->index_offset;
  long long int orig_root_offset = target->index_offset;
  target->index_offset = target->index_offset + (len - result - result - 1);
  long long int root_dif = target->index_offset - orig_root_offset;
  TreeNode *temp = target->left;
  target->left = target->right;
  if (target->left != nullptr){
    target->left->index_offset -= (result + 1);
    target->left->index_offset -= root_dif;
  }
  target->right = temp;
  if (target->right != nullptr){
    target->right->index_offset += (len - result);
    target->right->index_offset -= root_dif;
  }
  return result;
}

//4 4 1213

int main(int argc, char *argv[]) {
  std::string first_line;
  std::getline(std::cin, first_line);
  int len = 0;
  int num_op = 0;
  TreeNode *root;
  std::vector<TreeNode *> map;
  std::vector<int> input;
  std::vector<int> ops;
  std::string word = "";
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
