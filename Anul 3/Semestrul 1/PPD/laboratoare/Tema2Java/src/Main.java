import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.concurrent.CyclicBarrier;

public class Main {

    //private static int p = 4; //numarul de thread-uri
    private static int N = 10000, M = 10, m = 5, n = 5; //dimensiuni matrice F nebordata si V + dimensiuni matrice W
    private static float[][] F; //matricea initiala + bordata,
    private static float[][] W = new float[m][n]; //matricea de filtrare
    private static CyclicBarrier barrier;

    //calculare noua valoare din matrice, folosind matricea de filtrare
    public static float calculateNewValue(int i, int j) {
        float newValue = 0;
        int poz = n / 2;
        for (int ii = 0; ii < m; ii++) {
            for (int jj = 0; jj < n; jj++) {
                newValue += W[ii][jj] * F[i - poz + ii][j - poz + jj];
            }
        }

        return newValue;
    }

    public static void main(String[] args) throws IOException {
        //Helper.generateMatrix(N, M);
        int p = Integer.parseInt(args[0]);
        float wVal = (float) 1 / 9;

        //initializarea matricii W
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                W[i][j] = wVal;
            }

        //citire matrice F din fisier
        F = Helper.readMatrix(N, M);

        //bordarea matricii
        F[0][0] = F[0][1] = F[1][0] = F[1][1] = F[2][2];
        F[M + 3][1] = F[M + 2][1] = F[M + 3][0] = F[M + 2][0] = F[M + 1][2];
        F[0][N + 3] = F[0][N + 2] = F[1][N + 3] = F[1][N + 2] = F[2][N + 1];
        F[M + 3][N + 3] = F[M + 3][N + 2] = F[M + 2][N + 3] = F[M + 2][N + 2] = F[M + 1][N + 1];

        for (int i = 2; i < M + 2; i++) {
            F[i][0] = F[i][1] = F[i][2];
            F[i][N + 2] = F[i][N + 3] = F[i][N + 1];
        }
        for (int j = 2; j < N + 2; j++) {
            F[0][j] = F[1][j] = F[2][j];
            F[M + 2][j] = F[M + 3][j] = F[M + 1][j];
        }

       /* BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("seq / par ?");
        String type = reader.readLine();*/
        String type = args[1];
        if (type.equals("seq")) {
            //secvential
            FileWriter outputSeq = new FileWriter("outputMatrixSequencial.txt");
            long startTime = System.nanoTime();

            for (int i = 2; i < M + 2; i++) {
                for (int j = 2; j < N + 2; j++) {
                    float value = calculateNewValue(i, j);
                    outputSeq.write(value + " ");
                }
                outputSeq.write("\n");
            }
            outputSeq.close();

            long endTime = System.nanoTime();
            System.out.println((double) (endTime - startTime) / 1E6);
        } else {
            //paralel
            long startTime = System.nanoTime();

            barrier = new CyclicBarrier(p);
            MyThread[] threads = new MyThread[p];
            for (int i = 0; i < p; i++) {
                threads[i] = new MyThread(barrier, i, p, F, M, N);
                threads[i].start();
            }

            for (int i = 0; i < p; i++) {
                try {
                    threads[i].join();
                } catch (InterruptedException exception) {
                    System.out.println(exception);
                }
            }
            long endTime = System.nanoTime();

            FileWriter outputPar = new FileWriter("outputMatrixParallel.txt");
            for (int i = 2; i < M + 2; i++) {
                for (int j = 2; j < N + 2; j++)
                    outputPar.write(F[i][j] + " ");
                outputPar.write("\n");
            }

            outputPar.close();
            System.out.println((double) (endTime - startTime) / 1E6);
        }

        if (type.equals("par")) {
            if (!Helper.checkEquality())
                System.out.println("Rezultate diferite");
            else
                System.out.println("Rezultate identice");
        }
    }
}