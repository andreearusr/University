
public class BankAccountPlus {

    private double amount;

    public BankAccountPlus(double amount){
        this.amount = amount;
    }

    public synchronized double getAmount(){
        return amount;
    }

    public synchronized boolean deposit(double sum){
        amount += sum;

        return true;
    }

    public synchronized boolean withdrow(double sum){
        if(amount < sum) {

            return false;
        }
        else
            amount -= sum;


        return true;
    }

    public boolean transfer(BankAccountPlus toAccount, double sum){
        synchronized (this) {
            synchronized (toAccount){
                if(amount < sum) {
                    return false;
                }

                try{
                    Thread.sleep(1000);
                }
                catch (InterruptedException e){
                    throw  new RuntimeException();
                }

                toAccount.deposit(sum);
                amount -= sum;

                return true;
            }
        }
   }

    public boolean transfer2(BankAccountPlus toAccount, double sum){
        synchronized (toAccount) {
            synchronized (this){
                if(amount < sum) {
                    return false;
                }

                try{
                    Thread.sleep(1000);
                }
                catch (InterruptedException e){
                    throw  new RuntimeException();
                }

                toAccount.deposit(sum);
                amount -= sum;

                return true;
            }
        }
    }


}
