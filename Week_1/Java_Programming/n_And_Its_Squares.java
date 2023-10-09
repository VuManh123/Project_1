import java.util.Scanner;

public class n_And_Its_Squares {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        for(int i=1; i<=n; i++){
            System.out.print(i+" ");
            int tmp = (int)Math.pow(i,2);
            System.out.println(tmp);
        }
    }
}
