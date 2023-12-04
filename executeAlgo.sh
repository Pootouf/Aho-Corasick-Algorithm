./genereTexteEtMots.sh
countResults=$(find results/ -type f | wc -l)
if ((countResults>0))
then
  rm results/*
  echo "Ancien résultat effacé"
fi

for alphabetSize in 2 4 20 70
do
	for algo in ac-matrice ac-hachage
	do
	  text=texts/texts${alphabetSize}.txt
	  word=words/words${alphabetSize}min5max15.txt
	  echo Nombre d\'occurences dans ${text} pour $word avec ${algo}
	  { time ./${algo} ${word} ${text}; } 2> results/result${algo}${alphabetSize}min5max15.txt
	  word=words/words${alphabetSize}min15max30.txt
    echo Nombre d\'occurences dans ${text} pour $word avec ${algo}
	  { time ./${algo} ${word} ${text}; } 2> results/result${algo}${alphabetSize}min15max30.txt
	  word=words/words${alphabetSize}min30max60
    echo Nombre d\'occurences dans ${text} pour $word avec ${algo}
	  { time ./${algo} ${word}.txt ${text}; } 2> results/result${algo}${alphabetSize}min30max60.txt
	  echo
	done
done