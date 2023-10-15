public class MyThreadWorker extends Thread {

    private Queue termsQueue;
    private LinkedList invariant;

    public MyThreadWorker(Queue termsQueue, LinkedList invariant) {
        this.termsQueue = termsQueue;
        this.invariant = invariant;
    }

    @Override
    public void run() {
        try {
            Term term = termsQueue.pop();

            while (term != null) {
                invariant.addTerm(new Node(term));
                term = termsQueue.pop();
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }
}
