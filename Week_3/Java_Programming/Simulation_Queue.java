import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Simulation_Queue {
    public static void main(String[] args) {
        Queue<Integer> queue = new LinkedList<>();
        Scanner sc = new Scanner(System.in);

        while(sc.hasNextLine()){
            String cmd = sc.nextLine();
            String[] parts = cmd.split(" ");
            if(parts[0].equals("PUSH")){
                int data = Integer.parseInt(parts[1]);
                queue.offer(data);
            }else if(parts[0].equals("POP")){
                try{
                    int data = queue.poll();
                    System.out.println(data);
                }catch(Exception ex){
                    System.out.println("NULL");
                }
            }else if(parts[0].equals("#")){
                break;
            }
        }
        sc.close();
    }
}
