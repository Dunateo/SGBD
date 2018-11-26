#!/bin/bash
cd data
echo "La liste des BDD:"
echo "-nb:"
ls -1 | wc -l
echo "-nom:"
ls
ls > ../script/structure.txt
echo "Le nom de la sélection ?"
read nombdd
cd $nombdd
ls
