public class Potager {
	private Legume [] tab;
	
	public Potager (int tailleMax) {
		tab = new Legume[tailleMax];
	}
	
	public boolean estPlein() {
		for (int i=0; i<tab.length; i++) {
			if (tab[i] == null)
				return false;
		}
		return true;
	}
	
	public void ajouter() {
		if (estPlein()) {
			System.out.println("Potager plein");	
			return;
		}
		for (int i=0; i<tab.length; i++) {
			if (tab[i] == null) {
				if (Math.random() < 0.3) {
				System.out.println("Ajoute PommeTerre");
					tab[i] = new PommeTerre (Math.random()*3, (char) (Math.random()*('G'-'L'+1)+'L'));
				}
				else if (Math.random() < 0.7) {
					if (Math.random()<0.5) {
						System.out.println("Ajoute Laitue");
						tab[i] = new Laitue(Math.random()*3, Math.random());
					}else{
						System.out.println("Ajoute Endive");
						tab[i] = new Endive(Math.random()*3, Math.random());					
					}
				} else {
					System.out.println("Ne rajoute rien");
				}
				return;
			}
		}
	}
	
	public double prixPotager(double prixKilo) {
		double res = 0.0;
		for (int i=0; i<tab.length; i++) {
			if (tab[i] != null){
				res += tab[i].evaluer(prixKilo);
			}
		}
		return res;
	}
	
	public String toString() {
		String res = "Dans le potager \n";
		for (int i=0; i<tab.length; i++) {
			if (tab[i] != null){
				res += tab[i].toString() + "\n";
			}
		}
		return res;
	}
}
