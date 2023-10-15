import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.CyclicBarrier;

public class MyThreadReader extends Thread {
    private Queue termsQueue;
    List<String> files;
    private CyclicBarrier barrier;
    private int nrWorkers;

    public MyThreadReader(List<String> files, Queue termsQueue, CyclicBarrier barrier, int nrWorkers) {
        this.files = files;
        this.termsQueue = termsQueue;
        this.barrier = barrier;
        this.nrWorkers = nrWorkers;
    }

    @Override
    public void run() {
        try {
            for(String fileName: files){
                File file = new File(fileName);
                Scanner reader = new Scanner(file);
                while (reader.hasNextLine()) {
                    String line = reader.nextLine();
                    String[] words = line.split(" ");
                    termsQueue.push(new Term(Integer.parseInt(words[0]), Integer.parseInt(words[1])));
                }
            }

            barrier.await();
            for(int i = 0; i < nrWorkers; i ++)
                termsQueue.push(null);
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }
}