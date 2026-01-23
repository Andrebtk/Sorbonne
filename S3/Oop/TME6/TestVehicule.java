public class TestVehicule {
	public static void main (String [] args) {
		Velo v1 = new Velo("MyVTT", 17);
		System.out.println(v1);
		v1.rouler(15);
		
		Voiture vo1 = new Voiture("My4x4", 300, 4);
		System.out.println(vo1);
		vo1.approvisionner (500);
		vo1.transporter (3, 300);
		
		Camion c1 = new Camion ("myCamion", 500, 300);
		System.out.println(c1);
		c1.approvisionner (100);
		c1.transporter ("Tuiles", 50);
		
		Vehicule [] lstV = new Vehicule[3];
		lstV[0] = v1;
		lstV[1] = vo1;
		lstV[2] = c1;
		
		for(int i=0; i<lstV.length; i++){
			lstV[i].rouler (10);
		}
		
		//On peut mettre transporter dans Vehicule.java
	} 
}
