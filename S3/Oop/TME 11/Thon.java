public class Thon extends Poisson {
	public Thon(){
		super();
	}
	
	public void move(Point cible){
		double objectif = super.position.distanceTo(cible);
		if (objectif>60){
			position.x+=(int)(Math.random()*(15+15+1)-15);
			position.y+=(int)(Math.random()*(15+15+1)-15);
		}else {
			position.x+=objectif/2;
			position.y+=objectif/2;
		}
		super.verifPosition();
	}
	
	
	public String toString(){
		return "Thon"+super.toString();
	}
}
