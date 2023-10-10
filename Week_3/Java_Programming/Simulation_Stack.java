import java.util.Scanner;
import java.util.Stack;

public class Simulation_Stack {
    public static void main(String[] args) {
        Stack<Integer> stack = new Stack<>();
        Scanner sc = new Scanner(System.in);

        while(sc.hasNextLine()){
            String cmd = sc.nextLine();
            String[] parts = cmd.split(" ");
            if(parts[0].equals("PUSH")){
                int data = Integer.parseInt(parts[1]);
                stack.push(data);
            }else if(parts[0].equals("POP")){
                try{
                    int data = stack.pop();
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
