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
	  result=$({ time ./${algo} ${word} ${text};} 2>&1 >/dev/null)
	  grep=$(echo "$result" | grep "real")
	  echo "$grep" > results/result${algo}${alphabetSize}min5max15.txt
	  word=words/words${alphabetSize}min15max30.txt
    result=$({ time ./${algo} ${word} ${text};} 2>&1 >/dev/null)
    grep=$(echo "$result" | grep "real")
    echo "$grep" > results/result${algo}${alphabetSize}min15max30.txt
	  word=words/words${alphabetSize}min30max60.txt
	  result=$({ time ./${algo} ${word} ${text};} 2>&1 >/dev/null)
    grep=$(echo "$result" | grep "real")
    echo "$grep" > results/result${algo}${alphabetSize}min30max60.txt
	done
done