#!/bin/bash
cd data
echo "La liste des BDD:"
echo "-nb:"
ls -1 | wc -l
echo "-nom:"
ls -C
echo "Le nom de la sélection ?"
read nombdd
if [ -d $nombdd ];then
  cd $nombdd
  ls
  read -p "Appuyer sur une touche pour continuer ..."
else
  echo "la bdd n'existe pas"
fi
