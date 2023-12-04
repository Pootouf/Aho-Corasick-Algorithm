import matplotlib.pyplot as plt
import re


## Génère la courbe de comparaison des temps pour une implémentation et un alphabet
def createGraphByAlphabetSize(timesMat, timesHach, alphabetSize, sizes):
	index = 0
	fig, ax = plt.subplots()
	ax.plot(sizes, timesMat, linewidth=2.0, label = "ac-matrice")
	ax.plot(sizes, timesHach, linewidth=2.0, label = "ac-hachage")
	plt.legend()
	plt.title("Courbe des temps d'exécutions pour l'alphabet " + str(alphabetSize))
	plt.xlabel("Longueur moyenne des mots")
	plt.ylabel("Temps en secondes")
	plt.savefig("graph/alphabet" + str(alphabetSize))
	plt.show()

## Génère la courbe de comparaison des temps pour une taille moyenne de mots et une implémentation
def createGraphBySizes(timesMat, timesHach, size, alphabetSizes):
	index = 0
	fig, ax = plt.subplots()
	ax.plot(alphabetSizes, timesMat, linewidth=2.0, label = "ac-matrice")
	ax.plot(alphabetSizes, timesHach, linewidth=2.0, label = "ac-hachage")
	plt.legend()
	plt.title("Courbe des temps d'exécutions pour la taille de mots " + size)
	plt.xlabel("Taille de l'alphabet")
	plt.ylabel("Temps en secondes")
	plt.savefig("graph/size" + size)
	plt.show()

def getValueInSec(filename):
	f = open(filename)
	line = f.readline()
	timeString = line.split()[1]
	values = re.split("[m,s]", timeString)
	f.close()
	return float(values[0]) * 60 + float(values[1]) + float(values[2])/1000

def main():
	alphabetSizes = [2, 4, 20, 70]
	algos = ["ac-matrice", "ac-hachage"]
	sizes = ["min5max15", "min15max30", "min30max60"]

	for alphabetSize in alphabetSizes:
		timesMatrice = []
		timesHachage = []
		for algo in algos:
			for size in sizes:
				timeSec = getValueInSec("results/result" + algo + str(alphabetSize) + size + ".txt")
				if algo == algos[1]:
					timesMatrice.append(timeSec)
				else :
					timesHachage.append(timeSec)
		createGraphByAlphabetSize(timesMatrice, timesHachage, alphabetSize, sizes)

	for size in sizes:
		timesMat = []
		timesHach = []
		for alphabetSize in alphabetSizes:
			for algo in algos:
				timeSec = getValueInSec("results/result" + algo + str(alphabetSize) + size + ".txt")
				if algo == algos[1]:
					timesMat.append(timeSec)
				else :
					timesHach.append(timeSec)
		createGraphBySizes(timesMat, timesHach, size, alphabetSizes)




main()