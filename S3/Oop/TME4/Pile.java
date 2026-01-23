public class Pile {
    private Assiette [] tab;
    private int nbA;

    public Pile (int tailleMax) {
        tab = new Assiette[tailleMax];
    }

    public boolean estVide () {
        return nbA == 0;
    }

    public boolean estPleine () {
        return nbA == tab.length;
    }

    public void empiler (Assiette a) {
        if ( !(estPleine ()) ) {
            for(int i = tab.length -1; i>0; i--) {
                tab[i] = tab[i-1];
            }
            tab[0] = a;
            nbA++;
        }
        
    }

    public Assiette depiler () {
        if ( !(estVide ()) ) {
            Assiette temp = tab[0];

            for (int i = 0; i<tab.length-1; i++) {
                tab[i] = tab[i+1];
            }
            nbA--;
            tab[nbA] = null;
           
            return temp;
        }
        return null;
    }

    public String toString() {
        String res = "";
        for (int i=0; i<tab.length; i++) {
            if (tab[i] != null) 
                res += tab[i] + "\n";
        }
        return res;
    }

} 