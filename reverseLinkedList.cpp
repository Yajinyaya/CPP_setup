using namespace std;

#include <iostream>

class ListNode {
 public:
  int value = 0;
  ListNode *next;

  ListNode(int value) {
    this->value = value;
    next = nullptr;
  }
};

class ReverseLinkedList {
 public:
  static ListNode *reverse(ListNode *head) {
    // TODO: Write your code here
    ListNode *cur = head;
    ListNode *prev = nullptr;
    ListNode *next = nullptr;
    while(cur != nullptr){
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
  }
};