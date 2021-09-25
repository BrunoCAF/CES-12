#ifndef TSP_SOLVER
#define TSP_SOLVER


#include <TspReader.h>
#include <vector>

// Classe para representar a árvore de espalhamento em lista de adjacências
class Vertex {
    std::vector<int> adjIndex; // Lista de vizinhos do vértice
public:
    bool visited; // Estado no percurso
    Vertex() {visited = false; next = 0;}
    void visit() {visited = true;}
    void addNeighbor(int idx) {adjIndex.push_back(idx);}
    int next;
    int getNext() {return adjIndex[next];}
    int sizeNeighbors() {return adjIndex.size();}
    void listNeighbors() { // Serve só pra debugar
        for(int i = 0; i < adjIndex.size(); i++)
            std::cout << adjIndex[i] << " ";
    }
};

class TspSolver {
public:
    // you should fill percourse with a permutation that represents the TSP solution
    void solve(TspReader &tr, std::vector<int> &percourse); 
    
private:
    void PreOrder(int v, std::vector<Vertex> &T, std::vector<int> &percourse);
}; 

#endif
