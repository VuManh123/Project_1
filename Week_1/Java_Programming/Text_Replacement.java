import java.util.Scanner;

public class Text_Replacement {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String str = sc.nextLine();
        String strReplace = sc.nextLine();
        String input = sc.nextLine();
        String output = "";
        String[] parts = input.split(" ");

        for (int i = 0; i < parts.length; i++) {
            if (parts[i].equals(str)) {
                output += strReplace;
            } else {
                output += parts[i];
            }
            if (i < parts.length - 1) {
                output += " ";
            }
        }
        System.out.println(output);
    }
}
