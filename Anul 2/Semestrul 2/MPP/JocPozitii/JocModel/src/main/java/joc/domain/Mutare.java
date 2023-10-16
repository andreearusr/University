package joc.domain;

import java.sql.Timestamp;

public class Mutare extends Entity<Long> {

    private Long id;
    private Joc joc;
    private Jucator jucator;

    private String stareJoc;
    private Configuratie configuratie;
    private String cuvant1;
    private String cuvant2;
    private String cuvant3;

    private Integer nrGhicite;
    private String cuvinteGhicite;

    private Integer rezultat;

    private Timestamp timestamp;

    public Mutare() {

    }

    public Mutare(Long id, Joc joc, Jucator jucator, String stareJoc, Configuratie configuratie, String cuvant1, String cuvant2, String cuvant3, Integer rezultat, Timestamp timestamp,Integer nrGhicite, String cuvinteGhicite) {
        setId(id);
        this.joc = joc;
        this.jucator = jucator;
        this.stareJoc = stareJoc;
        this.configuratie = configuratie;
        this.cuvant1 = cuvant1;
        this.cuvant2 = cuvant2;
        this.cuvant3 = cuvant3;
        this.rezultat = rezultat;
        this.timestamp = timestamp;
        this.nrGhicite=nrGhicite;
        this.cuvinteGhicite=cuvinteGhicite;

    }

    public Mutare(Joc joc, Jucator jucator, String stareJoc, Configuratie configuratie, String cuvant1, String cuvant2, String cuvant3, Integer rezultat, Timestamp timestamp, Integer nrGhicite, String cuvinteGhicite) {
        setId(0L);
        this.joc = joc;
        this.jucator = jucator;
        this.stareJoc = stareJoc;
        this.configuratie = configuratie;
        this.cuvant1 = cuvant1;
        this.cuvant2 = cuvant2;
        this.cuvant3 = cuvant3;
        this.rezultat = rezultat;
        this.timestamp = timestamp;
        this.nrGhicite=nrGhicite;
        this.cuvinteGhicite=cuvinteGhicite;

    }

    @Override
    public Long getId() {
        return super.getId();
    }

    @Override
    public void setId(Long id) {
        super.setId(id);
    }

    public Joc getJoc() {
        return joc;
    }

    public void setJoc(Joc joc) {
        this.joc = joc;
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public String getStareJoc() {
        return stareJoc;
    }

    public void setStareJoc(String stareJoc) {
        this.stareJoc = stareJoc;
    }

    public Configuratie getConfiguratie() {
        return configuratie;
    }

    public void setConfiguratie(Configuratie configuratie) {
        this.configuratie = configuratie;
    }

    public String getCuvant1() {
        return cuvant1;
    }

    public void setCuvant1(String cuvant1) {
        this.cuvant1 = cuvant1;
    }

    public String getCuvant2() {
        return cuvant2;
    }

    public void setCuvant2(String cuvant2) {
        this.cuvant2 = cuvant2;
    }

    public String getCuvant3() {
        return cuvant3;
    }

    public void setCuvant3(String cuvant3) {
        this.cuvant3 = cuvant3;
    }

    public Integer getRezultat() {
        return rezultat;
    }

    public void setRezultat(Integer rezultat) {
        this.rezultat = rezultat;
    }

    public Timestamp getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(Timestamp timestamp) {
        this.timestamp = timestamp;
    }

    public Integer getNrGhicite() {
        return nrGhicite;
    }

    public void setNrGhicite(Integer nrGhicite) {
        this.nrGhicite = nrGhicite;
    }

    public String getCuvinteGhicite() {
        return cuvinteGhicite;
    }

    public void setCuvinteGhicite(String cuvinteGhicite) {
        this.cuvinteGhicite = cuvinteGhicite;
    }

    public void setCuvant(Integer nr, String cuvant) {
        if (nr == 1) {
            this.setCuvant1(cuvant);
        }

        if (nr == 2) {
            this.setCuvant2(cuvant);
        }

        if (nr == 3) {
            this.setCuvant3(cuvant);
        }
    }

    @Override
    public String toString() {
        return "Mutare{" +
                "id=" + id +
                ", joc=" + joc +
                ", jucator=" + jucator +
                ", stareJoc='" + stareJoc + '\'' +
                ", configuratie=" + configuratie +
                ", cuvant1='" + cuvant1 + '\'' +
                ", cuvant2='" + cuvant2 + '\'' +
                ", cuvant3='" + cuvant3 + '\'' +
                ", nrGhicite=" + nrGhicite +
                ", cuvinteGhicite='" + cuvinteGhicite + '\'' +
                ", rezultat=" + rezultat +
                ", timestamp=" + timestamp +
                '}';
    }
}
