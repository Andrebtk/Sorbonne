package prep_TME1;

public class Produit {
	private int id;
	private String nom;
	private double prix;

	public Produit(int id, String nom, double prix) {
		this.id = id;
		this.nom = nom;
		this.prix = prix;
	}


	public int GetId() {
		return id;
	}

	public String GetNom() {
		return nom;
	}

	public double GetPrix() {
		return prix;
	}

	public String toString() {
		//'[ID: 101] Nom - Prix'.
		return "[ID: " + id + "] " + nom + " - " + prix + "€";
	}

}