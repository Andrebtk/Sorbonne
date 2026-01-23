public class TestStringBuilder {
	public static String testString(int nbIter, String chaine) {
		String s ="";
		for(int i=0; i<nbIter; i++){
			s+=chaine;
		}
		return s;
	}
	
	public static StringBuilder testStringBuilder(int nbIter, String chaine){
		StringBuilder sb = new StringBuilder();
		for (int i=0; i<nbIter; i++){
			sb.append(chaine);
		}
		return sb;
	}
	
	public static void main(String [] args){
		int nbIter = 100000;
		if (args.length == 1) nbIter=Integer.parseInt(args[0]);
		
		String [] tab = {"1", "1234567890", "123456789012345678901234567890"};
		
		for (String chaine: tab) {
			System.out.println("### nbIter =" + nbIter + " longueur=" + chaine.length());
			long debut1 = System.currentTimeMillis();
			testString(nbIter, chaine);
			long fin1 = System.currentTimeMillis();
			System.out.println("String durée : " +(fin1-debut1)+ " ms");
			
			long debut2 = System.currentTimeMillis();
			testStringBuilder(nbIter, chaine);
			long fin2 = System.currentTimeMillis();
			System.out.println("StringBuilder Durée : " + (fin2-debut2) + " ms");
			
		}
	}
}
