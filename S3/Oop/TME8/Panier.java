import java.util.ArrayList; 

public class Panier {
	private double poidsMax;
	private double poidsActuel;
	private ArrayList<Object> dansPanier = new ArrayList<Object>();
	
	public Panier(double poidsMax) {
		this.poidsMax = poidsMax;
		poidsActuel = 0.0;
	}
	
	
	public void add (Object obj) {

		if(obj instanceof Ramassables) {
			if (obj instanceof Champignon) {
				poidsActuel += ((Champignon)obj).getPoids();
				dansPanier.add(obj);
			}
			/*if ( (((obj.getClass())obj).getPoids())+poidsActuel <= poidsMax) {
				poidsActuel += ((obj.getClass())obj).getPoids();
				dansPanier.add(obj);
			}*/
		} else {
			
		}
	}
	
	public double getPoids() {
		return 0.0;
	}
	
	
}
