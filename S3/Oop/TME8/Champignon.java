public class Champignon implements Ramassables {
	private String nom ;
	private double poids = (Math.random()*3);
	
	public Champignon (String nom) {
		this.nom = nom;
	}
	
	public double getPoids() {
		return poids;
	}
	
	public String toString() {
		return String.format("%s %fkg", nom, poids);
	}
	
}
