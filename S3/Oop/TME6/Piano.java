public class Piano extends Instrument {
	private int nbTouches;
	
	public Piano (int poids, int prix, int nbTouches) {
		super(poids, prix);
		this.nbTouches = nbTouches;
	}
	
	public String toString () {
		return String.format("Piano : %d touches poids : %d kg, prix : %d euros", nbTouches, super.poids, super.prix);
	}
	
	public void jouer() {
		System.out.println (String.format("Le piano a %d touches joue", nbTouches));
	}
	
	
}
