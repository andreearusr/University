package tasks.model;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.MockitoAnnotations;
import tasks.services.TasksService;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.mock;

public class ETaskTestTopDown {

    private TasksService service;
    private TasksOperations repo;
    private Task t1;
    @Test
    public void getTitle() {
        service.add(t1);
        assertEquals(service.getObservableList().get(0).getTitle(),"T1");
        assertEquals(repo.tasks.get(0).getTitle(),"T1");
    }

    @Test
    public void setTitle() {

        service.add(t1);
        service.getObservableList().get(0).setTitle("TITLU");
        assertEquals(service.getObservableList().get(0).getTitle(), "TITLU");
        assertEquals(repo.tasks.get(0).getTitle(), "TITLU");
    }

    @BeforeEach
    public void setUp() throws ParseException {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        t1 = new Task("T1", formatter.parse("21-09-2022"), formatter.parse("24-09-2022"),120, true);
        repo= new TasksOperations(new ArrayList<>(Arrays.asList(t1)));
        service = new TasksService(repo);

    }
}