#!/bin/bash
cd data
echo "La liste des BDD:"
echo "-nb:"
ls -1 | wc -l
echo "-nom:"
ls
ls > ../script/structure.txt
