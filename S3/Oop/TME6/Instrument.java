public class Instrument {
	 protected int poids;
	 protected int prix;
	 
	 public Instrument (int poids, int prix) {
	 	this.poids = poids;
	 	this.prix = prix;
	 }
	 
	 public String toString()  {
	 	return String.format ("poids : %d kg, prix : %d euros", poids, prix);
	 }
	 
	 public void jouer () {
	 	System.out.println("L'instrument joue");
	 }
}
