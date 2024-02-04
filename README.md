# Aho-Corasick-Algorithm

The Aho-Corasick Algorithm is an algorithm that allows you to search efficiently in a text a set of words. The executable will scan the text with only one pass and then return the number of occurrences found
This application contains a word and a text generator, and an implementation of the Trie of the algorithm with two methods : a matrix or a hash table

## Installation

You will need gcc installed on your computer, and the make command if you want to use the makefile
Then, you can use the following command to compile the code in the project directory : 
```
  make
```
You can then launch the program by using the two executables with the implementation of your choice, ac-matrice or ac-hachage

For the python application, you need python3 installed.
You can then install matplotlib with :
```
  pip install matplotlib
```


## Usage

The executables take two file for the input, one for the words and one for the text

The text generator take two arguments, the size of the text to generate and the number of letter in the generated alphabet
The word generator take four arguments, the number of word to generate, the minimum size of the words, the maximum size of the words and the number of letter in the generated alphabet. The words will have a length between the min and the max size.

Some scripts are also available :
- genereTexteEtMots.sh : generate some texts and words with predefined size of alphabets
- executeAlgo.sh : execute the algo on the texts and words generated with the previous scripts, and calculate some data on the execution, like the time taken
- script.sh : launch an example execution

A python application is also available to generate graph on the data calculated by executeAlgo.sh. The application require matlibplot and python installed on the device.

## License

The program is under [MIT License](https://github.com/Pootouf/Aho-Corasick-Algorithm/blob/main/LICENSE)
