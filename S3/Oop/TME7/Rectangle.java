public class Rectangle extends Figure2D {
	private double longeur;
	private double largeur;
	
	public Rectangle (double longeur, double largeur) {
		super();
		this.longeur = longeur;
		this.largeur = largeur;
	}
	
	public double surface () {
		return longeur*largeur;
	}
	
		
	public double perimetre () {
		return (longeur+largeur) * 2;
	}
}
