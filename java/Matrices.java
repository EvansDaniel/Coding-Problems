/**
 * Created by daniel on 6/20/16.
 */
public class Matrices {

    int[][] multiplySquareMatrices(int[][] A, int[][] B) {
        int n = A.length;
        int[][] C = new int[n][n];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    C[i][j] += A[i][k] * B[k][j];

        return C;
    }

}
