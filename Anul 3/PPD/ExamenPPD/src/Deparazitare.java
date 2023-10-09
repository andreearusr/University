
public class Deparazitare {

    public Queue termsQueue;

    public Deparazitare(Queue termsQueue) {
        this.termsQueue = termsQueue;
    }

    public void addD(Tichet t)   {
        this.termsQueue.push(t);
    }
}
