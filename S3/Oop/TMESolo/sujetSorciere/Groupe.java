public class Groupe {
	private EtreVivant[] tab;
	
	public Groupe(int taille) {
		tab = new EtreVivant[taille];
	}
	
	
	public void ajouter(EtreVivant e) {
		for (int i =0; i<tab.length; i++) {
			if (tab[i] == null) {
				tab[i] = e;
				return;
			}
		}
	}
	
	public int nombrePasKo () {
		int res=0;
		for (int i =0; i<tab.length; i++) {
			if(tab[i] != null) {
				if(tab[i].estPasKo())
					res++;
			}
		}
		return res;
	}
	
	public void subirDegatsGroupe(int degats) {
		for (int i =0; i<tab.length; i++) {
			if(tab[i] != null) {
				tab[i].subirDegats(degats);
			}
		}
	}
	
	public void attaqueGroupe(Groupe g) {
		int somme = 0;
		for (int i =0; i<tab.length; i++) {
			if(tab[i] != null && tab[i].estPasKo()) {
				somme += tab[i].getDegats();
			}
		}
		
		g.subirDegatsGroupe(somme/nombrePasKo());
	}
	
	public String toString() {
		String res = "Le groupe est composé de : \n";
		for (int i =0; i<tab.length; i++) {
			if (tab[i] != null) {
				res+=tab[i].toString();
			}
		}
		return res;
	}
	
}
