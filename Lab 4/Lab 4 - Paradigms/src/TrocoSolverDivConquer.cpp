#include <TrocoSolver.h>

void TrocoSolverDivConquer::solve(const std::vector<unsigned int> &denom,unsigned int value, std::vector<unsigned int> &coins) {
    this->recursivecalls = 0;   
    coins.resize(denom.size(), 0); 
    int q = 0;
    this->solveRecursive(denom, value, coins, q);
}//solve

void TrocoSolverDivConquer::solveRecursive( const std::vector<unsigned int> &denom, unsigned int value, std::vector<unsigned int> &coins, int &q){
    this->recursivecalls++;
    if(value == 0) return;
    q = value;
    for (int i = 0; i < denom.size(); i++){
        if(denom[i] <= value){
            std::vector<unsigned int> subcoins(denom.size(), 0);
            int subq = 0;
            this->solveRecursive(denom, value - denom[i], subcoins, subq);
            if(1 + subq <= q){
                q = 1 + subq;
                (coins = subcoins, coins[i]++);
            }
        }
    }
}