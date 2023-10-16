package joc.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Jucator extends Entity<Long> implements Serializable {

    private Long id;
    private String username;
    private String password;
    private String alias;

    public Jucator(Long id, String username, String password, String alias) {
        setId(id);
        this.username = username;
        this.password = password;
        this.alias=alias;
    }

    public Jucator(String username, String password, String alias) {
        setId(0L);
        this.username = username;
        this.password = password;
        this.alias=alias;
    }

    @Override
    public Long getId() {
        return super.getId();
    }

    @Override
    public void setId(Long id) {
        super.setId(id);
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getAlias() {
        return alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }


    @Override
    public String toString() {
        return "Jucator{" +
                "id=" + id +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                ", alias='" + alias +
                '}';
    }
}
