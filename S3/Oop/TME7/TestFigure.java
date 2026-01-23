public class TestFigure {
	public static void main (String [] args) {
		Figure [] tab = new Figure[5];
		
		Carre ca1 = new Carre(50);
		Carre ca2 = new Carre(42);
		
		Cercle ce1 = new Cercle(5,10);
		Cercle ce2 = new Cercle(4,6);
		
		tab[0] = ca1;
		tab[1] = ca2;
		tab[2] = ce1;
		tab[3] = ce2;
		
		for (Figure i: tab) {
			if (i != null && i instanceof Figure2D) {
			
				System.out.println(String.format("surface: %f, périmètre: %f", i.surface(), ((Figure2D )i).perimetre() ));
			}
		}
	}
}
