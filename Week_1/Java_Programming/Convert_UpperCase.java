import java.util.*;

@SuppressWarnings({"unchecked", "deprecation"})
public class Convert_UpperCase {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String str = scanner.nextLine();
            System.out.println(str.toUpperCase());
        }
    }
}