import java.util.Scanner;

public class Count_Words {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int words = 0;
        while (sc.hasNextLine()) {
            String str = sc.nextLine();
            str = str.trim();
            String[] parts = str.split("\\s+");
            if(str.isEmpty()){
                continue;
            }
            else{
                words += parts.length;
            }
        }
        System.out.println(words);
    }
}