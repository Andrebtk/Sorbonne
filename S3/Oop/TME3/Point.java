public class Point {
	private int posx;
	private int posy;
	
	public Point (int posx, int posy) {
		this.posx = posx;
		this.posy = posy;
	}
	
	public Point () {
		this((int) (Math.random()*9),(int) (Math.random()*9));
	}
	
	public Point (Point p) {
		this.posx = p.posx;
		this.posy = p.posy;
	}
	
	public void deplaceToi (int newx, int newy) {
		posx = newx;
		posy = newy;
	}
	
	public boolean equal (Point p) {
		return (this.posx==p.posx) && (this.posy==this.posy);
	}

	public double distance (Point P) {
		return Math.sqrt ( Math.pow((double) (P.posx-posx),2) + Math.pow((double) (P.posy-posy),2) );
	}
	
	public String toString () {
		return String.format("(%d,%d)", posx, posy);
	}
}

