public class Main {

    public static void main(String[] args) {
        BankAccountPlus first = new BankAccountPlus(10000.0);
        BankAccountPlus second = new BankAccountPlus(10000.0);

        Thread t1 = new Thread(() ->{
            first.withdrow(50);
        });

        Thread t2 = new Thread(() ->{
            first.deposit(1000);
        });

        Thread t3 = new Thread(() ->{
            first.transfer(second, 10);
        });

        Thread t4 = new Thread(() ->{
            second.withdrow(50);
        });

        Thread t5 = new Thread(() ->{
            second.transfer(first,100);
        });

        Thread t6 = new Thread(() ->{
            first.transfer2(second,100);
        });

        System.out.println("First: " + first.getAmount());
        System.out.println("Second: " + second.getAmount());

        t1.start();
        t2.start();
        t3.start();
        t4.start();
        t5.start();
        t6.start();

        try{
            t1.join();
            t2.join();
            t3.join();
            t4.join();
            t5.join();
            t6.join();
        }
        catch (InterruptedException e){
            throw  new RuntimeException();
        }

        System.out.println("First after: " + first.getAmount());
        System.out.println("Second after: " + second.getAmount());

    }
}
