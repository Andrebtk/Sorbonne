import java.util.ArrayList;
public class PoissonList extends ArrayList<Poisson> {
	public ArrayList<Poisson> lstPoisson;
	
	public PoissonList (){
		lstPoisson = new ArrayList<Poisson>();
	}
	
	public PoissonList(PoissonList lst){
		lstPoisson = new ArrayList<Poisson>();
		
		for (Poisson elem: lst){
			lstPoisson.add(elem);
		}
		
	}
	
	public int nbThons(){
		int res =0;
		for (Poisson elem: lstPoisson){
			System.out.println(elem);
			if (elem instanceof Thon){
				res+=1;
			}
		}
		return res;
	}
}
