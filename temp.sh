#!/bin/bash

# Nom du fichier source et de l'exécutable
SOURCE="programme.c"
EXECUTABLE="programme"

# Vérifier si l'exécutable existe
if [ ! -f "$EXECUTABLE" ]; then
    echo "L'exécutable $EXECUTABLE n'existe pas. Compilation en cours..."
    gcc "$SOURCE" -o "$EXECUTABLE"
    
    # Vérifier si la compilation a réussi
    if [ $? -ne 0 ]; then
        echo "Erreur : compilation échouée. Arrêt du script."
        exit 1
    fi
    echo "Compilation réussie."
fi

# Exécuter le programme
./"$EXECUTABLE"
CODE_RETOUR=$?

# Vérifier le code retour
if [ $CODE_RETOUR -eq 0 ]; then
    echo "Le programme s'est exécuté correctement."
    # Suite du traitement possible ici
else
    echo "Le programme a échoué avec le code retour $CODE_RETOUR."
    # Traiter l'erreur ou arrêter le script
    exit $CODE_RETOUR
fi

