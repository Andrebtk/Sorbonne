public class Vache extends AnimauxAvecPattes {
	
	private double quantiteLait = (int) (Math.random()*(30-5)+5);
	
	public Vache (String nom, int age) {
		super(nom,age,4);
	}
	
	public String crier() {
		return String.format ("Vache crie");
	}
	
}
