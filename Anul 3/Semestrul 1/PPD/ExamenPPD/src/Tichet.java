public class Tichet {
    int id;
    int serviciu;

    public Tichet(int id, int serviciu) {
        this.id = id;
        this.serviciu = serviciu;
    }

    @Override
    public String toString() {
        return id + " " + serviciu;
    }
}
