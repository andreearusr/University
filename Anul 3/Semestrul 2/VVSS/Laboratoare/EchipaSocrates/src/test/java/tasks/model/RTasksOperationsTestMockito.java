package tasks.model;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;
import tasks.services.TasksService;


import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

class RTasksOperationsTestMockito {

    private TasksOperations repo;
    private Task t1;

    int sizeOfIterable(Iterable<Task> iterable) {
        int counter = 0;
        for (Object i : iterable) { counter++; }
        return counter;
    }


    @BeforeEach
    void setUp() {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        t1 = mock(Task.class);
        repo= new TasksOperations(new ArrayList<>(Arrays.asList(t1)));
        MockitoAnnotations.initMocks(this);

    }

    @Test
    void add() {
        Mockito.when(t1.getTitle()).thenReturn("title");
        repo.add(t1);
        Mockito.verify(t1,never()).getTitle();
        assertEquals(repo.tasks.get(0).getTitle(),"title");
    }

    @Test
    void incoming() throws ParseException {
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        Mockito.when(t1.nextTimeAfter(formatter.parse("21-09-2022"))).thenReturn(formatter.parse("22-09-2022"));
        Iterable<Task> tasksfiltered = repo.incoming(formatter.parse("21-09-2022"),formatter.parse("26-09-2022"));
        Mockito.verify(t1,times(1)).nextTimeAfter(formatter.parse("21-09-2022"));
        assertEquals(tasksfiltered.iterator().next().nextTimeAfter(formatter.parse("21-09-2022")),formatter.parse("22-09-2022"));

    }
}