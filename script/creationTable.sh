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
		echo -e "#----------\033[31m1\033[0m---\033[33mINT\033[0m"
		echo -e "#----------\033[31m2\033[0m---\033[33mCHAR\033[0m"
		echo -e "#----------\033[31m3\033[0m---\033[33mFLOAT\033[0m"
		echo -e "#----------\033[31m4\033[0m---\033[33mPRIMARY KEY\033[0m"
		echo "#-----------------------------------------#"
		read typeelem
			if [ $typeelem -eq 0 -o  $typeelem -gt 4 ] ;
			then
				echo "Ce type n'éxiste pas";
			else
			echo "Type de l'élements:"
        echo "#-----------------------------------------#"
    		echo -e "#----------\033[31m1\033[0m---\033[33mINT\033[0m"
    		echo -e "#----------\033[31m2\033[0m---\033[33mCHAR\033[0m"
    		echo -e "#----------\033[31m3\033[0m---\033[33mFLOAT\033[0m"
    		echo -e "#----------\033[31m4\033[0m---\033[33mPRIMARY KEY\033[0m"
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
