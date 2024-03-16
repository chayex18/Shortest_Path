# Graph Implementation 
The Graph class shows an implementation of a graph in C++ with an adjacency list. This program provides an implementation of a weighted directed graph. This class will support the addition of vertices and edges, and it can find the shortest path between two vertices by using Dijkstra's algorithm.

## Table of contents
- Usage
- API Referance
- Compile
- Contributor

## Usage
1. Creating a Graph from File: 
- The program will read an input from a text file (.txt), where each line in the file represents an edge between two vertices and its weight in the following format: '<'Vertex'><'Vertex'><'Weight'>'

2. Operations:
- Display all vertices in the graph
- Find the shortest path between two vertices.
- Exit the program.

## API Reference
### Constructor
- #### Graph()
Initialize an empty graph as an adjacency list.
### Destructors
- #### ~Graph()
Clears adjacency list and frees memory.
### Vertex Operations
- #### void addVertex(std::string label)
Adds Vertex with specified label to custom graph.
- #### bool hasVertex(const std::string& label)
Checks if a Vertex with specified label exist on graph.
### Edge Operations
- #### void addEdge(std::string label1, std::string label2, unsigned long weight)
Adds an edge between two specified vectors and it assigns a weight to it.
- #### bool hasEdge(const std::string& label1, const std::string& label2)
Checks if an edge between two specified Vertex exist on graph.
### Shortest Path
- #### unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
Finds the shortest path from Vertex "startLabel" to Vertex "endLabel" by using Dijkstra's algorithm. It returns the total distance as an unsigned long and updates the "path" vector with the vertices to the shortest path.
### Additional Functions
- #### int extractInputs(const std::string& str, std::string*& inputs)
This function finds the number of elements in the text file.
### Main Function
- This function will initialize a graph object and processes user commands in a loop
- It will also display a menu option to interact with the graph based on user input

## Compile
To properly compile the program it is necessary to have a text file with the elements of the graph properly stated in the format '<"vertex"><"vertex"><"weight">'. Each line represents an edge between two vertices and its weight. Example: <'hello'><'goodbye'><6> would represent an edge from vertex 'hello' to vertex 'goodbye' with weight of 6. Also it is important that the file is in format .txt

#### The program must be in the same directory as the .txt file in order to properly function.

Once everything is in the correct position by the use of the terminal you will navigate to the directory where the program is located, and you will proceed to type the following line in the terminal:

- g++ -std=c++17 -Wall Shortest_Path.cpp 

After the program properly compiled you will have to type the following line in the terminal to run it:

- ./a.out

Program will execute and ask you to type the name of the file (It is important to type it with the correct format - Example: "filename.txt"). To properly illustrate this, the zip files contains a graph example which is called Graph.txt. Once the file was properly read, the terminal will prompt the message: "Graph was succesfully created!"

The program will display a menu that can be interacted by typing the numbers between 1 to 3. Once the user is done, you can type the number '3' to Exit the program.

## Contributor
- Yeixon Chacon - U24830068
