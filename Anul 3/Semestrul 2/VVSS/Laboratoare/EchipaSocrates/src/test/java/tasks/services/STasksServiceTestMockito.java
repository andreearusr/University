package tasks.services;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;
import tasks.model.ArrayTaskList;
import tasks.model.Task;
import tasks.model.TasksOperations;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.times;

class STasksServiceTestMockito {

    private  TasksService service = null;
    private TasksOperations repo;
    private Task t1, t2;

    int sizeOfIterable(Iterable<Task> iterable) {
        int counter = 0;
        for (Object i : iterable) { counter++; }
        return counter;
    }

    @BeforeEach
    void setUp() {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        repo= mock(TasksOperations.class);
        service = new TasksService(repo);
        MockitoAnnotations.initMocks(this);

        try {
            t1 = new Task("T1", formatter.parse("21-09-2022"), formatter.parse("24-09-2022"),120, true);
            t2 = new Task("T2", formatter.parse("22-09-2022"), formatter.parse("25-09-2022"),60, true);
        } catch (ParseException e) {
            throw new RuntimeException(e);
        }
    }

    @Test
    void add() {
        Mockito.doNothing().when(repo).add(t1);
        service.add(t1);
        Mockito.verify(repo,times(1)).add(t1);
    }

    @Test
    void filterTasks() throws ParseException {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        Mockito.when(repo.incoming(formatter.parse("21-09-2022"),formatter.parse("26-09-2022"))).thenReturn(Arrays.asList(t2));
        Iterable<Task> tasksfiltered =service.filterTasks(formatter.parse("21-09-2022"),formatter.parse("26-09-2022"));
        int size = sizeOfIterable(tasksfiltered);
        Mockito.verify(repo,times(1)).incoming(formatter.parse("21-09-2022"),formatter.parse("26-09-2022"));
        assertEquals(size,1);
    }
}