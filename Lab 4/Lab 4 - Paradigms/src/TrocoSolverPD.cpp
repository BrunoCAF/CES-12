#include <TrocoSolver.h>

void TrocoSolverPD::solve(const std::vector<unsigned int> &denom,unsigned int value, std::vector<unsigned int> &coins) {
    coins.resize(denom.size(), 0); 
    std::vector<unsigned int> qtd(value+1, 0), last(value+1, -1);
    for(int val = 1; val <= value; val++){
        unsigned int qtdProv = val, lastProv = 0;
        for(int j = 0; j < denom.size(); j++){
            if(denom[j] > val) continue;
            if(qtd[val - denom[j]] + 1 < qtdProv)
                (qtdProv = qtd[val - denom[j]] + 1, lastProv = j);
        }
        (qtd[val] = qtdProv, last[val] = lastProv);
    }
    for(int val = value; val > 0; val -= denom[last[val]]) coins[last[val]]++;
}//solve
