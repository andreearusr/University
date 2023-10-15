
public class ConsultatieMedicala {
    public Queue termsQueue;

    public ConsultatieMedicala(Queue termsQueue) {
        this.termsQueue = termsQueue;
    }

    public void addCM(Tichet t) {
        this.termsQueue.push(t);
    }
}
