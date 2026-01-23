public class AMoteur extends Vehicule {
	private int capaciteReservoir;
	private int niveauEssence=0;
	
	public AMoteur (String marque, int capaciteReservoir) {
		super (marque);
		this.capaciteReservoir = capaciteReservoir;
	}
	
	public void approvisionner (double nbLitres) {
		niveauEssence+=nbLitres;
	}	
	
	public boolean enPanne() {
		return niveauEssence<0;
	}
	
	public String toString() {
		return super.toString();
	}
}
