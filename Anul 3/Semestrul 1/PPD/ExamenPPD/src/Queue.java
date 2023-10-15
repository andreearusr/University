import java.util.ArrayList;
import java.util.List;

public class Queue {
    List<Tichet> values;

    public Queue() {
        this.values = new ArrayList<>();
    }

    synchronized void push(Tichet term) {
        values.add(term);
        notifyAll();
    }

    synchronized Tichet pop() throws InterruptedException {
        while(values.isEmpty()) {
            wait();
        }
        Tichet object = values.remove(0);
        notifyAll();
        return object;
    }
}