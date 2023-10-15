public class MyThread extends Thread {

    private int p, id, M, N;
    private float[][] V;

    public MyThread(int id, int p, float[][] V, int M, int N) {
        this.id = id;
        this.p = p;
        this.V = V;
        this.M = M;
        this.N = N;
    }

    @Override
    public void run() {
        for (int i = id + 2; i < M + 2; i += p) {
            for (int j = 2; j < N + 2; j++) {
                float value = Main.calculateNewValue(i, j);
                V[i - 2][j-2] = value;
            }
        }
    }
}

