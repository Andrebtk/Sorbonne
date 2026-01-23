public class Velo extends SansMoteur {
	private int nbVitesses;
	
	public Velo (String marque, int nbVitesses) {
		super(marque);
		this.nbVitesses = nbVitesses;
	}
	
	public String toString() {
		return String.format ("Vélo %s sans moteur %d vitesses", super.toString(), nbVitesses);
	}
	
	public void transporter (String depart, String arrivee) {
		System.out.println(String.format("Le velo %d se déplace de %s a %s", cpt, depart, arrivee));
	}
	

}
