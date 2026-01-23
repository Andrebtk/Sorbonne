public class TestPotager {
	public static void main(String [] args) {
		Potager p1 = new Potager(10);
		Potager p2 = new Potager(10);
		Potager p3 = new Potager(10);
		
		p1.ajouter();
		p1.ajouter();
		p1.ajouter();
		p1.ajouter();
	
		
		
		p2.ajouter();
		p2.ajouter();
		p2.ajouter();
		
		p3.ajouter();
		p3.ajouter();
		p3.ajouter();
		
		System.out.println(String.format("p1 prix -> %.2f", p1.prixPotager(3.9)));
		System.out.println(String.format("p2 prix -> %.2f", p2.prixPotager(3.9)));
		System.out.println(String.format("p3 prix -> %.2f", p3.prixPotager(3.9)));
		
		
		System.out.println(p1+ "\n");
		System.out.println(p2+ "\n");
		System.out.println(p3+ "\n");
	}
}
