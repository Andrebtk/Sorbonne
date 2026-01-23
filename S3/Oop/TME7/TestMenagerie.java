public class TestMenagerie {
	public static void main (String [] args) {
		Menagerie m = new Menagerie();
		
		Vache v1 = new Vache("Vache1", 3);
		Vache v2 = new Vache("Vache2", 7);
		Boa b1 = new Boa("boa1", 2);
		
		m.ajouter(v1);
		m.ajouter(v2);
		m.ajouter(b1);
		
		System.out.println(m);
		m.midi();
	}
}
