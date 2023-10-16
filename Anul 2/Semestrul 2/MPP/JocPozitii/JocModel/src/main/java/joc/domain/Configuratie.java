package joc.domain;

public class Configuratie extends Entity<Long> {

    private Long id;
    private String l1;
    private String l2;
    private String l3;
    private String cuv1;
    private String cuv2;
    private String cuv3;


    public Configuratie() {

    }

    public Configuratie(Long id, String l1, String l2, String l3, String cuv1, String cuv2, String cuv3) {
        setId(id);
        this.l1 = l1;
        this.l2 = l2;
        this.l3 = l3;
        this.cuv1 = cuv1;
        this.cuv2 = cuv2;
        this.cuv3 = cuv3;
    }


    public Configuratie(String l1, String l2, String l3, String cuv1, String cuv2, String cuv3) {
        this.l1 = l1;
        this.l2 = l2;
        this.l3 = l3;
        this.cuv1 = cuv1;
        this.cuv2 = cuv2;
        this.cuv3 = cuv3;
    }

    @Override
    public Long getId() {
        return super.getId();
    }

    public void setId(Long id) {
        super.setId(id);
    }

    public String getL1() {
        return l1;
    }

    public void setL1(String l1) {
        this.l1 = l1;
    }

    public String getL2() {
        return l2;
    }

    public void setL2(String l2) {
        this.l2 = l2;
    }

    public String getL3() {
        return l3;
    }

    public void setL3(String l3) {
        this.l3 = l3;
    }

    public String getCuv1() {
        return cuv1;
    }

    public void setCuv1(String cuv1) {
        this.cuv1 = cuv1;
    }

    public String getCuv2() {
        return cuv2;
    }

    public void setCuv2(String cuv2) {
        this.cuv2 = cuv2;
    }

    public String getCuv3() {
        return cuv3;
    }

    public void setCuv3(String cuv3) {
        this.cuv3 = cuv3;
    }

    @Override
    public String toString() {
        return "Configuratie{" +
                "id=" + id +
                ", l1='" + l1 + '\'' +
                ", l2='" + l2 + '\'' +
                ", l3='" + l3 + '\'' +
                ", cuv1='" + cuv1 + '\'' +
                ", cuv2='" + cuv2 + '\'' +
                ", cuv3='" + cuv3 + '\'' +
                '}';
    }
}
