public abstract class AnimauxSansPattes extends Animal {
	
	public AnimauxSansPattes (String nom, int age) {
		super(nom, age);
	}
	
	public String toString () {
		return String.format ("Animal sans pattes %s", super.toString() );
	}
}
