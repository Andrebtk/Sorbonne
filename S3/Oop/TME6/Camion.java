public class Camion extends AMoteur {
	private double volume;
	
	public Camion (String marque, int capaciteReservoir, double volume) {
		super(marque, capaciteReservoir);
		this.volume = volume;
	}
	
	public String toString() {
		return String.format ("%s , volume : %f", super.toString(), volume);
	}

	public void transporter (String materiau, int km) {
		approvisionner(-km);
		
		if (super.enPanne()) {
			System.out.println(String.format("le camion %d n'a plus d'essence !", cpt));
		} else {
			System.out.println(String.format("Le camion %d a transporté des %s sur %d km",cpt,materiau,km));
		}
	}
}
