public class Sorcier extends EtreVivant{
	private int intelligence;
	
	
	public Sorcier(int pv, int i){
		super(pv);
		intelligence = i;
	}
	
	public int getDegats() {
		return intelligence + (int)(Math.random()*(4-2+1)+2);
	}
	
	public String toString(){
		return String.format("Sorcier d'intelligence %d - %s\n",intelligence,super.toString());
	}
}
