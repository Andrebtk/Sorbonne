public class Feu {
    private Lampe rouge;
    private Lampe orange;
    private Lampe vert;

    public Feu (Lampe rouge, Lampe orange, Lampe vert) {
        this.rouge = rouge;
        this.orange = orange;
        this.vert = vert;
    }

    public Feu () {
        this.rouge = new Lampe();
        this.orange = new Lampe();
        this.vert = new Lampe();
    }
}