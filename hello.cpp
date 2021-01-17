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

class ReverseSubList {
 public:
  static ListNode *reverse(ListNode *head, int p, int q) {
    // TODO: Write your code here
    if (p == q){
        return head;
    }
    ListNode *prev;
    ListNode *cur;
    
    int count = 1;
    while (count != p){
        ++count;
        prev = cur;
        cur = cur->next;
        
    }

    ListNode *next = nullptr;
    ListNode *start;
    ListNode *subStart;

    start = prev;
    substart = cur;
    prev = nullptr;
    cur = nullptr;

    while (count != q+1){
        ++count;
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

  }
};

int main(int argc, char *argv[]) {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);

  ListNode *result = ReverseSubList::reverse(head, 2, 4);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->value << " ";
    result = result->next;
  }
}
