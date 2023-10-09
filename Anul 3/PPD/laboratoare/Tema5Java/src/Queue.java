import java.util.ArrayList;
import java.util.List;

public class Queue {
    List<Term> values;
    int MAXvalue;

    public Queue(int MAXvalue) {
        this.MAXvalue = MAXvalue;
        this.values = new ArrayList<>();
    }

    synchronized void push(Term term) throws InterruptedException {
        while(values.size() == MAXvalue) {
            wait();
        }

        values.add(term);
        notifyAll();
    }

    synchronized Term pop() throws InterruptedException {
        while(values.isEmpty()) {
            wait();
        }

        Term object = values.remove(0);
        notifyAll();
        return object;
    }

    boolean isEmpty() {
        return values.isEmpty();
    }
}