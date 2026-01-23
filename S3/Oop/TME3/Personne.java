public class Personne {
	private String nom;
	private Personne conjoint;
	
	public Personne (String nom) {
		this.nom = nom;
		conjoint = null;
	}
	
	public Personne () {
		this("Pers"+ (char)(Math.random()*('Z'-'A')+'A'));
	}
	
	public void epouser (Personne p) {
		if (this == p) {
			System.out.println("[Error] - Une personne essaye de se marier avec elle-même");
			return;
		} else if (this.conjoint != null) {
			System.out.println (String.format("[Error] - Le mariage de %s, marié(e) avec %s, célibataire est impossible", this.nom, p.nom));
		} else if (p.conjoint != null) {
			System.out.println (String.format("[Error] - Le mariage de %s, marié(e) avec %s, célibataire est impossible", p.nom, this.nom));
		} else {
			System.out.println (String.format("%s, célibataire se marie avec %s, célibataire", this.nom, p.nom));
			this.conjoint = p;
		}
	}

	public void divorcer () {
		if (this.conjoint == null) {
			System.out.println (String.format("[Error] - Divorce impossible %s n'est pas marié(e)", this.nom));
		} else {
			System.out.println (String.format("%s, marié(e) divorce de %s, marié(e)", this.nom, this.conjoint.nom));
			
			this.conjoint.conjoint = null;
			this.conjoint = null;
		}
	}

	public String toString () {
		return nom += (conjoint!=null) ? ", marié(e)" : ", célibataire"; 	
	}
}
