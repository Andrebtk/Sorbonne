public class TestOrchestre {
	public static void main (String [] args) {
		Guitare g1 = new Guitare(300, 700, "classique");
		Piano p1 = new Piano (500, 1100, 88);
		System.out.println(p1);
		System.out.println(g1);
		
		Orchestre o1 = new Orchestre(5);
		o1.ajouterInstrument (g1);
		o1.ajouterInstrument (p1);
		o1.jouer();
	}
}
