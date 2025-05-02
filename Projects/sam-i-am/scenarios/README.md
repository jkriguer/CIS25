# /scenarios/
This is the directory where scenario binaries are saved/loaded as needed by the program. Here's an example of how they're structured, as of save version 1.

```c+
const std::vector<char> scenario = {
10, //validator
3, //static count
0, 26, 22, //player
2, 23, 18, //city 1
2, 30, 18, //city 2
8, //mobile count
2, 0, 7, 27, 10, //fighter kills interdictor turn 2
1, 1, 2, 11, 18, //interdictor kills city 1 turn 3
1, 0, 4, 30, 28, //bomber kills city 2 turn 5
1, 0, 4, 23, 28, //bomber kills city 1 turn 5
1, 1, 6, 46, 18, //interdictor kills city 2 turn 4
1, 3, 0, 32, 12, //command
0, 1, 6, 31, 19, //cropduster
0, 2, 3, 15, 28, //concorde
-10 //exit validator
};
}; 
```