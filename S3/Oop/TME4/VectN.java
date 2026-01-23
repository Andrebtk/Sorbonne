public class VectN {
    private int[] tab;

    private VectN (int n) {
        tab = new int[n];
    }

    public VectN (int n, int valMax) {
        this(n);
        for (int i=0; i<n-1; i++){
            tab[i] = (int) ( (Math.random() * valMax));
        }
    }

    public VectN () {
        this(5, 9);
    }

    public VectN (int a, int b, int c) {
        this (3);
        tab[0]=a;
        tab[1]=b;
        tab[2]=c;
    }

    public int somme () {
        int res = 0;
        for (int i: tab) {
            res += i;
        }
        return res;
    }

    public String toString () {
        String res = "[";

        for (int i=0; i<tab.length; i++) 
            res += i+1 == tab.length ? tab[i]+ "]" : tab[i] + ", ";

        return res;
    }

    public int[] getTab() {
        int []tabCopie = new int[tab.length];
        for (int i=0; i<tab.length; i++) {
            tabCopie[i] = tab[i];
        }
        return tabCopie;
    }
}