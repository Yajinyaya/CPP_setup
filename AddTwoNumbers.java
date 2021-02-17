// /**
//  * Definition for singly-linked list.
//  * public class ListNode {
//  *     int val;
//  *     ListNode next;
//  *     ListNode() {}
//  *     ListNode(int val) { this.val = val; }
//  *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
//  * }
//  */
// class Solution {
//     public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
//         int carry = 0;
//         ListNode result = null;
//         ListNode head =null;
        
//         while (l1 != null || l2 != null){
            
//             int val = carry;
            
//             if (l1 != null){
//                 val += l1.val;
//             }
//             if (l2 !=null){
//                 val += l2.val;
//             }
//             if (val >= 10){
//                 val -= 10;
//                 carry = 1;
//             } else {
//                 carry = 0;
//             }
            
//             if (result == null){
//                 result = new ListNode(val);
//                 head = result;
//             } else {
//                 result.next = new ListNode(val);
//                 result = result.next;
//             }
//             if (l1 != null){
//                 l1 = l1.next;
//             }
//             if (l2 != null){
//                 l2 = l2.next;
//             }
        
            
            
//         }
//         if (carry == 1){
//             result.next = new ListNode(1);
//         }
//         return head;
        
//     }
// }