import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Node {
    public Term value;
    public Node nextNode = null;
    private ReentrantReadWriteLock lock;

    Node(Term value) {
        this.value = value;
        this.lock = new ReentrantReadWriteLock();
    }

    public void lock(){
        lock.writeLock().lock();
    }

    public void unlock(){
        lock.writeLock().unlock();
    }
}