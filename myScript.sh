#!/bin/bash

EXEC_DIR="codeC"
EXEC_NAME="wildwater"
EXEC_PATH="$EXEC_DIR/$EXEC_NAME"
DATA_FILE="c-wildwater.csv"

start_time=$(date +%s)

show_help() {
    echo "Usage: ./myScript.sh [COMMAND] [ARGS]"
    echo "Commands:"
    echo "  histo [max|src|real]  : Génère l'histogramme des usines."
    echo "  leaks [FactoryID]     : Calcule les fuites pour une usine donnée."
    echo "  -h, --help            : Affiche ce message."
}


if [ $# -eq 0 ]; then
    echo "Erreur : Aucun argument fourni."
    show_help
    exit 1
fi


if [ ! -f "$EXEC_PATH" ]; then
    echo "L'exécutable n'existe pas. Compilation en cours..."
    make -C "$EXEC_DIR"
    
    if [ $? -ne 0 ]; then
        echo "Erreur : La compilation a échoué."
        exit 2
    fi
fi


COMMAND=$1

case "$COMMAND" in
    "histo")
        if [ -z "$2" ]; then
            echo "Erreur : Argument manquant pour 'histo'. Choisir parmi : max, src, real."
            exit 1
        fi
        
        SUB_ARG=$2
        if [[ "$SUB_ARG" != "max" && "$SUB_ARG" != "src" && "$SUB_ARG" != "real" ]]; then
             echo "Erreur : Argument invalide '$SUB_ARG'. Choisir parmi : max, src, real."
             exit 1
        fi

        echo "Traitement Histogramme ($SUB_ARG) en cours..."
        
        "$EXEC_PATH" "$DATA_FILE" "histo" "$SUB_ARG"
        

        if [ $? -ne 0 ]; then
            echo "Erreur lors de l'exécution du programme C."
            exit 3
        fi


        echo "Génération du graphique..."
        gnuplot -e "filename='${SUB_ARG}.dat'; outputname='${SUB_ARG}.png'" graph_script.gnu
        echo "Graphique généré : ${SUB_ARG}.png"
        ;;

    "leaks")
        if [ -z "$2" ]; then
            echo "Erreur : Identifiant d'usine manquant."
            exit 1
        fi
        
        FACTORY_ID="$2"
        echo "Calcul des fuites pour l'usine : $FACTORY_ID"

        "$EXEC_PATH" "$DATA_FILE" "leaks" "$FACTORY_ID"

        if [ $? -ne 0 ]; then
            echo "Erreur lors de l'exécution du programme C."
            exit 3
        fi
        echo "Résultat ajouté au fichier de sortie."
        ;;

    "-h" | "--help")
        show_help
        ;;

    *)
        echo "Erreur : Commande inconnue '$COMMAND'."
        show_help
        exit 1
        ;;
esac

# --- 5. GESTION DU TEMPS (Fin) ---
end_time=$(date +%s)
duration=$((end_time - start_time))
echo "Durée totale du traitement : $duration secondes."

exit 0