import java.util.*;

public class BFS_NodesVisited{
    /*List danh sach can phai sap xep tu be den lon
    Dung Danh sach kep de bieu dien dinh ke
    Use queue*/
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); // nodes
        int m = sc.nextInt(); // edges

        List<List<Integer>> graph = new ArrayList<>();
        for(int i=0; i<n; i++){
            graph.add(new ArrayList<>());
        }

        for(int i=0; i<m; i++){
            int u = sc.nextInt();
            int v = sc.nextInt();
            graph.get(u-1).add(v);
            graph.get(v-1).add(u); // Them u vao danh sach ke cua v
        }

        List<Integer> visited = bfsGraph(graph, n);
        for(int node : visited){
            System.out.print(node + " ");
        }
    }

    private static List<Integer> bfsGraph(List<List<Integer>> graph, int n){
        List<Integer> visited = new ArrayList<>();
        Queue<Integer> queue = new LinkedList<>();
        boolean[] isVisited = new boolean[n];
        for(int i=0; i<n; i++){
            if(!isVisited[i]){
                queue.add(i);
                isVisited[i] = true;
            }

            while(!queue.isEmpty()){
                int node = queue.poll();
                visited.add(node + 1);
                List<Integer> adjacent = graph.get(node);
                Collections.sort(adjacent);

                for(int adj : adjacent){
                    if(!isVisited[adj - 1]){
                        queue.add(adj-1);
                        isVisited[adj-1] = true;
                    }
                }
            }
        }
        return visited;
    }
}