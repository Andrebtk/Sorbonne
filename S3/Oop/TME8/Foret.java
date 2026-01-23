import java.util.ArrayList; 

public class Foret {
	protected Object[][] terrain;
	
	public Foret(int taille) {
		terrain = new Object[taille][taille];
	}
	
	public boolean placer (Object obj) {
		int x = (int) (Math.random()*terrain.length); 
		int y = (int) (Math.random()*terrain[0].length);
		
		if (terrain[x][y]==null) {
			terrain[x][y] = obj;
			return true;
		}
		
		return false;
	}
	
		
	ArrayList<Champignon> ramasserChampignons() {
		ArrayList<Champignon> res = new ArrayList<Champignon>();

		for (int i=0; i< terrain.length; i++) {
			for (int j=0; j<terrain[i].length; j++) {
				if (terrain[i][j] instanceof Champignon) {
					res.add ( (Champignon)terrain[i][j]);
				}
			}
		}
		return res;
	}
	
	ArrayList<Object> ramasserTout () {
	
		ArrayList<Object> res = new ArrayList<Object>();
		
		for (int i=0; i< terrain.length; i++) {
			for (int j=0; j<terrain[i].length; j++) {
				if (terrain[i][j] instanceof Ramassables) {
					res.add (terrain[i][j]);
				}
			}
		}
		
		return res;
	}
	
	void ramasser (Panier p) {
	
	}
	
	

	public String toString() {
		String res="";
		for (int i=0; i< terrain.length; i++) {
			res += "|";
			for (int j=0; j<terrain[i].length; j++) {
				if (terrain[i][j] == null) {
					res += " ";
				} else {
					res += terrain[i][j].toString().charAt(0);
				}
			}
			res += "|\n";
		}
		return res;
	}
}
