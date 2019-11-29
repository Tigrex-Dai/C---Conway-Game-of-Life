#!/bin/sh
set -e

executable_name=bin/lavie

if command tput colors 2>/dev/null 1>&2 && [ "$(tput colors)" -ge 16 ]
then
  magenta_color="\033[35m"
  cian_color="\033[36m"
  reset_color="\033[0m"
fi

num_grilles=8
tests_end_generation=50

printf "[${cian_color}Test cyclique${reset_color}] : Exécution sur %s$tests_end_generation générations\n"
for grilles_id in $(seq $num_grilles)
do
  grille_file="grilles/grille$grilles_id.txt"
  printf "[${magenta_color}Test grille${reset_color}] : $grille_file\n"
  (i=;while [ $((i+=1)) -le $tests_end_generation ]; do echo;done; echo q) | "./$executable_name" "$grille_file" 1>/dev/null
done

printf "\n[${cian_color}Test non cyclique${reset_color}] : Exécution sur %s$tests_end_generation générations\n"
for grilles_id in $(seq $num_grilles)
do
  grille_file="grilles/grille$grilles_id.txt"
  printf "[${magenta_color}Test grille${reset_color}] : $grille_file\n"
  (echo c;i=;while [ $((i+=1)) -le $tests_end_generation ]; do echo;done; echo q) | "./$executable_name" "$grille_file" 1>/dev/null
done

printf "\n[${cian_color}Test vieillissement cyclique${reset_color}] : Exécution sur %s$tests_end_generation générations\n"
for grilles_id in $(seq $num_grilles)
do
  grille_file="grilles/grille$grilles_id.txt"
  printf "[${magenta_color}Test grille${reset_color}] : $grille_file\n"
  (echo v;i=;while [ $((i+=1)) -le $tests_end_generation ]; do echo;done; echo q) | "./$executable_name" "$grille_file" 1>/dev/null
done

printf "\n[${cian_color}Test vieillissement non cyclique${reset_color}] : Exécution sur %s$tests_end_generation générations\n"
for grilles_id in $(seq $num_grilles)
do
  grille_file="grilles/grille$grilles_id.txt"
  printf "[${magenta_color}Test grille${reset_color}] : $grille_file\n"
  (echo v;echo c;i=;while [ $((i+=1)) -le $tests_end_generation ]; do echo;done; echo q) | "./$executable_name" "$grille_file" 1>/dev/null
done
