public class Jonque extends Navire {
	private int nbCanon;
	private String couleur;
	
	public Jonque(int tailleMax, String nom, String couleur){
		super(tailleMax, 250, nom);
		this.nbCanon = 6;
		this.couleur = couleur;
	}
	
	
	public int getDegats() {
		return Math.max(nbCanon,super.getNbCombattant()*10+super.getDegatsEquipage());
	}
	
	public String toString() {
		return "La jonque " + couleur + ", " + super.toString();
	}
}
