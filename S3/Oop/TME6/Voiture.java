public class Voiture extends AMoteur{
	private int nbPlaces;
	
	public Voiture (String marque, int capaciteReservoir, int nbPlaces) {
		super (marque, capaciteReservoir);
		this.nbPlaces = nbPlaces;
	}
	
	public String toString() {
		return String.format ("%s , nbPlaces : %d", super.toString(), nbPlaces);
	}
	
	public void transporter (int nbPers, int km) {
		approvisionner(-km);
		if (super.enPanne()) {
			System.out.println(String.format("la voiture %d n'a plus d'essence !", cpt));
		} else if (nbPers > nbPlaces){
			System.out.println("Pas assez de places");
		}else{
			System.out.println(String.format("la voiture %d transporte %d persoones sur %d km", cpt, nbPers, km));
		}
	} 
}
