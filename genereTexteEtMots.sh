countTexts=$(find texts/ -type f | wc -l)
if ((countTexts>0))
then
  rm texts/*
  echo "Ancien texte effacé"
fi

countWords=$(find words/ -type f | wc -l)
if ((countWords>0))
then
  rm words/*
  echo "Ancien mots effacé"
fi

for a in 2 4 20 70
do
	./genere-texte 5000000 ${a} > texts/texts${a}.txt
	./genere-mots 100 5 15 ${a} > words/words${a}min5max15.txt
	./genere-mots 100 15 30 ${a} > words/words${a}min15max30.txt
	./genere-mots 100 30 60 ${a} > words/words${a}min30max60.txt
done
