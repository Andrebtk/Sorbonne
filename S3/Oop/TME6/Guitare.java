public class Guitare extends Instrument {
	private String type;
	
	public Guitare (int poids, int prix, String type) {
		super(poids, prix);
		this.type = type;
	}
	
	public String toString() {
		return String.format ("Guitare : type %s, poids : %d kg, prix : %d euros", type, super.poids, super.prix);
	}
	
	public void jouer () {
		System.out.println(String.format("La guitare %s joue", type));
	}
}
