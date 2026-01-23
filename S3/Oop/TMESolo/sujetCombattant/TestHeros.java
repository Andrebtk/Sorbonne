public class TestHeros {
	public static void main(String [] args){
		Guilde g1 = new Guilde(10);
		g1.ajouterHeros(new Guerrier("epee", 13, "William"));
		g1.ajouterHeros(new Guerrier("marteau", 13, "Astrid"));
		g1.ajouterHeros(new Medecin("Lucie", 13));
		
		System.out.println(g1);
		g1.actionGuild();
	}
}
