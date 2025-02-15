# Hangman
  ```
    .========.     _  _                                      
    || /     |    | || | __ _  _ _   __ _  _ __   __ _  _ _  
    ||/     _|_   | __ |/ _` || ' \ / _` || '  \ / _` || ' \ 
    ||     (x_x)  |_||_|\__,_||_||_|\__, ||_|_|_|\__,_||_||_|
    ||     /| |\                    |___/                    
    ||    ^ |_| ^
  ========= / \ ====
  ||              ||
```

This program is a simple word game where the user guesses letters to determine a hidden phrase.<br>

[Video presentation of program and code](TODO)

How to play:
1. Two random words will be randomly chosen for you to guess.
2. Try guessing letters to fill in the blanks.
3. Only letters will be accepted as input. If you try to enter more than one character, only the first will be processed.
4. Get a letter wrong, and the hanged man will be drawn (you'll lose lives).
5. Guess all the letters and you win!
6. Run out of lives before you guess all the letters and it's game over.

Error Codes:<br>
* <b>-10</b>: There was no word list file present. Please make sure that there is a file called "wordlist.txt" in the directory you run this program.
* <b>-11</b>: The word list file was present but contained no words. This game generates a puzzle using 2 different random words, so you must have at least 2 words in the word list.
* <b>-12</b>: The word list file was present but didn't have enough words. See explanation for **-11** for more info.