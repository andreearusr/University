import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class MyThread extends Thread {

    private int p, id, M, N;
    private float[][] F;
    private CyclicBarrier barrier;

    public MyThread(CyclicBarrier barrier, int id, int p, float[][] F, int M, int N) {
        this.barrier = barrier;
        this.id = id;
        this.p = p;
        this.F = F;
        this.M = M;
        this.N = N;
    }

    @Override
    public void run() {
        //calculare de noi valori din matricea F
        List<Float> auxiliarArray = new ArrayList<>();
        for (int i = id + 2; i < M + 2; i += p) {
            for (int j = 2; j < N + 2; j++) {
                float value = Main.calculateNewValue(i, j);
                auxiliarArray.add(value);
            }
        }

        //asteptare toate thread-urile la bariera
        try {
            barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        //asignarea noilor valori in matricea F
        int index = 0;
        for (int i = id + 2; i < M + 2; i += p) {
            for (int j = 2; j < N + 2; j++) {
                F[i][j] = auxiliarArray.get(index);
                index++;
            }
        }
    }
}


