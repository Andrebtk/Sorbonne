public class TestMonstre {
	public static void main(String [] args) {
		Bande b1 = new Bande(10);
		
		b1.ajouterMonstre(new Kraken(8, 12, "geant"));
		b1.ajouterMonstre(new Kraken(6, 18, "petit"));
		b1.ajouterMonstre(new Loup(8, "foret", "brun"));
		b1.ajouterMonstre(new Loup(6, "plaine", "blanc"));
		
		System.out.println(b1);
		
		System.out.println(b1.attaqueBande());
	}
}
