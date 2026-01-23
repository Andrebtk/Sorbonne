public class TestTriangle {
	public static void main (String [] args) {
		Point p1 = new Point();
		Point p2 = new Point();
		
		System.out.println (p1.toString());
		System.out.println (p2.toString());
		
		Point p3 = new Point();
		Triangle t1 = new Triangle (p1, p2, p3);
		Triangle t2 = new Triangle (t1);
		
		System.out.println(t1.toString ()+" : "+t1.getPerimetre());
		System.out.println(t2.toString ()+" : "+t1.getPerimetre());
		System.out.println(t1.equals (t2)+"\n");
		
		p1.deplaceToi (0,0);	
			
		System.out.println(t1.toString ()+" : "+t1.getPerimetre());
		System.out.println(t2.toString ()+" : "+t1.getPerimetre());
		System.out.println(t1.equals (t2));

	}
}
