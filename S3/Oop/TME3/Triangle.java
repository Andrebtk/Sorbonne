public class Triangle {
	private Point p1;
	private Point p2;
	private Point p3;
	
	public Triangle (Point p1, Point p2, Point p3) {
		this.p1 = p1;
		this.p2 = p2;
		this.p3 = p3;
	}
	
	public Triangle () {
		this(new Point(), new Point(), new Point());
	}
	
	public Triangle (Triangle t) {
		this.p1 = new Point (t.p1);
		this.p2 = new Point (t.p2);
		this.p3 = new Point (t.p3);
	}

	public double getPerimetre () {
		return p1.distance(p2) + p1.distance(p3) + p2.distance(p3);
	}	
	
	public boolean equals (Triangle t) {
		if (t == null) return false;

		return ((t.p1.equal(this.p1)) && (t.p2.equal(this.p2)) && (t.p3.equal(this.p3)));
	} 
	
	public String toString() {
		return "{"+p1+";"+p2+";"+p3+"}";
	}
}

