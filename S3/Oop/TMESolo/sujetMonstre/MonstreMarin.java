public abstract class MonstreMarin extends Monstre {
	protected String grandeur;
	
	public MonstreMarin (int force, String grandeur) {
		super(force,"mer");
		this.grandeur = grandeur;
	}
	

}
