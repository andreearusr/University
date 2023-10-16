package joc.domain;

import java.io.Serializable;

public class Entity<T> implements Serializable {

    public T Id;

    public Entity() {
    }

    public T getId() {
        return Id;
    }

    public void setId(T id) {
        Id = id;
    }

    @Override
    public String toString() {
        return Id.toString();

    }
}
