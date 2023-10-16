package joc.domain;

import java.sql.Timestamp;

public class MutareDTO extends Entity<Long>{

    private Long id;
    private Long idJoc;
    private Long idJucator;

    private String stareJoc;
    private Long idConfiguratie;
    private String cuvant1;
    private String cuvant2;
    private String cuvant3;

    private Integer rezultat;
    private Integer nrGhicite;
    private String cuvinteGhicite;

    private Timestamp timestamp;


    public MutareDTO(Long id, Long idJoc, Long idJucator, String stareJoc, Long idConfiguratie, String cuvant1, String cuvant2, String cuvant3, Integer rezultat, Timestamp timestamp,  Integer nrGhicite, String cuvinteGhicite) {
            setId(id);
        this.idJoc=idJoc;
        this.idJucator=idJucator;
        this.stareJoc = stareJoc;
        this.idConfiguratie=idConfiguratie;
        this.cuvant1 = cuvant1;
        this.cuvant2 = cuvant2;
        this.cuvant3 = cuvant3;
        this.rezultat = rezultat;
        this.timestamp = timestamp;
        this.nrGhicite=nrGhicite;
        this.cuvinteGhicite=cuvinteGhicite;

    }
    public MutareDTO( Long idJoc, Long idJucator, String stareJoc, Long idConfiguratie, String cuvant1, String cuvant2, String cuvant3, Integer rezultat, Timestamp timestamp,  Integer nrGhicite, String cuvinteGhicite) {
        setId(0L);
        this.idJoc=idJoc;
        this.idJucator=idJucator;
        this.stareJoc = stareJoc;
        this.idConfiguratie=idConfiguratie;
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


    public String getStareJoc() {
        return stareJoc;
    }

    public void setStareJoc(String stareJoc) {
        this.stareJoc = stareJoc;
    }

    public Long getIdJoc() {
        return idJoc;
    }

    public void setIdJoc(Long idJoc) {
        this.idJoc = idJoc;
    }

    public Long getIdJucator() {
        return idJucator;
    }

    public void setIdJucator(Long idJucator) {
        this.idJucator = idJucator;
    }

    public Long getIdConfiguratie() {
        return idConfiguratie;
    }

    public void setIdConfiguratie(Long idConfiguratie) {
        this.idConfiguratie = idConfiguratie;
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

    @Override
    public String toString() {
        return "MutareDTO{" +
                "id=" + id +
                ", idJoc=" + idJoc +
                ", idJucator=" + idJucator +
                ", stareJoc='" + stareJoc + '\'' +
                ", idConfiguratie=" + idConfiguratie +
                ", cuvant1='" + cuvant1 + '\'' +
                ", cuvant2='" + cuvant2 + '\'' +
                ", cuvant3='" + cuvant3 + '\'' +
                ", rezultat=" + rezultat +
                ", nrGhicite=" + nrGhicite +
                ", cuvinteGhicite='" + cuvinteGhicite + '\'' +
                ", timestamp=" + timestamp +
                '}';
    }
}

