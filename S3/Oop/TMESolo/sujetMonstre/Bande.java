public class Bande {
	private Monstre[] tab;
	
	public Bande(int tailleMax) {
		tab = new Monstre[tailleMax];
	}
	
	
	public void ajouterMonstre(Monstre m) {
		for (int i =0; i<tab.length; i++) {
			if (tab[i] == null) {
				tab[i] = m;
				return;
			}
		}
	}
	
	public int attaqueBande() {
		int res=0;
		for (int i =0; i<tab.length; i++) {
			if (tab[i] != null) {
				res += tab[i].attaque(); 
			}
		}
		return res;
	}
	
	public String toString() {
		String res = "La bande est composée de  \n";
		for (int i =0; i<tab.length; i++) {
			if (tab[i] != null) {
				res += tab[i].toString() + "\n";
			}
		}
		
		return res;
		
	}
}
