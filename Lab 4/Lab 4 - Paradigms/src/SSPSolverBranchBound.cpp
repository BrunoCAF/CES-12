#include <SubsetSumSolver.h>


bool SSPSolverBranchBound::solve(const std::vector<long> &input, long value, std::vector<char> &output){
    output.resize(input.size(), false);
    // Criamos o vetor das somas parciais para auxiliar na regra de poda #3
    std::vector<long> partial_sum(input.size(), input[0]);
    for(int i = 1; i < input.size(); i++)
        partial_sum[i] = partial_sum[i-1] + input[i];
    // Passando partial_sum em vez de input, podemos obter input[n] com apenas uma subtração
    // Por outro lado, para obter partial_sum[n-1] a partir de input, seria necessária uma 
    // soma de n-1 termos em cada chamada do método recursivo.

    return BranchBoundRecursion(input.size()-1, value, output, partial_sum);
}

bool SSPSolverBranchBound::BranchBoundRecursion(int n, long value, std::vector<char> &output, const std::vector<long> &partial_sum){    
    // Caso base: só temos o item input[0]
    if(n == 0) return ((partial_sum[n] == value) ? (output[n] = true, true) : (value == 0));
    if(value == 0) return true; // Regra de poda #1: se o value=0 é pq já encontrou solução

    long input = partial_sum[n] - partial_sum[n-1]; // Obtemos input[n] a partir de partial_sum
    bool com = false, sem = false; // Para sinalizar se existe solução *com* ou *sem* o item input[n]

    // Regra de poda #2: item maior do que a soma requerida, não abre a subtree *com* ele
    if(input <= value) 
        com = BranchBoundRecursion(n-1, value-input, output, partial_sum);
    // Regra de poda #3: soma parcial insuficiente para atingir a soma, não abre a subtree *sem*
    // Regra de poda #4: se já encontramos solução *com* o item, não precisa procurar *sem* ele
    if(!com && (partial_sum[n-1] >= value))
        sem = BranchBoundRecursion(n-1, value, output, partial_sum);

    output[n] = com;
    return com || sem;
}