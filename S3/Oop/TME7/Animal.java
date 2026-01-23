public abstract class Animal {
	private String nom;
	private int age;
	
	public Animal (String nom, int age) {
		this.nom = nom;
		this.age = age;
	}
	
	public Animal (String nom) {
		this(nom, 1);
	}
	
	public String toString () {
		return String.format ("Animal- nom: %s, age: %d", nom, age);
	}
	
	public void vieillir () {
		this.age+=1;
	}
	abstract public String crier();
}
