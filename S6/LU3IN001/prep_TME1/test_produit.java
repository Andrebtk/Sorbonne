package prep_TME1;

import java.util.ArrayList;
import java.util.List;

import java.util.HashMap;


public class test_produit {
	public static void main(String[] args) {
		Produit n = new Produit(101, "toto", 15);

		System.out.println(n.toString());

		List<Produit> listProduit = GestionStock.chargerFichier("prep_TME1/stock.csv");

		System.out.println("Nb d'article: " + listProduit.size());

		for(Produit p: listProduit) {
			System.out.println(p);
		}

		HashMap<Integer, Produit> map = GestionStock.toHashMap(listProduit);
		System.out.println(map.get(103));

		List<Produit> listProduitSorted = GestionStock.sortList(listProduit);

		System.out.println("\n\nSorted list : ");
		for(Produit p: listProduitSorted) {
			System.out.println(p);
		}
	}
}