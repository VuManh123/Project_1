import java.util.Scanner;

public class YYYY_MM_DD {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String date = sc.nextLine();
        String[] parts = date.split("-");
        if(parts.length != 3 || parts[2].length() != 2 || parts[1].length() != 2){
            System.out.println("INCORRECT");
            return;
        }
        int[] array = new int[parts.length];

        for(int i=0; i< parts.length; i++){
            array[i] = Integer.parseInt(parts[i]);
            if(array[1]>12 || array[2]>31){
                System.out.println("INCORRECT");
                return;
            }
        }
        for(int i=0; i< parts.length; i++){
            System.out.print(array[i]+" ");
        }
    }
}
