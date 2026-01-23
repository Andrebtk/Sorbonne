public class TestTracteur {
	public static void main(String [] args) {
		Roue r1 = new Roue(120);
		Roue r2 = new Roue(120);
		
		Roue r3 = new Roue(80);
		Roue r4 = new Roue(80);
		
		Cabine c1 = new Cabine (3, "bleue");
		Cabine c2 = new Cabine (3, "bleue");
		
		Tracteur t1 = new Tracteur (c1, r1, r2, r3, r4);
		System.out.println (t1.toString());
		
		//Tracteur t2 = t1;
		
		Tracteur t2 = new Tracteur (c2, r1, r2, r3, r4);
		t2.peindre ("rouge");		// couleur t1 -> Rouge, car t2 pointe vers t1
						//Il faut crée une autre Cabine
		System.out.println (t2.toString());		
	}
}
