import model.MessageTask;

import java.time.LocalDateTime;

public class Run {

    public static MessageTask[] createMessageTaskArray(){
        MessageTask t1 = new MessageTask("1","MTask1","Buna","Daniel","Octavian", LocalDateTime.now());
        MessageTask t2 = new MessageTask("2","MTask2","Salut","Octavian","Daniel", LocalDateTime.now());
        MessageTask t3 = new MessageTask("3","MTask3","Ciao","Maria","Ana", LocalDateTime.now());
        return new MessageTask[]{t1,t2,t3};
    }

    public static void main(String[] args){
        MessageTask[] messageTasks = createMessageTaskArray();

        for(MessageTask t : messageTasks){
            t.execute();
        }

    }

}
