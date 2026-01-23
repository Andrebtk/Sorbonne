public class Orchestre {
	private int max;
	private Instrument [] lstOrchestre;
	private int nbInstrument = 0;
	
	public Orchestre (int max) {
		this.max = max;
		lstOrchestre = new Instrument[2];
	}
	
	public void ajouterInstrument (Instrument x) {
		if (nbInstrument<max) {
			lstOrchestre[nbInstrument] = x;
			nbInstrument++;
		}
	}
	
	public void jouer() {
		for (int i =0; i<lstOrchestre.length; i++) {
			lstOrchestre[i].jouer();
		}
	}
}
