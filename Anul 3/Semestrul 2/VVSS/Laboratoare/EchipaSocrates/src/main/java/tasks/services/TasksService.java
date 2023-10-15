package tasks.services;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import tasks.model.ArrayTaskList;
import tasks.model.Task;
import tasks.model.TasksOperations;
import tasks.utils.TaskIO;

import java.util.Date;

import static tasks.utils.Helper.formTimeUnit;

public class TasksService {

    private  TasksOperations repo = null;

    public TasksService(TasksOperations repo){
        this.repo=repo;
    }

    public String getIntervalInHours(Task task){
        int seconds = task.getRepeatInterval();
        int minutes = seconds / DateService.SECONDS_IN_MINUTE;
        int hours = minutes / DateService.MINUTES_IN_HOUR;
        minutes = minutes % DateService.MINUTES_IN_HOUR;
        return formTimeUnit(hours) + ":" + formTimeUnit(minutes);//hh:MM
    }

    public int parseFromStringToSeconds(String stringTime){//hh:MM
        String[] units = stringTime.split(":");
        int hours = Integer.parseInt(units[0]);
        int minutes = Integer.parseInt(units[1]);
        int result = (hours * DateService.MINUTES_IN_HOUR + minutes) * DateService.SECONDS_IN_MINUTE;
        return result;
    }

    public void add(Task t){
        repo.add(t);
    }

    public Iterable<Task> filterTasks(Date start, Date end){
        Iterable<Task> filtered = repo.incoming(start,end);

        return filtered;
    }

    public ObservableList<Task> getObservableList() {
        return FXCollections.observableArrayList(repo.tasks);
    }
}
