public class TestGroupe {
	public static void main(String [] args) {
		Groupe groupeSorcier = new Groupe(10);
		
		groupeSorcier.ajouter(new Sorcier(20, 4));
		groupeSorcier.ajouter(new Sorcier(20, 6));
		groupeSorcier.ajouter(new Sorcier(20, 8));
		
		Groupe groupeDragon = new Groupe(3);
		groupeDragon.ajouter(new Dragon (false));
		groupeDragon.ajouter(new Dragon (true));
		
		System.out.println(groupeSorcier);
		System.out.println(groupeDragon);
		
		groupeSorcier.attaqueGroupe(groupeDragon);
		
		System.out.println("Apres attaque");
		System.out.println(groupeSorcier);
		System.out.println(groupeDragon);
	}
}
