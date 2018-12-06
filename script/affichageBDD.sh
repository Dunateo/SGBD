#!/bin/bash
cd data
echo -e "\033[35;1mLa liste des BDD:\033[0m"
echo -e "\033[33m------nb:\033[0m"
ls -1 | wc -l
echo -e "\033[33m------nom:\033[0m"
ls -C
