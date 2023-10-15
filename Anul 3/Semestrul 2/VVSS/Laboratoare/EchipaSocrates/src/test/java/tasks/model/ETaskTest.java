package tasks.model;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.text.ParseException;

import static org.junit.jupiter.api.Assertions.*;

public class ETaskTest {

    private Task t= null;

    @Test
    public void getTitle() {
        try {
            t= new Task("new task",Task.getDateFormat().parse("2023-02-12 10:10"));
        } catch (ParseException e) {
            throw new RuntimeException(e);
        }
        String title = t.getTitle();
        assertEquals(title,"new task");
    }

    @Test
    public void setTitle() {

        try {
            t= new Task("old task",Task.getDateFormat().parse("2023-02-12 10:10"));
        } catch (ParseException e) {
            throw new RuntimeException(e);
        }
        t.setTitle("new title");
        assertEquals(t.getTitle(),"new title");
    }

}