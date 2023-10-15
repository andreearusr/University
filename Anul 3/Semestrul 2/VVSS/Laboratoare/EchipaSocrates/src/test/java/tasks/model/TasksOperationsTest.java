package tasks.model;

import javafx.collections.ObservableList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import tasks.controller.NewEditController;
import tasks.services.DateService;
import tasks.services.TasksService;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;

public class TasksOperationsTest {
    private TasksOperations tasksOperations = null;
    private Date di,di2,di3,di4,di5,di6= new Date();
    private Date dou,dou2,dou3,dou4,dou5,dou6= new Date();
    private Task t1, t2, t3, t4, t5;

    @BeforeEach
    public void setUp() throws ParseException {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        di = formatter.parse("12-09-2023");
        di2 = formatter.parse("22-09-2022");
        di3 = formatter.parse("25-09-2022");
        di4 = formatter.parse("25-09-2022");
        di5 = formatter.parse("25-09-2022");
        di6 = formatter.parse("24-09-2022");

        dou = formatter.parse("11-09-2023");
        dou2 = formatter.parse("23-09-2022");
        dou3 = formatter.parse("26-09-2022");
        dou4 = formatter.parse("26-09-2022");
        dou5 = formatter.parse("27-09-2022");
        dou6 = formatter.parse("28-09-2022");

        t1 = new Task("T1", formatter.parse("21-09-2022"), formatter.parse("24-09-2022"),120, true);
        t2 = new Task("T2", formatter.parse("22-09-2022"), formatter.parse("26-09-2022"),60, true);
        t3 = new Task("T1", formatter.parse("27-09-2022"), formatter.parse("28-09-2022"),120, true);
        t4 = new Task("T2", formatter.parse("28-09-2022"), formatter.parse("29-09-2022"),120, true);
        t5 = new Task("T1", formatter.parse("26-09-2022"), formatter.parse("27-09-2022"),120, true);

    }

    public int sizeOfIterable(Iterable<Task> iterable) {
        int counter = 0;
        for (Object i : iterable) { counter++; }
        return counter;
    }

    @Test
    public void filterTasksWB1() {
        ArrayList<Task> tasks = new ArrayList<Task>();
        tasks.add(t1);
        tasks.add(t2);
        tasksOperations = new TasksOperations(tasks);
        Iterable<Task> result = tasksOperations.incoming(di, dou);
        assertEquals(sizeOfIterable(result), 0);
    }

    @Test
    public void filterTasksWB2() {
        ArrayList<Task> tasks = new ArrayList<Task>();
        tasksOperations = new TasksOperations(tasks);
        Iterable<Task> result = tasksOperations.incoming(di2, dou2);
        assertEquals(sizeOfIterable(result), 0);
    }

    @Test
    public void filterTasksWB3() {
        ArrayList<Task> tasks = new ArrayList<Task>();
        tasks.add(t1);
        tasksOperations = new TasksOperations(tasks);
        Iterable<Task> result = tasksOperations.incoming(di3, dou3);
        assertEquals(sizeOfIterable(result), 0);
    }

    @Test
    public void filterTasksWB4() {
        ArrayList<Task> tasks = new ArrayList<Task>();
        tasks.add(t3);
        tasks.add(t4);
        tasksOperations = new TasksOperations(tasks);
        Iterable<Task> result = tasksOperations.incoming(di4, dou4);
        assertEquals(sizeOfIterable(result), 0);
    }

    @Test
    public void filterTasksWB5() {
        ArrayList<Task> tasks = new ArrayList<Task>();
        tasks.add(t5);
        tasksOperations = new TasksOperations(tasks);
        Iterable<Task> result = tasksOperations.incoming(di5, dou5);
        assertEquals(sizeOfIterable(result), 1);
    }

    @Test
    public void filterTasksWB6() {
        ArrayList<Task> tasks = new ArrayList<Task>();
        tasks.add(t5);
        tasksOperations = new TasksOperations(tasks);
        Iterable<Task> result = tasksOperations.incoming(di6, dou6);
        assertEquals(sizeOfIterable(result), 1);
    }
}
