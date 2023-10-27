import java.util.Scanner;

public class AllPairShortestPaths {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); //nodes
        int m = sc.nextInt(); //edges

        int[][] graph = new int[n][n]; //Trong so canh

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(i==j)
                    graph[i][j] = 0;
                else graph[i][j] = Integer.MAX_VALUE;
            }
        }
        for(int i=0; i<m; i++){
            int u = sc.nextInt() - 1;
            int v = sc.nextInt() - 1;
            int w = sc.nextInt();
            graph[u][v] = w;
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                for(int k=0; k<n; k++){
                    if(graph[j][i] != Integer.MAX_VALUE && graph[i][k] != Integer.MAX_VALUE){
                        graph[j][k] = Math.min(graph[j][k], graph[j][i] + graph[i][k]);
                    }
                }
            }
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                System.out.print(graph[i][j] + " ");
            }
            System.out.println();
        }
        sc.close();
    }
}
