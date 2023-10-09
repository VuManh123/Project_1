import java.util.Scanner;

public class Giai_PTbac2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        int c = sc.nextInt();
        int delta = (int) Math.pow(b, 2) - 4 * a * c;
        if (delta < 0) {
            System.out.println("NO SOLUTION");
        } else if (delta == 0) {
            double x0 = -b / (2.0 * a);
            System.out.printf("%.2f", x0);
        } else {
            double x1 = (-b + Math.sqrt(delta)) / (2.0 * a);
            double x2 = (-b - Math.sqrt(delta)) / (2.0 * a);
            if (x1 < x2) {
                System.out.printf("%.2f %.2f", x1, x2);
            } else {
                System.out.printf("%.2f %.2f", x2, x1);
            }
        }
    }
}
