public class Ellipse extends Figure2D {
	private double longueurA;
	private double longueurB;
	
	public Ellipse (double longueurA, double longueurB) {
		super();
		this.longueurA = longueurA;
		this.longueurB = longueurB;
	}
	
	public double surface () {
		return Math.PI*longueurA*longueurB;
	}
	
		
	public double perimetre () {
		return 2*Math.PI*Math.sqrt(((longueurA*longueurA + longueurB*longueurB)/2));
	}
}
