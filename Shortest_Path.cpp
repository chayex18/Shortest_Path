/*
Yeixon Chacon - U24830068 
Shortest_Path.cpp - Program based on Dijkstra's Algorithm to find the Shortest Path of a graph in an external file - 02/04/2024
Program will prompt the user with options three options to interact with:
1. Display all vertices
2. Find the Shortest Path between two Vertices
3. Exit
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

class Graph
{
    private:
    std::vector<std::pair<std::string , std::vector<std::pair<std::string, unsigned long> > > > adjList; // Adjacency List to store the graph.
    public:
    Graph() {}   // Constructor

    ~Graph() // Destructor
    {
        adjList.clear();                // Clear all elements in vector.
        adjList.shrink_to_fit();        // Free memory.
    }  

    void addVertex(std::string label)    // Function to add Vertex to graph
    {
        if(hasVertex(label))                // If Vertex exist.
        {
            return;                     // Just return.
        }
        else
            adjList.emplace_back(label, std::vector<std::pair<std::string, unsigned long> >()); // Else add Vector to adjacency list.
    }

    bool hasVertex(const std::string& label)    // Boolean function to check if Vertex exist
        {
        for (const auto& pair : adjList) {      // Iterate through the adjacency list.
            if (pair.first == label)            // If label match with vertex.
            {
                return true;        // Return true.
            }
        }
        return false;      // Else return false.
    }

    bool hasEdge(const std::string& label1, const std::string& label2) {     // Boolean function to check if edges exist.
        for (const auto& pair : adjList) {                      // Iterate through the list
            if (pair.first == label1) {                         // If label1 match with vertex
                for (const auto &neighbor : pair.second) {       // Iterate through vertices
                    if (neighbor.first == label2) {             // If one of them matches with label2.
                        return true;                            // Return true.
                    }
                }
            }
        }
            return false;                                           // Else return false.
    }

    void addEdge(std::string label1, std::string label2, unsigned long weight)       // Function to add edge to Graph.
    {
        // Check if the vertices are the same
        if (label1 == label2)
        {
            throw std::runtime_error("A vertex cannot have an edge to itself - Please check original text file"); // Throw error message.
        }

        // Add the edge with the specific weight to the adjacency lists
        for (auto &pair: adjList)
        {
            if(pair.first == label1)
            {
                pair.second.push_back(std::pair<std::string, unsigned long> (label2, weight));
            }
        }
    }

    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)     // Dijkstra's Algorithm to find shortest path from vertex starLabel to vertex endLabel.
    {
        std::unordered_map<std::string, unsigned long> distance;        // unordered map to store distances
        std::unordered_map<std::string, std::string> previous;          // unordered map for previous vertex visited.
        std::priority_queue<std::pair<unsigned long, std::string>, std::vector<std::pair<unsigned long, std::string > >, std::greater<std::pair<unsigned long, std::string > > > pq;    // Priority Queue based on the weight of vertices.

        for (const auto &vertex : adjList) {
            distance[vertex.first] = 4294967295;     // Set all distances to ULONG_MAX
        }

        distance[startLabel] = 0;   // Set start distance to 0.
        pq.push(std::make_pair(0, startLabel));     // Push first pair to priority queue of startLabel with 0.

        while (!pq.empty()) {           // While priority queue is not empty.
            auto current = pq.top().second;     // Set current to string of element on top of queue.
            pq.pop();                   // Pop last element on priority queue.

            for (const auto &neighbor : adjList)    // Iterate through list 
            {
                if(neighbor.first == current)       // If Vertex equals string of element on top of queue.
                {
                    for(const auto &edge : neighbor.second)     // Iterate through other vertices.
                    {
                        unsigned long newDistance = distance[current] + edge.second;    // Create new distance by adding the distance to current with the weight its Vertices connected.

                        if(newDistance < distance[edge.first])  // If new Distance is less than the distance to Vertex, update elements and push to priority queue.
                        {
                            distance[edge.first] = newDistance;
                            previous[edge.first] = current;
                            pq.push(std::make_pair(newDistance, edge.first));
                        }
                    }
                    break;
                }
            }
        }

        path.clear();   // Clear path in case there is something in it.
        unsigned long totalDistance = distance[endLabel];   // Total distance will equal the distance to endLabel.
        std::string currentLabel = endLabel;    // currentLabel variable to store endLabel.

        while (!currentLabel.empty())       // While currentLabel is not empty, update path. 
        {
            path.insert(path.begin(), currentLabel);    
            currentLabel = previous[currentLabel];
        }

        return totalDistance;   // Return totalDistance.
    }
};

int extractInputs(const std::string& str, std::string*& inputs) { // Function to Extract count of inputs from text file with format <vertex><vertex><weight>
    int count = 0;
    size_t pos = 0;
    while (pos < str.length()) 
    {
        size_t start = str.find_first_of('<', pos); // First find '<'
        if (start == std::string::npos) break;
        
        size_t end = str.find_first_of('>', start + 1); // Then find where it ends '>'
        if (end == std::string::npos) break;

        inputs[count++] = str.substr(start + 1, end - start - 1);   // Count each input between '<' and '>'
        pos = end + 1;
    }
    return count;   // Return count
}


int main() {
    Graph l;    // construction of graph 'l'

    std::string input;
    std::cout << "Input name of file:" << std::endl;        // Prompt to input the name of file
    std::cin >> input;

    FILE *inputFile = fopen(input.c_str(), "r");            // Open the file for reading
    if (!inputFile) 
    {                                                       // Check if the file opened successfully
        std::cerr << "Error: Unable to open the file.\n";
        return 1;                                           // Return an error code
    }

    char mediator[100];                 // Mediator to store each line
    std::string out[100];               // String array out to store each line of text file
    int i = 0;
    while (fgets(mediator, sizeof(mediator), inputFile)) { // Read each line from the file
        out[i] = mediator;
        i++;
    }
    
    std::string Ver[100];               // String array to store all vertices
    unsigned long weight[100];          // long array to store all weights
    int f = 0, g = 1, v = 0, h = 1, index_ver = 0;      // Values to index the different elements in the "for" loop
    std::unordered_map<std::string, unsigned long> dic; // unordered map to store all vertices in order without repeating them.

    for(int j = 0; j != i; j++)
    {
        std::string *inputs = new std::string[out[j].length()]; // Allocate memory for inputs

        int count = extractInputs(out[j], inputs);  // Get count to control loop.

        for (int k = 0; k < count; ++k)         // "for" loop to construct graph with values from text file
        {
            if (g == (3 * h))                   // If it is a weight
            {
                weight[v] = std::stoul(inputs[k]);      // Convert string to unsigned long
                std::string First = Ver[index_ver];
                index_ver++;
                std::string Second = Ver[index_ver];
                l.addEdge(First,Second, weight[v]);     // Add edge with the two vertices and the weight.
                // Add values that control loop.
                index_ver++;
                h++;
                v++;
                g++;
            }
            else        // Else it is a vertex
            {
                Ver[f] = inputs[k];     // Set value to Ver array
                dic[Ver[f]];            // Add it to the unordered map of vertices.
                l.addVertex(Ver[f]);    // Add vertex to Graph.
                // Add values that control loop
                f++;
                g++;
            }
        }
        delete[] inputs; // Deallocate memory
    }


    int option;                 // Option on switch statement.
    unsigned long distance;     // Total Distance 
    int indexloop = 0;          // index of loop inside switch statement.
    std::vector<std::string> p; // Vector where path followed will be stored
    std::string fVertex;        // String to store First Vertex
    std::string sVertex;        // String to store Second Vertex

    std::cout << "Graph was succesfully created!" << std::endl;                     // Display if nothing went wrong.
    for (int i = 0; i < 50; ++i) {std::cout << "-";}    std::cout << std::endl;     

    do{ // Do-While Loop
        std::cout << "Please select one of the following options by typing the proper number: " << std::endl;       // Selection Prompt
        std::cout << "1 -> Display all vertices in the graph " << std::endl;
        std::cout << "2 -> Find the Shortest Path between two Vertices " << std::endl;
        std::cout << "3 -> Exit " << std::endl;
        if (!(std::cin >> option)) {                    // If option is not an int, this prevents program from crash.
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please choose a number between 1 and 3." << std::endl;
            continue; // Restart the loop
        }

        switch(option){             // Switch Statement
            case 1:
                std::cout << "The Graph contains the vertices:" << std::endl;       // Display all vertices in Graph
                for(const auto& pair: dic)
                {
                    std::cout << pair.first << std::endl;
                }
                for (int i = 0; i < 50; ++i) {std::cout << "-";}    std::cout << std::endl;
                break;

            case 2:
                std::cout << "Input the first vertex" << std::endl;     // Find shortest path by requesting first vertex
                std::cin >> fVertex;
                for(const auto& pair: dic)
                {
                    if(pair.first == fVertex) 
                    {
                        indexloop = 1;
                    }
                }
                if(indexloop != 1)
                {
                    std::cout << "Vertex not in Graph - Please select: Display all vertices option to view all available vertices" << std::endl;    // If Vertex not found
                    for (int i = 0; i < 50; ++i) {std::cout << "-";}    std::cout << std::endl;
                    break;
                }
                indexloop = 0;
                std::cout << "Input the Second vertex" << std::endl;    // Request Second Vertex
                std::cin >> sVertex;
                for(const auto& pair: dic)
                {
                    if(pair.first == sVertex) {indexloop = 1;}
                }
                if(indexloop != 1)
                {
                    std::cout << "Vertex not in Graph - Please select: Display all vertices in the graph option to view all available vertices" << std::endl;   // If Vertex not found
                    for (int i = 0; i < 50; ++i) {std::cout << "-";}    std::cout << std::endl;
                    break;
                }

                if(fVertex == sVertex)  // If Vertex are the same
                {
                    std::cout << "Distance from " << fVertex << " to " << sVertex << ": 0" << std::endl;
                }
                else
                {
                    distance = l.shortestPath(fVertex, sVertex, p);         // Find Shortest Path
                    if (distance == 4294967295)         // If there is no way to reach from fVertex to sVertex
                    {
                        std::cout << "There is no way to get from " << fVertex << " to " << sVertex << "- Please double check direction of vertices in original Graph located in text file." << std::endl;  // Display Message.
                        for (int i = 0; i < 50; ++i) {std::cout << "-";}    std::cout << std::endl;
                        break;
                    }
                    std::cout << "Distance from " << fVertex << " to " << sVertex << ": " << distance << std::endl; // Display shortest path
                    std::cout << "Path followed: " << std::endl;    // Display path followed
                    for(auto element : p)
                    {
                        std::cout << element << " ";
                    }
                    std::cout << std::endl;
                }

                for (int i = 0; i < 50; ++i) {std::cout << "-";}    std::cout << std::endl;
                break;

            case 3:                 // Exit case
                std::cout << "Thanks for using the program! " << std::endl; // Display message.
                l.~Graph();             // Destruct Graph
                fclose(inputFile);      // Close File
                return 0;               
            
            default:
                std::cout << "Invalid input. Please choose a number between 1 and 3" << std::endl;
                break;
        }
    } while (option < 1 || option > 3 || option != 3);  // While statement to control Loop

}
