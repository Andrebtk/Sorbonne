public class SystemeSolaire {
    public static void main (String [] args) {
        Planete Mercure = new Planete ("Mercure", 2439.7);
        Planete Terre = new Planete ("Terre", 6378.1);
        Planete Mars = new Planete ("Mars");


        System.out.println (Mercure.toString ());
        System.out.println (Terre.getRayon ());
        System.out.println (Mars.getRayon ());

        double max, min;
        max = 'z';
        min = 'a';

        char randomChar = (char) (Math.random () * (max - min) + min);


        System.out.println ("random " + randomChar);
        
        int x=2, y=5;
        double z = x/y;
        
        System.out.println ("bonjour\nvous\ttous !");
    }
}