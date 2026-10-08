#!/usr/bin/env python3

import os
import matplotlib.pyplot as plt

N = 50  # nombre de colonnes du tas
Nb_ajout = 3

# ===== Lecture fichiers à 3 colonnes =====
def lire_dernier_run(csv_path):
    with open(csv_path, "r", encoding="utf-8") as f:
        lignes = [l.strip() for l in f if l.strip()]

    lignes = lignes[-N:]

    x, h_init, h_final = [], [], []
    for ligne in lignes:
        i, hi, hf = map(int, ligne.split())
        x.append(i)
        h_init.append(hi)
        h_final.append(hf)

    return x, h_init, h_final


# ===== Lecture fichier ajout (4 colonnes, plusieurs blocs) =====
def lire_tous_les_ajouts(csv_path):
    with open(csv_path, "r", encoding="utf-8") as f:
        lignes = [l.strip() for l in f if l.strip()]

    nb_blocs = len(lignes) // N

    # On ne garde que les Nb_ajout derniers blocs
    debut = max(0, nb_blocs - Nb_ajout)

    blocs = []

    for k in range(debut, nb_blocs):
        bloc = lignes[k * N : (k + 1) * N]

        x, h_init, h_ajout, h_final = [], [], [], []
        for ligne in bloc:
            i, hi, ha, hf = map(int, ligne.split())
            x.append(i)
            h_init.append(hi)
            h_ajout.append(ha)
            h_final.append(hf)

        blocs.append((x, h_init, h_ajout, h_final))

    return blocs


def main():
    os.makedirs("plots", exist_ok=True)

    # ===== Stabilisation simple =====
    x, h_init, h_stable = lire_dernier_run("../datas/data_simple.csv")

    plt.figure(figsize=(8, 4))
    plt.plot(x, h_init, "o-", label="tas initial")
    plt.plot(x, h_stable, "o-", label="après stabilisation")
    plt.xlabel("indice")
    plt.ylabel("hauteur")
    plt.title("Avant / Après stabilisation")
    plt.grid(alpha=0.3)
    plt.legend()
    plt.tight_layout()
    plt.savefig("plots/stabilisation.png", dpi=150)
    plt.close()

    # ===== Effet du vent =====
    x, h_init, h_vent = lire_dernier_run("../datas/data_vent.csv")

    plt.figure(figsize=(8, 4))
    plt.plot(x, h_init, "o-", label="tas initial")
    plt.plot(x, h_stable, "o-", label="après stabilisation")
    plt.plot(x, h_vent, "o-", label="après effet du vent")
    plt.xlabel("indice")
    plt.ylabel("hauteur")
    plt.title("Avant / Après effet du vent")
    plt.grid(alpha=0.3)
    plt.legend()
    plt.tight_layout()
    plt.savefig("plots/vent.png", dpi=150)
    plt.close()

    # ===== Ajouts successifs : UNE IMAGE PAR AJOUT =====
    blocs = lire_tous_les_ajouts("../datas/data_ajout.csv")

    for k, (x, h_init, h_ajout, h_final) in enumerate(blocs, start=1):
        plt.figure(figsize=(8, 4))
        plt.plot(x, h_init, "o-", label="tas initial")
        plt.plot(x, h_ajout, "o-", label="après ajout")
        plt.plot(x, h_final, "o-", label="après stabilisation")
        plt.xlabel("indice")
        plt.ylabel("hauteur")
        plt.title(f"Ajout de grains – itération {k}")
        plt.grid(alpha=0.3)
        plt.legend()
        plt.tight_layout()
        plt.savefig(f"plots/ajout_{k}.png", dpi=150)
        plt.close()

    print("Graphes créés :")
    print("- plots/stabilisation.png")
    print("- plots/vent.png")
    for k in range(1, len(blocs) + 1):
        print(f"- plots/ajout_{k}.png")


if __name__ == "__main__":
    main()