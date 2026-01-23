public class TestForet {
	public static void main (String [] args) {
		Foret f = new Foret(10);
		
		for (int i=0; i<10; i++) {
			Object ajt;
			if (Math.random()<0.3) {
				ajt = new Arbre ("Pins");
			} else {
				if (Math.random()<0.3) {
					ajt = new ChampignonToxique("amanites");
				} else {
					ajt = new Champignon("cèpes");
				}
				
			}
			
			boolean res = f.placer(ajt);
			while (!res) {
		 		f.placer(ajt);
			}
		}
		
		System.out.println(f);
		
		Panier p = new Panier (8);
		p.add(new ChampignonToxique("amanites"));
		
	}
}
