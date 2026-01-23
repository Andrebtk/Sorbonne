public class Tubercules extends Legume {
	private char infection;
	
	public Tubercules(double poids, char lettre) {
		super(poids);
		infection = lettre;
	}
	
	public String toString() {
		return "infection: " + infection + " - " +super.toString();
	}
	
	public static double facteurInfeciton(char infection) {
		return 1 - 0.14*((int) (infection-'G'));
	}
	
	public double evaluer(double prixParKilo) {
		return Tubercules.facteurInfeciton(infection) * prixParKilo * poids;
	}
}
