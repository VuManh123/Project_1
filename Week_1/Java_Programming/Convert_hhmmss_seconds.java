import java.util.Scanner;

public class Convert_hhmmss_seconds {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String time = sc.nextLine();
        String[] parts = time.split(":");
        if(parts.length != 3 || parts[2].length() != 2 || parts[1].length() != 2){
            System.out.println("INCORRECT");
            return;
        }
        int[] array = new int[parts.length];

        for(int i=0; i< parts.length; i++){
            array[i] = Integer.parseInt(parts[i]);
            if(array[0]>24 || array[1]>=60 || array[2]>60){
                System.out.println("INCORRECT");
                return;
            }
        }
        int seconds = array[0]*3600 + array[1]*60 +array[2];
        System.out.println(seconds);
    }
}
