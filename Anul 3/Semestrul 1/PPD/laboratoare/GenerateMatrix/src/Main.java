import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Main {

    public static void main(String[] args) {
        generateMatrix(10000,10);
    }


    //functie pentru generarea unei matrici noi
    public static void generateMatrix(int N, int M) {
        try {
            FileWriter myWriter = new FileWriter("input.txt");
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

}
