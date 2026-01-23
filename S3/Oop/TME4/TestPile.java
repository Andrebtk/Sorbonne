public class TestPile {
    public static void main (String [] args) {
        Pile p = new Pile (3);

        Assiette a1 = new Assiette (13);
        Assiette a2 = new Assiette (42);
        Assiette a3 = new Assiette (53);

        
        p.empiler (a1);
        System.out.println(p);
        p.empiler (a2);
        System.out.println(p);
        p.empiler (a3);
        System.out.println(p);
        
        p.depiler();
        System.out.println(p);
        
        
        p.empiler (a1);
        System.out.println(p);
        p.empiler (a2);
        System.out.println(p);

        p.depiler();
        System.out.println(p);
        p.depiler();
        System.out.println(p);
        p.depiler();
        System.out.println(p);
        p.depiler();
        System.out.println(p);
        
    
    }
}