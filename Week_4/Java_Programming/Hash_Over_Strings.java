import java.util.Scanner;

public class Hash_Over_Strings {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        sc.nextLine();

        for (int i = 0; i < n; i++) {
            String input = sc.nextLine();
            char[] arr = input.toCharArray();
            int k = arr.length;
            long sum = 0;
            long powerOf256 = 1;

            for (int j = k - 1; j >= 0; j--) {
                sum = (sum + (arr[j] * powerOf256) % m) % m;
                powerOf256 = (powerOf256 * 256) % m;
            }

            System.out.println(sum);
        }
    }
}
