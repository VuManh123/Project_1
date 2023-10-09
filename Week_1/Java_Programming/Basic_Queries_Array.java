import java.util.Scanner;

public class Basic_Queries_Array {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int max = -1000;
        int min = 1000;
        int sum = 0;
        int[] array = new int[n];
        for(int i=0; i<n; i++){
            array[i] = sc.nextInt();
            sum += array[i];
            if(array[i] > max) max = array[i];
            if(array[i] < min) min = array[i];
        }
        String endArray = sc.nextLine();
        while(sc.hasNextLine()){
            int max1 = -1000;
            String Command = sc.nextLine();
            String[] parts = Command.split(" ");
            if(parts[0].equals("find-max")) System.out.println(max);
            else if(parts[0].equals("find-min")) System.out.println(min);
            else if(parts[0].equals("sum")) System.out.println(sum);
            else if(parts[0].equals("find-max-segment")){
                int a = Integer.parseInt(parts[1]);
                int b = Integer.parseInt(parts[2]);
                for(int i=a-1; i<b; i++){
                    if(array[i]>max1) max1 = array[i];
                }
                System.out.println(max1);
            }
            else if(parts[0].equals("*")) continue;
            else break;
        }
    }
}
