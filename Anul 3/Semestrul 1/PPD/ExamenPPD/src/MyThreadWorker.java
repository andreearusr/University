public class MyThreadWorker extends Thread{
    private Queue termsQueue;
    ConsultatieMedicala cm;
    Deparazitare d;
    Toaletare t;

    public MyThreadWorker(Queue termsQueue, ConsultatieMedicala cm, Deparazitare d, Toaletare t) {
        this.termsQueue = termsQueue;
        this.cm=cm;
        this.d=d;
        this.t=t;
    }

    @Override
    public void run() {
        try {
            int serviciu=0;
            Tichet term = termsQueue.pop();
            while (term != null) {
                serviciu = term.serviciu;
                if( serviciu == 1)
                    this.cm.addCM(term);
                else if(serviciu == 3)
                    this.d.addD(term);
                else if(serviciu==4)
                    this.t.addT(term);
                term = termsQueue.pop();
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }
}
