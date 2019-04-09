//Written By James Lindsay
//Student Number - 16332526
//Email - j.lindasy1@nuigalway.ie

#include <iostream>
#include <random>

//Defining NeighbourGraph which will form the network under the values inputted by the user
int** NeighbourGraph(int N, double p, double q);

//Main Method
int main(void) {
    
    //N for the number of vertices
    int N;
    //p and q
    double p, q;
    
    //Outputting to the user what the program is going to do
    std::cout << "***************************************\n";
    std::cout << "This program will create Neighbour Graphs (Described below) and then extract information from the simulated graphs to check to see whether the graph is connected or not!\n";
    std::cout << "***************************************\n";

    //Explaining to the user what they are about to do
    std::cout << "\n***************************************\n";
    std::cout << "You will now input N, p and q, with p>>q. \nThis will create a network with N vertices. \nThe probability that there is an edge between nodes i and j is p if i and j have a neighbour in common. \nOtherwise it's q\n";
    std::cout << "***************************************\n";

    //Prompting the user to input N
    std::cout << "\nPlease enter N (The number of vertices you would like in your network): ";
    std::cin >> N;
    
    //Prompting the user to input p
    std::cout << "\nPlease enter p: ";
    std::cin >> p;
    
    //Prompting the user to input q
    std::cout << "\nPlease enter q: ";
    std::cin >> q;

    int** network = NeighbourGraph(N, p, q);
    for(int i = 0; i < N; i++){
        //Adding a line breaker after every time so that the output has the apperance of a matrix
        std::cout << "\n\n";
        for(int j = 0; j < N; j++){
            //Outputting to the user the network in the form of a symmetric matrix
            std::cout << " " << network[i][j] << " ";
        }//end jfor
    }//end ifor
    
    //Implementing the All Pairs Shortest Path Algorithm
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i; j++){
            if(network[i][j] == 0){
                network[i][j] = INFINITY;
                network[j][i] = INFINITY;
            }//end if
        }//for jfor
    }//end ifor
    
    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < i; j++){
                if(network[i][j] > network[i][k] + network[k][j]){
                    network[i][j] = network[i][k] + network[k][j];
                    network[j][i] = network[i][k] + network[k][j];
                }//end if
            }//end jfor
        }//end ifor
    }//end kfor
    
    //outputing
    std::cout << "\n\n\n***************************************";
    std::cout << "\nHere is a matrix representation of the shortest path between any two vertices in the network";
    std::cout << "\n***************************************";

    for(int i = 0; i < N; i++){
        //Adding a line breaker after every time so that the output has the apperance of a matrix
        std::cout << "\n\n";
        for(int j = 0; j < N; j++){
            //Outputting to the user the network in the form of a symmetric matrix
            std::cout << " " << network[i][j] << " ";
        }//end jfor
    }//end ifor

    //Defining a boolean to say that the graph is connected
    bool connected = true;
    
    //Starting a loop that will iterate through the network and check to see if it is connected
    //This is done by iterating through and seeing if any of the values in the shortest distance graph are greater than the number of vertices in the graph as the shortest distance cannot possible be greater than the number of vertices meaning it is diverging and thus not a connected graph
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            
        if(network[i][j] > N){
            connected = false;
        }//end if
       }//end jfor
    }//end for
    
    std::cout << "\n\n***************************************\n";
    //If statement to tell the user if the network is connected or not
    if(connected == true){
        std::cout << "The network is connected\n";
        std::cout << "***************************************\n";
        //Outputting that there is one compnent if it is connected
        std::cout << "There is only 1 component to this network\n\n";
    }//end if
    else{
        std::cout << "The network is not connected\n";
        std::cout << "***************************************\n";
        std::cout << "There is more than 1 connected components to this network\n\n";
    }//end else

    return 0;
}//end main

//This part of the code will be the algorithm to simulate the Network assigned
int** NeighbourGraph(int N, double p, double q){
    //If statement to check to see if q is greater than q
    if(p <= q || p > 1 || q <= 0){
        std::cerr << "p must be greater than q \n";
        return(0);
    }//end if
    
    //Else runs if q is greater than q
    else{
        int** network = 0;
        network = new int*[N];
        for(int i = 0; i < N; i++){
            network[i] = new int[N];
            for(int j = 0; j < N; j++){
                network[i][j] = 0;
            }//end jfor
        }//end for ifor
        
        for(int i = 0; i < N; i++){
            for(int j = 0; j < i; j++){
                if(i != j){
                    bool neighbour = false;
                    for(int k = 0; k < N; k++){
                        if(network[i][k] == 1 && network[k][j] == 1){
                            neighbour = true;
                        }//end if
                    }//end kfor
                    double r = (double)rand() / ((double)RAND_MAX + 1);
                    if((neighbour && r <= p) || (!neighbour && r <= q)){
                        network[i][j] = 1;
                        network[j][i] =1;
                    }//end if
                }//end if
            }//end jfor
        }//end ifor
        
        //Outputting to the user the completed network
        std::cout << "\n***************************************";
        std::cout << "\nHere is the completed network (Being outputted as a symmetrical matrix):";
        std::cout << "The number 1 represents a connection between two nodes";
        std::cout << "\n***************************************";
        return network;
    }//end else
}//end network former
