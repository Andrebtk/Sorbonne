public abstract class Pirate {
	public final int id;
	private static int cpt = 0;
	private String prenom;
	
	public Pirate (String prenom) {
		id = cpt++;
		this.prenom = prenom;
	}
	
	public String toString() {
		return prenom;
	}
}
