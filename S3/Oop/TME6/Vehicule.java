public class Vehicule {
	protected static int cpt = 0;
	private String marque;
	private double distance = 0;
	
	public Vehicule (String marque) {
		this.marque = marque;
		cpt++;
	}	
	
	public void rouler (double d) {
		distance+=d;
		System.out.println(this + " a roulé "+ distance +" km");		
	}
	
	public String toString () {
		return String.format("%d de marque %s", cpt, marque);
	}
}
