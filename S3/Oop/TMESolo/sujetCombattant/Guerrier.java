public class Guerrier extends Combattant {
	private String arme;
	
	public Guerrier(String arme, int force, String prenom) {
		super(prenom, force);
		this.arme = arme;
	}
	
	public void action() {
		System.out.print(toString());
		if (arme == "marteau") {
			System.out.println (", attaque pour " + 2*super.getForce() + " degats");
		}else {
			System.out.println (", attaque pour " + (super.getForce() + (int)(Math.random()*(6-1+1)+1) )+ " degats");
		}
	}
	
	public String toString() {
		return super.toString() +", classe: guerrier, arme : " + arme;
	}
}
