import java.util.*;

class TopologicalSort {
  public static List<Integer> sort(int vertices, int[][] edges) {
    List<Integer> sortedOrder = new ArrayList<>();
    
    HashMap<Integer, Integer> indegreeMap = new HashMap<>();
    HashMap<Integer, List<Integer>> myMap = new HashMap<>();

    for (int i = 0; i < vertices; i ++){
        indegreeMap.put(i, 0);
        myMap.put(i, new ArrayList<Integer>());
        
    }
    for (int i = 0; i < edges.length;i ++){
        myMap.get(edges[i][0]).add(edges[i][1]);
        indegreeMap.put(edges[i][1], indegreeMap.get(edges[i][1]+1));
    }

    Queue<Integer> sources = new LinkedList<>();
    for (Map.Entry<Integer,Integer> entry : indegreeMap.entrySet()){
        if (entry.getValue() == 0){
            sources.add(entry.getKey());
        }
    }

    while (!sources.isEmpty()){
        int currentVertex = sources.poll();
        sortedOrder.add(currentVertex);
        List<Integer> children = myMap.get(currentVertex);
        for (int child : children){
            indegreeMap.put(child, indegreeMap.get(child)-1);
            if (indegreeMap.get(child) == 0){
                sources.add(child);
            }
        }
    }
    
    if (sortedOrder.size() != vertices) // topological sort is not possible as the graph has a cycle
      return new ArrayList<>();
    return sortedOrder;
  }

  public static void main(String[] args) {
    List<Integer> result = TopologicalSort.sort(4,
        new int[][] { new int[] { 3, 2 }, new int[] { 3, 0 }, new int[] { 2, 0 }, new int[] { 2, 1 } });
    System.out.println(result);

    result = TopologicalSort.sort(5, new int[][] { new int[] { 4, 2 }, new int[] { 4, 3 }, new int[] { 2, 0 },
        new int[] { 2, 1 }, new int[] { 3, 1 } });
    System.out.println(result);

    result = TopologicalSort.sort(7, new int[][] { new int[] { 6, 4 }, new int[] { 6, 2 }, new int[] { 5, 3 },
        new int[] { 5, 4 }, new int[] { 3, 0 }, new int[] { 3, 1 }, new int[] { 3, 2 }, new int[] { 4, 1 } });
    System.out.println(result);
  }
}