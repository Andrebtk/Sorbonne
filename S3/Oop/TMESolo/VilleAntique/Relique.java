public class Relique extends Artefact {
	private char grade;
	
	public Relique (int anciennete, char grade) {
		super(anciennete);
		this.grade = grade;
	}
	
	public static int facteurGrade(char lettre) {
		return 900-160*(lettre - 'A');
	}
	
	public String toString() {
		return String.format("%s, grade : %s",super.toString(),grade);
	}
	
	public int apprecier() {
		return super.anciennete * facteurGrade(grade);
	}
}
