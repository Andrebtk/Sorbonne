public class TestVilleAntique {
	public static void main(String [] args) {
		VilleAntique v1 = new VilleAntique(10);
		VilleAntique v2 = new VilleAntique(10);
		VilleAntique v3 = new VilleAntique(10);
		
		v1.fouiller();
		System.out.println("");
		v2.fouiller();
		System.out.println("");
		v3.fouiller();
		
		
		System.out.println(v1);
		System.out.println(v2);
		System.out.println(v3);
	}
}

