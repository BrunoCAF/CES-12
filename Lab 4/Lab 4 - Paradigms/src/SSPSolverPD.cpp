#include <SubsetSumSolver.h>
#include<iostream>

 bool SSPSolverPD::solve(const std::vector< long> &input, long value, std::vector< char> &output) {
    
    std::vector< std::vector<bool> > B(input.size()+1, std::vector<bool>(value+1, false));
    for(int n = 0; n <= input.size(); n++) B[n][0] = true;
    long w, partial_sum = 0; //partial_sum é a soma de todos os inputs até uma dada linha
    output.resize(input.size(), false);

    for(int n = 1; n <= input.size(); n++){
        partial_sum += input[n-1];
        for(w = input[n-1]; w <= value; w++){ // para w < input[n-1] o resultado não depende desse valor
            if(w > partial_sum) break; // Não tem como atingir essa soma com os valores até essa linha
            B[n][w] = (B[n-1][w] || B[n-1][w - input[n-1]]);
            if(B[n][w]) for(int k = n+1; k <= input.size(); k++) B[k][w] = true;
            // Se a soma w é possível com os inputs até essa linha, será possível com os demais valores
        }
    }
    
    if(B[input.size()][value]){ // Se a soma não for possível, não perdemos tempo preenchendo o output
        for(int n = input.size(), w = value; w > 0; (w -= input[n], output[n] = true))
            while(B[n][w]) n--;
        // A cada laço nós subimos as linhas da tabela à procura do primeiro item que torna
        // aquela soma possível. Marcamos aquele item como utilizado e decrementamos a soma
    }
    return B[input.size()][value];
}