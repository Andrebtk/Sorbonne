public class Matelot extends Pirate implements Combattant {
	private int force;
	
	
	public Matelot(String prenom, int force) {
		super(prenom);
		this.force = force;
	}
	
	public int getDegats () {
		return force + (int)(Math.random()*(6-1+1)+1);
	}

	public String toString(){
		return super.toString() + ", matelot de force " + force;
	}
}
