#ifndef SSP_SOLVER
#define SSP_SOLVER


#include <vector>
#include <string>
#include <SubsetSumSolverAbstract.h>


class SSPSolverBranchBound : public SubsetSumSolverAbstract {

    
public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
    bool BranchBoundRecursion(int n, long value, std::vector<char> &output, const std::vector<long> &partial_sum);
    virtual std::string getName() { return "BB"; }
    
}; 

class SSPSolverPD : public SubsetSumSolverAbstract {

public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
    
    virtual std::string getName() { return "PD"; }
    
}; 

#endif
