public abstract class AnimauxAvecPattes extends Animal {
	private int nbPattes;
	
	public AnimauxAvecPattes (String nom, int age, int nbPattes) {
		super(nom, age);
		this.nbPattes = nbPattes;
	}
	
	public String toString () {
		return String.format ("Animal avec %d pattes %s",nbPattes, super.toString());
	}
	

}
