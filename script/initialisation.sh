#!/bin/bash
if [ -d "data" ];then
  echo "Initialisation";
else
echo "Problème il manque le dossier data Cccccréation !";
mkdir data
fi
cd script
touch structure.txt
