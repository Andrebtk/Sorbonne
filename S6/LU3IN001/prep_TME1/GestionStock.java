package prep_TME1;

import java.util.List;
import java.util.ArrayList;

import java.util.HashMap;
import java.util.Collections;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class GestionStock {
	

	public static List<Produit> chargerFichier(String chemin) {

		List<Produit> l = new ArrayList<>();

		try (BufferedReader br = new BufferedReader(new FileReader(chemin))) {
			String line;

			while((line = br.readLine()) != null) {
				String[] line_data = line.split(";");
				try {
					l.add( new Produit(
						Integer.parseInt(line_data[0]),
						line_data[1],
						Double.parseDouble(line_data[2])
					));
				} catch (NumberFormatException e) {
					System.out.println("Ligne ignorée (format incorrect) : " + line);
				}
				
			}

		} catch (IOException e) {
			System.err.println("Error reading the file: " + e.getMessage());
		}

		return l;
	}

	public static HashMap<Integer, Produit> toHashMap(List<Produit> l) {
		HashMap<Integer, Produit> map = new HashMap<>();

		for(Produit p: l) {
			map.put(p.GetId(), p);
		}

		return map;

	}

	public static List<Produit> sortList(List<Produit> lProd) {
		Collections.sort(lProd, 
			(l1, l2) -> Double.compare(l1.GetPrix(), l2.GetPrix())
		);

		return lProd;
	}

}