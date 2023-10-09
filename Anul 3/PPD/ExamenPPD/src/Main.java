import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class Main {
    private int R=5;
    private int W=3;

    public static void main(String[] args)  {
        Utils.fisGenerator();
        int nrFisiere = new File("./input/").list().length;

        int p1 = 5;
        int p2 = 3;

        Queue termsQueue = new Queue();
        List<Thread> threads = new ArrayList<>();
        ConsultatieMedicala cm = new ConsultatieMedicala(new Queue());
        Deparazitare d = new Deparazitare(new Queue());
        Toaletare t = new Toaletare(new Queue());

        int intreg = nrFisiere / p1;
        int rest = nrFisiere % p1;
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
            threads.add(new MyThreadReader(files, termsQueue, p2));
        }

        for (int i = 0; i < p2; i++) {
            threads.add(new MyThreadWorker(termsQueue, cm, d, t));
        }

        threads.forEach(Thread::start);

        threads.forEach(thread -> {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        long endTime = System.nanoTime();
        System.out.println((double) (endTime - startTime) / 1E6);

        System.out.println(cm.termsQueue.values);
        System.out.println(d.termsQueue.values);
        System.out.println(t.termsQueue.values);
    }
}
