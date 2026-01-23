public abstract class Monstre {
	private final int id;
	private int force;
	private String habitat;
	private static int cpt = 1;
	
	public Monstre (int force, String habitat) {
		id = cpt++;
		this.force = force;
		this.habitat = habitat;
	}
	
	public int getForce() {
		return force;
	}
	
	public abstract int attaque();
	
	public String toString() {
		return "habitat : " + habitat + ", id: " + id;
	}
}
