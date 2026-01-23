"""
 * Projet : Mini-Projet 2 : Gestion d’une bibliotheque
 * Auteurs : 
 *   - Andre Bertok (21204512)
 *   - Olivier Huang (21206369)
 """
import matplotlib.pyplot as plt
import pandas as pd

# Charger le fichier CSV
data = pd.read_csv("data_original.csv")


tailles = data["Taille"]
temps_liste = data["Temps_Liste"]
temps_hash = data["Temps_Hash"]


plt.figure(figsize=(10, 6))
plt.plot(tailles, temps_liste, marker='o', linestyle='-', color='red', label="Temps de recherche (Liste)")
plt.plot(tailles, temps_hash, marker='s', linestyle='-', color='blue', label="Temps de recherche (Table de hachage)")


plt.xlabel("Nombre de livres")
plt.ylabel("Temps de recherche (secondes)")
plt.title("Temps de recherche en fonction de la taille de la bibliothèque")
plt.legend()
plt.grid(True)

# Sauvegarder le graphique en image
plt.savefig("temps_recherche_bibliotheque.png", dpi=300)
plt.show()
