public class Kraken extends MonstreMarin {
	private int nbTentacules;
	
	public Kraken (int force, int nbTentacules, String grandeur) {
		super(force, grandeur);
		this.nbTentacules = nbTentacules;
	}
	
	public int attaque() {
		if (grandeur == "geant") {
			return nbTentacules * super.getForce();
		}
		return Math.max(nbTentacules,super.getForce());
	}

	public String toString() {
		return"Kraken a "+ nbTentacules +" tentacules "+ grandeur + " de force "+super.getForce()+" - "+super.toString();
	}
}
