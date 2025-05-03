```
   __|__
____(=)____		   _____ ___    __  ___   ____   ___    __  ___
 °°     °°		  / ___//   |  /  |/  /  /  _/  /   |  /  |/  /
                          \__ \/ /| | / /|_/ /   / /   / /| | / /|_/ / 
  ^  			 ___/ / ___ |/ /  / /  _/ /   / ___ |/ /  / /  
  |   ^			/____/_/  |_/_/  /_/  /___/  /_/  |_/_/  /_/   
      |   ^
          |
```
> ### [Video presentation of program and code](https://example.com)

Installation instructions:<br>
1. `git clone -n --depth=1 --filter=tree:0 https://github.com/jkriguer/CIS25/`
1. `cd CIS25`
1. `git sparse-checkout set --no-cone /Projects/sam-i-am`
1. `git checkout`
1. `mkdir build`
1. `cd build`
1. `cmake ..`

SAM-I-AM is a grid-based strategy game where you control a SAM battery to identify and destroy threats to protect your cities.<br>
Game Instructions:<br>
1. You'll have 3 options:
    - Identify: Attempt to identify an unknown aircraft.
    - Shoot: Fire a missile at a known enemy contact.
    - Quit: Close the game.
1. Protect all cities from enemy aircraft.
1. Avoid collateral damage.
1. Win by destroying all enemies.
