#!/bin/bash
if [ -d "data" ];then
  echo "démarrage programme";  
else
echo "Problème il manque le dossier data Cccccréation !";
mkdir data
fi
