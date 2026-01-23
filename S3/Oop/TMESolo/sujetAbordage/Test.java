public class Test {
	public static void main(String [] args) {
		Jonque j1 = new Jonque(40, "Thuyen", "rouge");
		j1.ajouter(new Matelot("Pierre",5));
		j1.ajouter(new Matelot("William",6));
		
		System.out.println(j1);
	}
}
