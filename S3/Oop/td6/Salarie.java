public class Salarie extends Personne {
    private double salaire;

    public Salarie (String nom, double salaire) {
        super(nom, null);
        this.salaire = salaire;
    }

    public double getSalaire () {
        return salaire;
    }

    public double prime() {
        double tmp = getNbEnfants() * 0.05;
        return salaire + (salaire*tmp);
    }

    public void modifierNumTel (String numTel) {
        super.numTel = numTel; 
        System.out.println(super.nom + ": Le salarie " + super.nom + " a pour numero " + numTel);
    }


}