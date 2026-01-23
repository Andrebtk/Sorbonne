public class Dragon extends EtreVivant {
	private boolean estGeant;
	
	public Dragon(boolean estGeant){
		super(estGeant ? 60 : 40);
		this.estGeant = estGeant;
	}
	
	public int getDegats () {
		return super.getPointVie()/3;
	}
	
	public String toString() {
		String r = "Dragon ";
		if (estGeant) r+= " géant ";
		return r + String.format("- %s \n",super.toString());
	}
}
