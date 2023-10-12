import java.util.Scanner;
import java.util.Stack;

public class isParenthesis {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String input = sc.nextLine();
        System.out.println(isParenthesis(input));
    }
    private static int isParenthesis(String input){
        Stack<Character> stack = new Stack<>();
        for(char c : input.toCharArray()){
            if(c == '(' || c == '{' || c=='['){
                stack.push(c);
            }else if(c == ')' || c==']' || c=='}'){
                if(stack.isEmpty())
                    return 0;
                char open = stack.pop();
                if((c == ')' && open != '(') || (c == '}' && open != '{') || (c==']' && open != '['))
                    return 0;
            }
        }
        if(stack.isEmpty()) return 1;
        else return 0;
    }
}
