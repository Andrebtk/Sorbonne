public class TestBouteille {
    public static void main (String [] args) {
        Bouteille b1 = new Bouteille (10);
        Bouteille b2 = new Bouteille ();

       
        System.out.println (b1.toString ());
        System.out.println (b2.toString ());  

        b2.remplir (b1);
        System.out.println (b1.toString ());
        System.out.println (b2.toString ());     
    }
}