public abstract class Navire {
	private String nom;
	private int solidite;
	
	private Combattant [] equipage;
	
	public Navire (int tailleMax, int solidite, String nom) {
		equipage = new Combattant[tailleMax];
		this.solidite = solidite;
		this.nom = nom;
	}
	
	public void ajouter(Combattant m) {
		for (int i=0; i<equipage.length; i++) {
			if (equipage[i] == null) {
				equipage[i] = m;
				return;
			}
		}
	}
	
	public abstract int getDegats();
	
	public int getNbCombattant () {
		int res = 0;
		for (int i=0; i<equipage.length; i++) {
			if (equipage[i] != null) {
				res++;
			}
		}
		return res;
	}
	
	public int getDegatsEquipage() {
		int res = 0;
		for (int i=0; i<equipage.length; i++) {
			if (equipage[i] != null) {
				res += equipage[i].getDegats();
			}
		}
		return res;
	}
	
	public String toString() {
		String res = "nommé " + nom + " a une solidité de " + solidite;
		res += "\nElle contient " + getNbCombattant() + " membres d'équipages : \n";
		for (int i=0; i<equipage.length; i++) {
			if (equipage[i] != null) {
				res += equipage[i].toString() + "\n";
			}
		}
		return res;
	}
	
}
