package model;

import java.util.Objects;

public abstract class Task {

    private String taskID;
    private String description;

    public Task(String taskID, String description) {
        this.taskID = taskID;
        this.description = description;
    }

    public String getTaskID() {
        return taskID;
    }

    public void setTaskID(String taskID) {
        this.taskID = taskID;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public String toString() {
        return taskID + " " + description;
    }

    @Override
    public int hashCode(){
        return Objects.hash(this.getTaskID(),this.getDescription());
    }

    @Override
    public boolean equals(Object o){
        if(this == o)
            return true;

        if(!(o instanceof Task))
            return false;

        Task task = (Task) o;

        return Objects.equals(this.getTaskID(),task.getTaskID()) && Objects.equals(this.getDescription(), task.getDescription());
    }

    public abstract void execute();
}
