public class Statue extends Relique {

	public Statue(int anciennete, char grade) {
		super(anciennete,grade);
	}
	public String toString() {
		return String.format("Statue | %s", super.toString());
	}
}
