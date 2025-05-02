# /scenarios/
This is the directory where scenario binaries are saved/loaded as needed by the program. Here's an example of how they're structured, as of save version 1.

```c++
const std::vector<char> defaultScenario = { 
	10,//validator
	3, //static count
	2, 23, 18, //city 1
	0, 26, 22, //player
	2, 30, 18, //city 2
	5, //mobile count
	2, 1, 0, 26, 1, //friendly 1
	0, -1, 3, 49, 20, //neutral 1
	1, 1, 0, 16, 10, //hostile 1
	2, 1, 0, 25, 2, //friendly 2
	0, -1, 1, 10, 10, //neutral 2
	-10 //exit validator
}; 
```