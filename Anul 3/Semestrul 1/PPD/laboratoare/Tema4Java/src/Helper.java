import java.io.*;
import java.util.Random;
import java.util.Scanner;

public class Helper {

    public static void polynomialGenerator() {
        int polynomialsCount;
        int maxExponent;
        int termsCount;
        Random random = new Random();

        Scanner sc = new Scanner(System.in);
        System.out.print("nr polinoame: ");
        polynomialsCount = sc.nextInt();
        System.out.print("max exponent: ");
        maxExponent = sc.nextInt();
        System.out.print("nr monoame: ");
        termsCount = sc.nextInt();

        for (int i = 1; i <= polynomialsCount; i++) {
            try {
                File file = new File("./input/" + i + ".txt");
                file.createNewFile();
                FileOutputStream fos = new FileOutputStream(file);
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));

                int count = termsCount;
                int[] exponents = new int[count];
                int[] coefficients = new int[count];

                int cur = 0;
                int remaining = maxExponent;
                for (int j = 1; j <= maxExponent && count > 0; j++) {
                    double probability = random.nextDouble();
                    if (probability < ((double) count) / (double) remaining) {
                        exponents[cur] = j;
                        coefficients[cur] = random.nextInt(100) + 1;
                        count--;
                        cur++;
                    }
                    remaining--;
                }

                for (int j = 0; j < termsCount; j++) {
                    bw.write(coefficients[j] + " " + exponents[j]);
                    if (j < termsCount - 1)
                        bw.newLine();
                }
                bw.close();
                fos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static boolean checkEquality() {
        File outputSeq = new File("outputSeq.txt");
        File outputPar = new File("outputPar.txt");

        if (outputSeq.length() != outputPar.length())
            return false;

        Scanner f1scanner = new Scanner("outputSeq.txt");
        Scanner f2scanner = new Scanner("outputPar.txt");

        while (f1scanner.hasNextInt())
            if (f1scanner.hasNextInt() != f2scanner.hasNextInt())
                return false;

        f1scanner.close();
        f2scanner.close();

        return true;
    }
}
