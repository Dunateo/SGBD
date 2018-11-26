#!/bin/bash
cd data
echo "Création d'une BDD rentrer le nom:"
read nom
if [ -d $nom ];then
  echo "La BDD existe déja";
else
  mkdir $nom
  cd $nom
  echo "Combien de tables ?:"
  read nb
  for ((i=0 ; $i<$nb ; i++))
  do
    echo "Nom de table:"
    read deuxnom
    touch $deuxnom.txt
    echo "nombre d'élements dans la table ?:"
    read nbelem

    for ((h=0 ; $h<$nbelem ; h++))
    do
    echo "Nom élements:"
    read nomelem
    echo -n "$nomelem|">> $deuxnom.txt
    done

  done
  echo "la création de $nom"
fi
