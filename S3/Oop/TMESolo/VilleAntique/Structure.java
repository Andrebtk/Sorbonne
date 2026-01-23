public class Structure extends Artefact {
	private double niveauPreservation;
	
	public Structure (int anc, double niv) {
		super(anc);
		niveauPreservation=niv;
	}
	
	public int apprecier() {
		return (int) (900*niveauPreservation*anciennete);
	}
	
	public String toString() {
		return String.format("%s, niveauPreservation: %.2f ",super.toString(),niveauPreservation*100);
	}
}
