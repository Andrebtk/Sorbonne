public class Couple {
    private int x,y;
    
    public Couple (int x, int y) {
        this.x = x;
        this.y = y;
    }

    public String toString () {
        return "(" + x + "," + y + ")";
    }

    public Couple addition (Couple a, Couple b) {
        return new Couple (a.x + b.x, a.y + b.y);
    }
}