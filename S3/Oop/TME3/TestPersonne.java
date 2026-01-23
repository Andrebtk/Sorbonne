public class TestPersonne {
	public static void main(String [] main) {
		Personne p1 = new Personne ("Pierre");
		Personne p2 = new Personne ("Alex");
		Personne p3 = new Personne ("Mathis");

		System.out.println(p1.toString());
		System.out.println(p2.toString());
		System.out.println(p3.toString());

		p1.epouser (p2);
		p1.epouser (p3);
		p3.epouser (p1);
		p1.epouser (p1);
		
		p1.divorcer ();
		p3.divorcer ();

		System.out.println(p1.toString());
		System.out.println(p2.toString());
		System.out.println(p3.toString());
	}
}