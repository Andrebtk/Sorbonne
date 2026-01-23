public class Guilde {
	private Heros[] tab;
	
	
	public Guilde (int tailleMax) {
		tab = new Heros[tailleMax];
	}
	
	public void ajouterHeros (Heros h) {
		for (int i=0; i<tab.length; i++) {
			if (tab[i] == null) {
				tab[i] = h;
				return;
			}
		}
	}
	
	public void actionGuild() {
		for (int i=0; i<tab.length; i++) {
			if (tab[i] != null) {
				tab[i].action();
			}
		}
	}
	
	public String toString() {
		String res = "La guilde est composée de : \n";
		for (int i=0; i<tab.length; i++) {
			if (tab[i] != null) {
				res += tab[i].toString() + "\n";
			}
		}
		return res;
		
	}
}
