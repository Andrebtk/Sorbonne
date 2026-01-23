public abstract class MonstreTerrestre extends Monstre {
	protected String couleur;
	
	public MonstreTerrestre (int force, String habitat, String couleur) {
		super(force, habitat);
		this.couleur = couleur;
	}


}
