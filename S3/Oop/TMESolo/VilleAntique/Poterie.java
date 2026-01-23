public class Poterie extends Relique {
	
	public Poterie(int anciennete, char grade) {
		super(anciennete,grade);
	}
	
	public String toString() {
		return String.format("Poterie | %s", super.toString());
	}
}
