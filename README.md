# t3c — Table de Correspondance Chaîne-Condensat

Deux modes : **G** (générer une table) et **L** (rechercher des chaînes depuis leurs condensats).

---

## Prérequis & compilation

**Sans Docker**
```bash
sudo apt-get install gcc make libssl-dev
make
```

**Avec Docker**
```bash
docker build -t t3c .
```

---

## Utilisation

### Mode G
```bash
./t3c G -i <dictionnaire> -o <table> [-a <algo>]
```
| Option | Obligatoire | Description |
|---|---|---|
| `-i` / `--input` | oui | Dictionnaire (une chaîne par ligne) |
| `-o` / `--output` | oui | Fichier T3C à créer |
| `-a` / `--algo` | non | `md5` (défaut) ou `sha256` |

### Mode L
```bash
./t3c L -t <table>
```
| Option | Obligatoire | Description |
|---|---|---|
| `-t` / `--table` | oui | Table T3C à charger |

Les condensats arrivent sur `stdin`, un par ligne. Une ligne de résultat par condensat (vide si non trouvé).
Deux façons de fournir les condensats :
- **Pipe** : `echo "<hash>" | ./t3c L -t table.t3c`
- **Interactif** : lancer `./t3c L -t table.t3c`, taper les hashes un par ligne, terminer avec `Ctrl+D`

---

## Avec Docker

```bash
# Mode G
docker run --rm -v $(pwd):/data t3c G -i /data/dictionnaire.txt -o /data/table.t3c

# Mode L
echo "<hash>" | docker run --rm -i -v $(pwd):/data t3c L -t /data/table.t3c
```

> `-v $(pwd):/data` monte votre dossier courant dans le conteneur. Les fichiers en entrée et en sortie doivent être préfixés par `/data/`.

---

## Exemple complet

```bash
./t3c G -i dictionnaire.txt -o table.t3c
echo "5f4dcc3b5aa765d61d8327deb882cf99" | ./t3c L -t table.t3c
# -> password
```

---

## Codes de retour

- `0` : exécution normale (y compris condensat non trouvé)
- non nul : erreur (argument manquant, fichier introuvable, dictionnaire vide…)
- `stdout` : résultat uniquement — logs et erreurs sur `stderr`
