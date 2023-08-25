import java.util.*;

public class BFS
{
    private final String information;
    public Boolean goalReached;

    public BFS(String information){
        this.information = information;
        goalReached = false;
    }

    public void printGrid(char[][] grid){
        if(!goalReached)
            System.out.println("No Path");
        else {
            StringBuilder sb = new StringBuilder();
            for (char[] rowGrid : grid)
                sb.append(new String(rowGrid)).append('\n');
            System.out.println(sb);
        }
    }

    public char[][] performBFS()
    {
        Scanner scanner = new Scanner(information);
        int row = scanner.nextInt();
        int col = scanner.nextInt();
        scanner.nextLine();

        char[][] grid = new char[row][col];
        boolean[][] visited = new boolean[row][col];
        Deque<Integer> queue = new ArrayDeque<>();
        int[] parent = new int[row * col];
        Arrays.fill(parent, -1);

        int start = -1, goal = -1;

        for (int i = 0; i < row; i++) {
            String s = scanner.nextLine();
            for (int j = 0; j < col; j++) {
                grid[i][j] = s.charAt(j);
                if (grid[i][j] == 'S')
                    start = i * col + j;
                else if (grid[i][j] == 'G')
                    goal = i * col + j;
            }
        }

        int[] rowDisp = {1, 0, -1, 0}; // DLUR
        int[] colDisp = {0, -1, 0, 1}; // DLUR

        queue.add(start);
        visited[start / col][start % col] = true;

        while (!queue.isEmpty()) {
            int curr = queue.poll();

            int r = curr / col;
            int c = curr % col;

            if (curr == goal) {
                goalReached = true;
                // Print the path
                while (curr != start) {
                    int x = curr / col;
                    int y = curr % col;
                    grid[x][y] = grid[x][y] == 'G' ? 'G' : '*';
                    curr = parent[curr];
                }
                break;
            }

            for (int i = 0; i < 4; i++) {
                int newRow = r + rowDisp[i];
                int newCol = c + colDisp[i];
                if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col &&
                        grid[newRow][newCol] != 'X' && !visited[newRow][newCol]) {
                    int newIndex = newRow * col + newCol;
                    queue.add(newIndex);
                    visited[newRow][newCol] = true;
                    parent[newIndex] = curr;
                }
            }
        }

        return grid;
    }
}
