import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class A {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n, m, k;
        n = scanner.nextInt();
        m = scanner.nextInt();
        k = scanner.nextInt();
        int[][] obj = new int[n][2];
        for (int i = 0; i < n; i++) {
            obj[i][1]= scanner.nextInt();
            obj[i][0] = i + 1;
        }
        scanner.close();
        int minobj = n/k;
        int[][] res = new int[k][minobj + 2];
        for (int i = 0; i < k; i++) {
            res[i][0] = 1;
        }
        int t = 0;
        for (int[] a : obj) {
            res[t][res[t][0]++] = a[0];
            t += 1;
            t %= k;
        }
        for (int i = 0; i < k; i++) {
            System.out.print(res[i][0] - 1);
            for (int j = 1; j < res[i][0]; j++) {
                System.out.print(" " + res[i][j]);
            }
            System.out.println();
        }
    }
}
