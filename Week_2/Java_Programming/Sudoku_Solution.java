import java.util.*;
public class Sudoku_Solution {

    public static void main(String[] args) {
        int[][] input = new int[9][9];
        Scanner sc = new Scanner(System.in);
        for(int i=0; i<9; i++){
            for(int j=0; i<9; j++){
                input[i][j] = sc.nextInt();
            }
        }
        int count = Solutions(input);
        System.out.println(count);
    }
    private static int Solutions(int[][] sudoku){

    }
}
