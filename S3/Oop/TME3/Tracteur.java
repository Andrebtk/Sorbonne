public class Tracteur {
	private Cabine c;
	
	private Roue r1;
	private Roue r2;
	private Roue r3;
	private Roue r4;

	public Tracteur (Cabine c, Roue r1, Roue r2, Roue r3, Roue r4) {
		this.c = c;
		this.r1 = r1;
		this.r2 = r2;
		this.r3 = r3;
		this.r4 = r4;
	}
	
	public void peindre (String couleur) {
		c.setCouleur(couleur);
	}
	
	public String toString () {
		return c.toString() + r1.toString() + r2.toString() + r3.toString() + r4.toString() +"\n";
	}
}
