#!/bin/bash

bash fils.sh &
CHILD_PID=$!

echo "Lancement de l'enfant avec PID $CHILD_PID depuis le parent (PID $$)."

sleep 2
echo "Fin du parent (PID $$)."
