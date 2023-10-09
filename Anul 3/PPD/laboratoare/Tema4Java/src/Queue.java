import java.util.ArrayList;
import java.util.List;

public class Queue {
    List<Term> values = new ArrayList<>();

    synchronized void push(Term term) {
        values.add(term);
    }

    synchronized Term pop() {
        if (!values.isEmpty())
            return values.remove(0);
        return null;
    }

    boolean isEmpty() {
        return values.isEmpty();
    }
}