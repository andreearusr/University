package tasks.model;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;
import tasks.services.TasksService;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

public class RTasksOperationsTestTopDown {

    private TasksService service;
    private TasksOperations repo;
    private Task t1;

    @BeforeEach
    public void setUp() {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        t1 = mock(Task.class);
        repo= new TasksOperations(new ArrayList<>(Arrays.asList(t1)));
        service = new TasksService(repo);
        MockitoAnnotations.initMocks(this);

    }

    @Test
    public void add() {
        Mockito.when(t1.getTitle()).thenReturn("title");
        service.add(t1);
        Mockito.verify(t1,never()).getTitle();
        assertEquals(repo.tasks.get(0).getTitle(),"title");
    }

    @Test
    public void incoming() throws ParseException {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        Mockito.when(t1.nextTimeAfter(formatter.parse("21-09-2022"))).thenReturn(formatter.parse("22-09-2022"));
        Iterable<Task> tasksfiltered = service.filterTasks(formatter.parse("21-09-2022"),formatter.parse("26-09-2022"));
        Mockito.verify(t1,times(1)).nextTimeAfter(formatter.parse("21-09-2022"));
        assertEquals(repo.incoming(formatter.parse("21-09-2022"),formatter.parse("22-09-2022"))
                .iterator().next().nextTimeAfter(formatter.parse("21-09-2022")),
                tasksfiltered.iterator().next().nextTimeAfter(formatter.parse("21-09-2022")));

    }
}