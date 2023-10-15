package tasks.model;

import javafx.collections.ObservableList;

import java.util.*;

public class TasksOperations {

    public ArrayList<Task> tasks = new ArrayList<>();

    public TasksOperations(ObservableList<Task> tasksList){
        tasks.addAll(tasksList);
    }

    public TasksOperations(ArrayList<Task> tasksList){
        tasks.addAll(tasksList);
    }
    public TasksOperations(ArrayTaskList tasksList){
        if(tasksList !=  null) {
            for (Task t : tasksList) {
                tasks.add(t);
            }
        }
    }

    public void add(Task t){
        tasks.add(t);
    }

    public Iterable<Task> incoming(Date start, Date end){
        ArrayList<Task> incomingTasks = new ArrayList<>();
        if (!start.before(end))
            return incomingTasks;
        int index = 0;
        while (index < tasks.size()) {
            Date nextTime = tasks.get(index).nextTimeAfter(start);
            if (nextTime != null) {
                if (nextTime.before(end) || nextTime.equals(end)) {
                    incomingTasks.add(tasks.get(index));
                }
            }
            index += 1;
        }
        return incomingTasks;
    }

    public SortedMap<Date, Set<Task>> calendar( Date start, Date end){
        Iterable<Task> incomingTasks = incoming(start, end);
        TreeMap<Date, Set<Task>> calendar = new TreeMap<>();

        for (Task t : incomingTasks){
            Date nextTimeAfter = t.nextTimeAfter(start);
            while (nextTimeAfter!= null && (nextTimeAfter.before(end) || nextTimeAfter.equals(end))){
                if (calendar.containsKey(nextTimeAfter)){
                    calendar.get(nextTimeAfter).add(t);
                }
                else {
                    HashSet<Task> oneDateTasks = new HashSet<>();
                    oneDateTasks.add(t);
                    calendar.put(nextTimeAfter,oneDateTasks);
                }
                nextTimeAfter = t.nextTimeAfter(nextTimeAfter);
            }
        }
        return calendar;
    }
}

