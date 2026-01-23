public class Requin extends Poisson {
	
	public Requin(){
		super();
	}
	
	public String toString(){
		return "requin"+super.toString();
	}
	
	public void move(Point cible) {
		double objectif = super.position.distanceTo(cible);

		position.x+=objectif/2;
		position.y+=objectif/2;
		
		super.verifPosition();
	}
}
