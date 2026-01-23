public class Theatre extends Structure{

	public Theatre(int anc, double niv) {
		super(anc,niv);
	}
	
	public String toString() {
		return String.format("Theatre | %s", super.toString());
	}
}
