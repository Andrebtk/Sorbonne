public abstract class Poisson {
	protected Point position;
	
	public Poisson () {
		position = new Point((int)(Math.random()*(499+1)),(int)(Math.random()*(499+1)));
	}
	
	public Point getPoint() {
		return position;
	}
	
	public abstract void move(Point cible);
	
	public void verifPosition(){
		if (position.x > 500) position.x = position.x % 500;
		if (position.y > 500) position.y = position.y % 500; 
		if (position.x < 0) position.x = -position.y % 500; 
		if (position.y < 0) position.y = -position.y % 500; 
	}
	
	public String toString() {
		return position.toString();
	}
}
