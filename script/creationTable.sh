#!/bin/bash
cd data
ls
echo "Ajout d'une table le nom de la BDD ?:"
read nom
if [ -d $nom ];then
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
		echo "Type de l'élements:"
		echo "#-----------------------------------------#"
		echo "#----------1---INT------------------------#"
		echo "#----------2---CHAR-----------------------#"
		echo "#----------3---FLOAT----------------------#"
		echo "#----------4---PRIMARY KEY----------------#"
		echo "#-----------------------------------------#"
		read typeelem
			if [ $typeelem -eq 0 -o  $typeelem -gt 4 ] ;
			then
				echo "Ce type n'éxiste pas";
			else
			echo "Type de l'élements:"
				echo "#-----------------------------------------#"
				echo "#----------1---INT------------------------#"
				echo "#----------2---CHAR-----------------------#"
				echo "#----------3---FLOAT----------------------#"
				echo "#----------4---PRIMARY KEY----------------#"
				echo "#-----------------------------------------#"
				echo -n "$typeelem|">> $deuxnom.txt
				echo "Nom élements:"
				read nomelem
				echo -n "$nomelem|">> $deuxnom.txt
				fi
		done

  done
  echo "Hop ta table est crée dans $nom"
else
  echo "BDD N'EXISTE PAS LO"

fi
cd ..
ls -1 | wc -l> ../script/structure.txt
ls >> ../script/structure.txt
ls -1 -d */* | wc -l>> ../script/structure.txt
ls -d */* >> ../script/structure.txt
read -p "Appuyer sur une touche pour continuer ..."
