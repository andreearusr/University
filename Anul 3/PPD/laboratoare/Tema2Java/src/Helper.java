import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class Helper {

    //functie pentru generarea unei matrici noi
    public static void generateMatrix(int N, int M) {
        try {
            FileWriter myWriter = new FileWriter("inputMatrix.txt");
            Random random = new Random();
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    myWriter.write(random.nextInt(10) + " ");
                }
                myWriter.write("\n");
            }
            myWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //citire matrice initiala din fisier
    public static float[][] readMatrix(int N, int M) {
        float[][] returnMatrix = new float[M + 4][N + 4];
        try {
            int i = 2, j = 2;
            File myObj = new File("inputMatrix.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                String[] values = data.split(" ");
                for (String str : values) {
                    float value = Float.parseFloat(str);
                    returnMatrix[i][j] = value;
                    j += 1;
                }
                j = 2;
                i += 1;
            }
            myReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return returnMatrix;
    }
    //functie pentru verificarea egalitatii fisierelor -> calcul secvential si calcul paralel
    public static boolean checkEquality() {
        File outputSeq = new File("outputMatrixSequencial.txt");
        File outputPar = new File("outputMatrixParallel.txt");

        if (outputSeq.length() != outputPar.length())
            return false;

        Scanner f1scanner = new Scanner("outputMatrixSequencial.txt");
        Scanner f2scanner = new Scanner("outputMatrixParallel.txt");

        while (f1scanner.hasNextFloat())
            if (f1scanner.nextFloat() != f2scanner.nextFloat())
                return false;

        f1scanner.close();
        f2scanner.close();

        return true;
    }
}