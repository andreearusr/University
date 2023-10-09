public class MyThread extends Thread {

    private Queue termsQueue;
    private LinkedList invariant;

    public MyThread(Queue termsQueue, LinkedList invariant) {
        this.termsQueue = termsQueue;
        this.invariant = invariant;
    }

    @Override
    public void run() {
        Term term;
        term = termsQueue.pop();
        if (term == null)
            return;

        while (term != null) {
                invariant.addTerm(new Node(term));
                term = termsQueue.pop();
        }
    }
}
