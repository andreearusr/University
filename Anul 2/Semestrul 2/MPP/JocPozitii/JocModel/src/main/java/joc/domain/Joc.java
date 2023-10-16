package joc.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Joc extends Entity<Long> implements Serializable {

    private Long id;
    private String stareJoc;

    public Joc() {
    }

    public Joc(Long id, String stareJoc) {
        setId(id);
        this.stareJoc = stareJoc;
    }

    public Joc(String stareJoc) {
        setId(0L);
        this.stareJoc = stareJoc;
    }

    @Override
    public Long getId() {
        return super.getId();
    }

    @Override
    public void setId(Long id) {
        super.setId(id);
    }

    public String getStareJoc() {
        return stareJoc;
    }

    public void setStareJoc(String stareJoc) {
        this.stareJoc = stareJoc;
    }


    @Override
    public String toString() {
        return "Joc{" +
                "id=" + id +
                ", stareJoc=" + stareJoc +
                '}';
    }
}
