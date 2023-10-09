import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BankAccount {

    private double amount;
    Lock lock = new ReentrantLock();

    public BankAccount(double amount){
        this.amount = amount;
    }

    public double getAmount(){
        return amount;
    }

    public boolean deposit(double sum){
        lock.lock();
        amount += sum;
        lock.unlock();

        return true;
    }

    public boolean withdrow(double sum){
        lock.lock();
        if(amount < sum) {
            lock.unlock();

            return false;
        }
        else
            amount -= sum;

        lock.unlock();

        return true;
    }

    public boolean transfer(BankAccount toAccount, double sum){
        lock.lock();
        toAccount.lock.lock();

        if(amount < sum) {
            toAccount.lock.unlock(); //unlock in ordine inversa
            lock.unlock();

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

        toAccount.lock.unlock();
        lock.unlock();

        return true;
    }
}
