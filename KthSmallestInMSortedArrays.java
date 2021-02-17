// import java.util.*;

// class Node{
//     int elementIndex;
//     int arrayIndex;
//     Node(int elementIndex, int arrayIndex){
//         this.elementIndex = elementIndex;
//         this.arrayIndex = arrayIndex;
//     }
// }
// class KthSmallestInMSortedArrays {

//   public static int findKthSmallest(List<Integer[]> lists, int k) {
//     int count = 0;
//     PriorityQueue<Node> pq = new PriorityQueue<>((n1, n2)->lists.get(n1.arrayIndex)[n1.elementIndex] - lists.get(n2.arrayIndex)[n2.elementIndex]);
//     for (int i = 0 ; i < lists.size(); i ++){
//         pq.add(new Node(0,i));
//     }

//     int count = 0;
//     int result = 0;
//     while (!pq.isEmpty()){
//         Node node = pq.poll();
//         result = lists.get(node.arrayIndex)[node.elementIndex];
//         if (++count == k){
//             break;
//         }
//         node.elementIndex++;
//         if (lists.get(node.arrayIndex).length >node.elementIndex){
//             pq.add(node);
//         }
//     }
//     return result;
//   }


//   public static void main(String[] args) {
//     Integer[] l1 = new Integer[] { 2, 6, 8 };
//     Integer[] l2 = new Integer[] { 3, 6, 7 };
//     Integer[] l3 = new Integer[] { 1, 3, 4 };
//     List<Integer[]> lists = new ArrayList<Integer[]>();
//     lists.add(l1);
//     lists.add(l2);
//     lists.add(l3);
//     int result = KthSmallestInMSortedArrays.findKthSmallest(lists, 5);
//     System.out.print("Kth smallest number is: " + result);
//   }
// }
