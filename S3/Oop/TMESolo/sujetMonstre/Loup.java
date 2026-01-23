public class Loup extends MonstreTerrestre {
	
	public Loup(int force, String habitat, String couleur) {
		super(force, habitat, couleur);
	}
	
	public int attaque() {
		return getForce() + (int)(Math.random()*(5+1-1)+1);
	}
	
	public String toString() {
		return "Loup " + couleur+ " de force " + getForce() + " - "+ super.toString();
	}
}
