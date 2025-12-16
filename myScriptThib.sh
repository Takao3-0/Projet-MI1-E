#!/bin/bash
# Usage:
#   ./myScript.sh <csv> histo <max|src|real>
#   ./myScript.sh <csv> leaks "<ID_usine>"

START=$(date +%s%3N)
EXEC=./wildwater

err() { echo "Erreur: $1"; END=$(date +%s%3N); echo "Durée : $((END-START)) ms"; exit 1; }

# args
[ $# -lt 3 ] && err "Usage: $0 <csv> histo <max|src|real> | leaks <ID_usine>"
CSV="$1"; MODE="$2"; OPT="$3"

[ ! -f "$CSV" ] && err "Fichier introuvable: $CSV"

# build si nécessaire
if [ ! -x "$EXEC" ]; then
  make || err "Compilation échouée (make)"
fi

case "$MODE" in
  histo)
    [[ "$OPT" != "max" && "$OPT" != "src" && "$OPT" != "real" ]] && err "histo: option invalide ($OPT)"

    # filtres (uniquement ceux utiles)
    if [ "$OPT" = "max" ]; then
      awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' "$CSV" > Usine.txt || err "awk max"
      "$EXEC" "$CSV" histo max Usine.txt || err "C histo max"
    elif [ "$OPT" = "src" ]; then
      awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' c-wildwater_v0.dat > Usine.txt
      awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4}' "$CSV" > Source.txt || err "awk src"
      "$EXEC" "$CSV" histo src Usine.txt Source.txt || err "C histo src"
    else # real
      awk -F ';' '$1=="-" && $2!="-" && $3=="-" && $4!="-" && $5=="-" {print $2 ";" $4}' c-wildwater_v0.dat > Usine.txt
awk -F ';' '$1=="-" && $2!="-" && $3!="-" && $4!="-" && $5!="-" {print $2 ";" $3 ";" $4 ";" $5}' "$CSV" > SourceL.txt 
      "$EXEC" "$CSV" histo real Usine.txt SourceL.txt || err "C histo real"
    fi
    ;;

  leaks)
    # ici on ne filtre pas (tu peux filtrer plus tard si besoin)
    "$EXEC" "$CSV" leaks "$OPT" || err "C leaks"
    ;;

  *)
    err "Commande inconnue: $MODE"
    ;;
esac

END=$(date +%s%3N)
echo "Durée : $((END-START)) ms"
exit 0

