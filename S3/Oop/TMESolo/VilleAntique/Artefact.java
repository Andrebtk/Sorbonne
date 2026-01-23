public abstract class Artefact {
	protected int anciennete;
	private static int cpt=0;;
	public final int id;
	
	public Artefact (int anciennete) {
		this.anciennete = anciennete;
		id=cpt++;
	}
	
	public String toString() {
		return String.format(" id : %d, anciennete : %d s",id ,anciennete);	
	}
	
	public abstract int apprecier();
}
