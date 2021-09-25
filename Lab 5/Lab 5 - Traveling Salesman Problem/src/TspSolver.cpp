#include <TspSolver.h>
#include <vector>
#include <algorithm>
#include <iostream>

// Classe para auxiliar o algoritmo de Prim a seguir as convenções
class MetaCity {
    City c, nearest;
    // c é a City representada, e nearest é a City mais próxima de c que já está na árvore
public:
    int distToTree; // Simplesmente a distância entre c e nearest; é o 1o critério de desempate
    MetaCity() {(c = City(), nearest = City()); distToTree = -1;} // Construtor default
    MetaCity(City _c, City treeCity){
        c = _c;
        nearest = treeCity;
        distToTree = c.disti(nearest);
    }
    bool operator< (const MetaCity a){
        if(this->distToTree == a.distToTree){
            if(this->nearest.getId() == a.nearest.getId()){
                return this->c.getId() > a.c.getId();
            }else return this->nearest.getId() > a.nearest.getId();
        }else return this->distToTree > a.distToTree;
    } // Sobrecarga do operador < para facilitar a criação do minheap seguindo a convenção
    void updateNearest(City treeCity){
        if(c.disti(treeCity) < distToTree){
            nearest = treeCity; 
            distToTree = c.disti(nearest);
        }else if(c.disti(treeCity) == distToTree && treeCity.getId() < nearest.getId())
            nearest = treeCity;
    } // Toda vez que um novo nó é agregado à árvore, as
      // distâncias aos demais nós devem ser atualizadas
    
    City getCity() {return c;}
    City getNearest() {return nearest;}
};

void TspSolver::solve(TspReader &tr, std::vector<int> &percourse) {
    /* Constroi T via Prim */
    // Cria um minheap de MetaCity (City + metadados)
    std::vector<MetaCity> heap;
    
    City root, c;
    tr.getCities(root);
    while(tr.getCities(c)){
        (heap.push_back(MetaCity(c, root)),
        std::push_heap(heap.begin(), heap.end()));
    } // Cria o heap já com os metadados de distância para a raiz
    
    // T é a representação em lista de adjacências da árvore de espalhamento
    std::vector<Vertex> T(tr.getNumCities());
    T[root.getId()-1] = Vertex();

    // Repete até esvaziar o heap: extrai o min, atualiza os nodes, ajusta o heap
    while(!heap.empty()){
        bool showHeap = false; // Esse bloco só serve pra debugar
        if(showHeap){
            for(auto it = heap.begin(); it != heap.end(); it++){
                std::cout << it->distToTree << ", ";
                std::cout << it->getNearest().getId() << ", ";
                std::cout << it->getCity().getId() << std::endl;
            }
            std::cout << "----------------------------------------" << std::endl;
        }

        // Pega o nó mais próximo/adjacente ao nó de menor índice em T/de menor índice
        MetaCity mc = heap.front(); 
        // Bota na árvore ...
        T[mc.getNearest().getId()-1].addNeighbor(mc.getCity().getId());
        T[mc.getCity().getId()-1] = Vertex();
        T[mc.getCity().getId()-1].addNeighbor(mc.getNearest().getId());
        // Tira do heap
        (std::pop_heap(heap.begin(), heap.end()),
        heap.pop_back());

        // Atualiza as distâncias porque a árvore T tem um novo nó
        for(auto it = heap.begin(); it != heap.end(); it++) 
            it->updateNearest(mc.getCity());
        
        // Ajusta o heap
        std::make_heap(heap.begin(), heap.end());
    }
    
    /* Faz o percurso em pre ordem de T, adicionando 
     * cada vertice a C na primeira visitação 
     * */
    PreOrder(0, T, percourse);

    bool showTree = false; // Mais um bloco pra debugação
    if(showTree){
    for(int i = 0; i < T.size(); i++){
        std::cout << i+1 << " | ";
        T[i].listNeighbors();
        std::cout << std::endl;
    }}
}

// Percurso em pre ordem simples
void TspSolver::PreOrder(int v, std::vector<Vertex> &T, std::vector<int> &percourse){
    (T[v].visit(), percourse.push_back(v+1));
    while(T[v].next < T[v].sizeNeighbors()){
        if(!T[T[v].getNext() - 1].visited) {
            PreOrder(T[v].getNext() - 1, T, percourse);}
        T[v].next++;
    }
}