public class Planete {
    private String nom;
    private double rayon;

    public Planete (String n, double r) {
        nom = n;
        rayon = r;
    }

	public Planete (String n) {
        nom = n;
        rayon = 1000;
    }

    public String toString () {
        return "Planete " + nom +  " de rayon " + rayon;
    }
    
    public double getRayon () {
        return rayon;
    }

}