public class TestPoissonList {
	public static void main (String [] args) {
		PoissonList lst = new PoissonList();
		lst.lstPoisson.add(new Thon());
		lst.lstPoisson.add(new Thon());
		lst.lstPoisson.add(new Requin());
		lst.lstPoisson.add(new Thon());
		lst.lstPoisson.add(new Requin());
		
		System.out.println(lst.nbThons());
	}
}
