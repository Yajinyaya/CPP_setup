import java.security.PrivilegedAction;
import java.util.*;

class ListNode {
  int value;
  ListNode next;

  ListNode(int value) {
    this.value = value;
  }
}

class MergeKSortedLists {

  public static ListNode merge(ListNode[] lists) {
    ListNode result = new ListNode(-1);
    ListNode current = result;
    PriorityQueue<ListNode> pq = new PriorityQueue<>(lists.length, (v1,v2)->(v1.value - v2.value));
    for (int i = 0; i < lists.length; i ++){
        pq.add(lists[i]);
    }
 
    while (true){
        if (pq.size() == 0){
            break;
        }
        ListNode popped = pq.poll();
        if (popped.next != null){
            pq.add(popped.next);
        }
        current.next = popped;
        current = current.next;
       
    }
    return result.next;
  }

  public static void main(String[] args) {
    ListNode l1 = new ListNode(2);
    l1.next = new ListNode(6);
    l1.next.next = new ListNode(8);

    ListNode l2 = new ListNode(3);
    l2.next = new ListNode(6);
    l2.next.next = new ListNode(7);

    ListNode l3 = new ListNode(1);
    l3.next = new ListNode(3);
    l3.next.next = new ListNode(4);

    ListNode result = MergeKSortedLists.merge(new ListNode[] { l1, l2, l3 });
    System.out.print("Here are the elements form the merged list: ");
    while (result != null) {
      System.out.print(result.value + " ");
      result = result.next;
    }
  }
}
