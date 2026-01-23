public abstract class Heros {
	private final int id;
	private String prenom;
	private static int cpt=0;
	
	public Heros (String prenom) {
		this.prenom = prenom;
		id = cpt++;
	}
	
	public String toString() {
		return prenom;
	}
	public abstract void action();
	
	

}
