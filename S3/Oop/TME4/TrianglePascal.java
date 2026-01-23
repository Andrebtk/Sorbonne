public class TrianglePascal {
    private int [][] triangle;

    public TrianglePascal (int n) {
        triangle = new int[n][];
        for (int i=0; i<n; i++) {
            triangle[i] = new int[i + 1];
        }
    }

    public void remplirTriangle() {
        for (int i=0; i< triangle.length; i++) {
            for (int j=0; j<triangle[i].length; j++) 
                 triangle[i][j] = ((j==0) || (j==i)) ? 1 :  triangle[i-1][j-1] + triangle[i-1][j];
        }
    }

    public String toString () {
        String res = "";
         for (int i=0; i< triangle.length; i++) {
            for (int j=0; j<triangle[i].length; j++) {
                res +=  triangle[i][j];
                res += (j == triangle[i].length-1) ? " \n" : " ";
            }
        }
        return res;
    }
}