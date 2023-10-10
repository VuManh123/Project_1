import java.util.*;
public class Sudoku_Solution {

    public static void main(String[] args) {
        int[][] input = new int[9][9];
        Scanner sc = new Scanner(System.in);
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                input[i][j] = sc.nextInt();
            }
        }
        int count = Solutions(input);
        System.out.println(count);
    }
    private static int[] findEmpty(int[][] board){
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j]==0)
                    return new int[]{i, j};
            }
        }
        return null;
    }
    private static int Solutions(int[][] board){
        int[] emptyCell = findEmpty(board);

        if(emptyCell == null){
            return 1;
        }
        int row = emptyCell[0];
        int col = emptyCell[1];
        int solutions = 0;

        for(int num=1; num<=9; num++){
            if(isValidMove(board, row, col, num)){
                board[row][col] = num;
                solutions += Solutions(board);
                board[row][col] = 0;
            }
        }
        return solutions;
    }
    private static boolean isValidMove(int[][] board, int row, int col, int num){
        for(int i=0; i<9; i++){
            if(board[row][i] == num || board[i][col] == num){
                return false;
            }
        }

        int startRow = row - row%3;
        int startCol = col - col%3;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i+startRow][j+startCol] == num){
                    return false;
                }
            }
        }
        return true;
    }
}
