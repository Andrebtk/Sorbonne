public class VilleAntique {
	private Artefact[] tab;
	
	public VilleAntique (int nbMax) {
		tab = new Artefact[nbMax];
	}
	
	public boolean estPlein () {
		for (int i=0; i<tab.length; i++) {
			if (tab[i] == null)
				return false;
		}
		
		return true;
	}
	
	public void fouiller () {
		System.out.println("Debut Fouille");
		for (int i=0; i<tab.length; i++) {
			if (Math.random() < 0.2) {
			System.out.println("Trouver Theatre");
				tab[i] = new Theatre((int) (Math.random()*60), Math.random());
			} else if (Math.random()<0.8) {
				if (Math.random()<0.5) {
					System.out.println("Trouver Statue");
					tab[i] = new Statue((int) (Math.random()*60),(char)(Math.random()*('A'-'F')+'F') );
				}else {
					System.out.println("Trouver Poterie");
					tab[i] = new Poterie((int) (Math.random()*60),(char)(Math.random()*('A'-'F')+'F'));
				}
			} else {
				System.out.println("Rien Trouver");
			} 
			
		}

	}
	
	
	public String toString() {
		String res = "Ville Antique : \n";
		for (int i=0; i<tab.length; i++) {
			if (tab[i] != null) {
				res += tab[i].toString() + "\n";
			}
		}
		return res;
	}
	
}
