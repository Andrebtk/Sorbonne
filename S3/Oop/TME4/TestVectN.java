public class TestVectN {
    public static void main(String [] args) {
        /*
        VectN v1 = new VectN(5, 9);

        System.out.println(v1.toString ());
        System.out.println(v1.somme());
        */

        VectN vect = new VectN ( 4, 5, 6) ;
        int [] t=vect.getTab ( ) ;
        
        System.out.println (" vect ="+vect) ;
        t[0] = 100;
        System.out.println (" vect ="+vect) ;
        
    }
}