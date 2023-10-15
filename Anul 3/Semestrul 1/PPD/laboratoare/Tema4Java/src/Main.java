import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;

public class Main {

    private static Queue termsQueue = new Queue();
    private static LinkedList invariant = new LinkedList();

    public static void sequencial(String[] args){
        int polinCount = new File("./" + args[0] + "/").list().length;

        long startTime = System.nanoTime();
        for (int i = 1; i <= polinCount; i++) {
            try {
                File file = new File("./" + args[0] + "/" + i + ".txt");
                Scanner reader = new Scanner(file);
                while (reader.hasNextLine()) {
                    String line = reader.nextLine();
                    String[] words = line.split(" ");
                    termsQueue.push(new Term(Integer.parseInt(words[0]), Integer.parseInt(words[1])));
                }

                Term term;
                while (!termsQueue.isEmpty()) {
                    term = termsQueue.pop();
                    invariant.addTerm(new Node(term));
                }

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        try {
            StringBuilder output = new StringBuilder();
            FileWriter myWriter = new FileWriter("outputSeq.txt");
            for (Term term: invariant.asList()) {
                output.append(term.coefficient).append(" ").append(term.exponent).append("\n");
            }
            myWriter.write(output.toString());
            myWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        long endTime = System.nanoTime();
        System.out.println((double) (endTime - startTime) / 1E6);
    }

    public static void parallel(String[] args) {

        int polinCount = new File("./" + args[0] + "/").list().length;

        long startTime = System.nanoTime();
        for (int i = 1; i <= polinCount; i++) {
            try {
                File file = new File("./" + args[0] + "/" + i + ".txt");
                Scanner reader = new Scanner(file);
                while (reader.hasNextLine()) {
                    String line = reader.nextLine();
                    String[] words = line.split(" ");
                    termsQueue.push(new Term(Integer.parseInt(words[0]), Integer.parseInt(words[1])));
                }

                int p = Integer.parseInt(args[1]);
                MyThread[] threads = new MyThread[p];
                for (int j = 0; j < p; j++) {
                    MyThread thread = new MyThread(termsQueue, invariant);
                    thread.start();
                    threads[j] = thread;
                }

                for (MyThread thread: threads) {
                    try {
                        thread.join();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        try {
            StringBuilder output = new StringBuilder();
            FileWriter myWriter = new FileWriter("outputPar.txt");
            for (Term term: invariant.asList()) {
                output.append(term.coefficient).append(" ").append(term.exponent).append("\n");
            }
            myWriter.write(output.toString());
            myWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        long endTime = System.nanoTime();
        System.out.println((double) (endTime - startTime) / 1E6);
    }

    public static void main(String[] args) {
        //Helper.polynomialGenerator();

        if(Objects.equals(args[2], "seq")){
            sequencial(args);
            return;
        }

        parallel(args);
        if (!Helper.checkEquality())
            System.out.println("Rezultate diferite");
        else
            System.out.println("Rezultate identice");
    }
}
