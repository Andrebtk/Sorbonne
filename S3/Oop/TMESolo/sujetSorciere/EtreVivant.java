public abstract class EtreVivant {
	private int id;
	private int pointVie;
	private static int cpt = 1;
	
	public EtreVivant (int pv) {
		id = cpt;
		cpt++;
		pointVie = pv;
	}
	
	public void subirDegats(int degats) {
		pointVie -= degats;
		if (pointVie<0) {
			pointVie=0;
		}
	}
	
	public boolean estPasKo() {
		return pointVie>0;
	}
	
	public abstract int getDegats();
	
	public int getPointVie() {
		return pointVie;
	}
	
	public String toString() {
		return String.format("pointVie : %d, id : %d", pointVie, id);
	}
}
