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
> ### [Video presentation of program and code](https://www.youtube.com/watch?v=UHvsPSl6sa0)

Installation instructions:<br>
1. `git clone -b project1-tests --single-branch -n --depth=1 --filter=tree:0 https://github.com/jkriguer/CIS25/`
2. `cd CIS25`
3. `git sparse-checkout set --no-cone /Projects/hangman`
4. `git checkout`

This program is a simple word game where the user guesses letters to determine a hidden phrase.<br>

How to play:
1. Two random words will be randomly chosen for you to guess.
2. Try guessing letters to fill in the blanks.
3. Only letters will be accepted as input. If you try to enter more than one character, only the first will be processed.
4. Get a letter wrong, and the hanged man will be drawn (you'll lose lives).
5. Guess all the letters and you win!
6. Run out of lives before you guess all the letters and it's game over.