# Hangman
This program is a simple word game where the user guesses letters to determine a hidden word.<br>

> It must be named *wordlist.txt* and contain a list of possible words to guess separated by linebreaks.
In testing, I used [this list from Wordle](https://gist.github.com/scholtes/94f3c0303ba6a7768b47583aff36654d#file-wordle-la-txt).
You can either download the file and rename it as needed or paste its contents into the blank wordlist file cloned from this repo.

How to play:
* TODO
* TODO AGAIN
* TODO ALSO
* TOMAYBEDO

Error Codes:<br>
* <b>-10</b>: There was no word list file present. Please make sure that there is a file called "wordlist.txt" in the directory you run this program.
* <b>-11</b>: The word list file was present but contained no words. This game generates a puzzle using 2 different random words, so you must have at least 2 words in the word list.
* <b>-12</b>: The word list file was present but didn't have enough words. See explanation for **-11** for more info.