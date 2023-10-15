
public class Toaletare {

    public Queue termsQueue;

    public Toaletare(Queue termsQueue) {
        this.termsQueue = termsQueue;
    }

    public void addT(Tichet t)   {
        this.termsQueue.push(t);
    }
}
