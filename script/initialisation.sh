#!/bin/bash
if [ -d "data" ];then
  echo "Initialisation";
else
echo "Problème il manque le dossier data Cccccréation !";
mkdir data
fi
cd script
touch structure.txt
cd ../data/
ls -1 | wc -l> ../script/structure.txt
ls >> ../script/structure.txt
ls -1 -d */* | wc -l>> ../script/structure.txt
ls -d */* >> ../script/structure.txt
