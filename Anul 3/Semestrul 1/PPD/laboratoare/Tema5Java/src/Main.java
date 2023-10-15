import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.CyclicBarrier;

public class Main {


    public static void sequencial(String[] args){
        try {
            int polinCount = new File("./" + args[0] + "/").list().length;
            List<Term> termsQueue =  new ArrayList<>();
            TreeMap<Integer, Integer> invariant = new TreeMap<>();
            long startTime = System.nanoTime();

            for (int i = 1; i <= polinCount; i++) {
                try {
                    File file = new File("./" + args[0] + "/" + i + ".txt");
                    Scanner reader = new Scanner(file);
                    while (reader.hasNextLine()) {
                        String line = reader.nextLine();
                        String[] words = line.split(" ");
                        termsQueue.add(new Term(Integer.parseInt(words[0]), Integer.parseInt(words[1])));
                    }
                    reader.close();

                    Term term;
                    while (!termsQueue.isEmpty()) {
                        term = termsQueue.remove(0);
                        Integer value = invariant.putIfAbsent(term.exponent, term.coefficient);
                        if(value != null)
                            invariant.put(term.exponent, term.coefficient + value);
                        if(invariant.get(term.exponent) == 0)
                            invariant.remove(term.exponent);
                    }

                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            }

            Map<Integer, Integer> desc = new TreeMap<>(Collections.reverseOrder());
            desc.putAll(invariant);

            StringBuilder output = new StringBuilder();
            FileWriter myWriter = new FileWriter("outputSeq.txt");
            for(Map.Entry<Integer, Integer> entry : invariant.entrySet()){
                output.append(entry.getValue()).append(" ").append(entry.getKey()).append("\n");
            }


            myWriter.write(output.toString());
            myWriter.close();

            long endTime = System.nanoTime();
            System.out.println((double) (endTime - startTime) / 1E6);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void parallel(String[] args) {
        int polinCount = new File("./" + args[0] + "/").list().length;

        int p = Integer.parseInt(args[2]);
        int p1 = Integer.parseInt(args[3]);;
        int p2 = p - p1;
        int MAX = Integer.parseInt(args[4]);
        Queue termsQueue = new Queue(MAX);
        LinkedList invariant = new LinkedList();
        CyclicBarrier barrier = new CyclicBarrier(p1);
        List<Thread> threads = new ArrayList<>();

        int intreg = polinCount / p1;
        int rest = polinCount % p1;
        int index = 1;

        long startTime = System.nanoTime();
        for (int i = 0; i < p1; i++) {
            List<String> files = new ArrayList<>();

            int partialInt = intreg;
            if (rest > 0) {
                rest--;
                partialInt++;
            }
            for (int j = 0; j < partialInt; j++) {
                files.add("./input/" + index + ".txt");
                index++;
            }
            threads.add(new MyThreadReader(files, termsQueue, barrier, p2));
        }

        for (int i = 0; i < p - p1; i++) {
            threads.add(new MyThreadWorker(termsQueue, invariant));
        }

        threads.forEach(Thread::start);

        threads.forEach(thread -> {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });

        try {
            StringBuilder output = new StringBuilder();
            FileWriter myWriter = new FileWriter("outputPar.txt");
            for (Term term : invariant.asList()) {
                output.append(term.coefficient).append(" ").append(term.exponent).append("\n");
            }
            myWriter.write(output.toString());
            myWriter.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }

        long endTime = System.nanoTime();
        System.out.println((double) (endTime - startTime) / 1E6);
    }

    public static void main(String[] args) {
        //Helper.polynomialGenerator();

        if(Objects.equals(args[1], "seq")){
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
