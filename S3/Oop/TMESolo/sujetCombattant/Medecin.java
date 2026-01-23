public class Medecin extends NonCombattant {
	
	public Medecin(String prenom, int intelligence) {
		super(prenom, intelligence);
	}
	
	public void action() {
		System.out.println(toString() + ", soigne " + super.getIntelligence()/2 + " heros");
	}
	
	public String toString() {
		return super.toString() + " Intelligence : " + super.getIntelligence() + ", classe : medecin";
	}

}

