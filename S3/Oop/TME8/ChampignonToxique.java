public class ChampignonToxique extends Champignon {
	
	
	public ChampignonToxique (String nom) {
		super(nom);
	}
	
	public double getPoids() {
		return super.getPoids();
	}
	public String toString() {
		return String.format("%s toxique ", super.toString());
	}
}
