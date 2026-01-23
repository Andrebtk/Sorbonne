public class Menagerie {
	private Animal [] tab = new Animal[10];
	private int nbAnimal=0;
	
	public Menagerie () {
	
	}
	
	public void ajouter (Animal a) {
		if (nbAnimal < 10) {
			tab[nbAnimal] = a;
			nbAnimal++;
		}
	}
	
	public String toString () {
		String s = "";
		for (Animal i: tab){
			if (i != null)
				s += i.toString()+"\n";
		}
		return s;
	}
	
	public void midi () {
		for (Animal i: tab){
			if (i != null)
				System.out.println(i.crier());
		}
	}
}
