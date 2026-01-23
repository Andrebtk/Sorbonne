public abstract class Legume {
	protected double poids;
	private static int cpt = 1;
	public final int id;
	
	public Legume(double poids) {
		this.poids = poids;
		id=cpt++;
	}
	
	public abstract double evaluer(double prixParKilo);

	public String toString() {
		return String.format("id : %d, poids : %.2fkg", id, poids);
	}
}

