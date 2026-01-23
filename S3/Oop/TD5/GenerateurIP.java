public class GenerateurIP {
    private static int [] tab = {192,168,0,0}; 

    private GenerateurIP () {};


    public static String getIP() {
        tab[3] +=1;
        if (tab[3] == 256) {
            tab[3] = 0;
            tab[2] += 1;
        }

        return String.format ("%d.%d.%d.%d", tab[0], tab[1], tab[2], tab[3]);
    }
}