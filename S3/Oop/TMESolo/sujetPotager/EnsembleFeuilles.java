public class EnsembleFeuilles extends Legume{
	private double degreGivre;
	
	public EnsembleFeuilles (double poids, double degreGivre) {
		super(poids);
		this.degreGivre = degreGivre;
	}
	
	public double evaluer(double prixParKilo) {
		return (1-degreGivre)*poids*prixParKilo;
	}
	
	public String toString() {
		return String.format("degreGivre: %.2f - %s", degreGivre, super.toString());
	}
}
