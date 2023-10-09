import java.util.Scanner;

public class Count_Odd_EvenNumber {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int odd = 0;
        int even = 0;
        for(int i=0; i<n; i++){
            int tmp = sc.nextInt();
            if(tmp%2==0) odd+=1;
            else even+=1;
        }
        System.out.println(even+" "+odd);
    }
}
