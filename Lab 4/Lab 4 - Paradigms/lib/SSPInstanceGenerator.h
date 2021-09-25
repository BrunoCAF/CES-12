#ifndef SSP_INSTANCE_GENERATOR
#define SSP_INSTANCE_GENERATOR

#include <vector>
#include <string>
#include <ostream>
#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm> // std::sort
#include <random> // std::uniform_int_distribution 
// C+11 randon classes: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

void streamSSP(std::ostream &os,  const std::vector< long> &input, const  long &value) ;
void streamSSP(std::ostream &os,  const std::vector< long> &input, const  long &value, const std::vector<char> &x) ;

void SortAndCutXAboveCapacity(std::vector< long> &input, const  long &value);
double fatorial(int n) ;

class SSPInstanceGenerator {
public:
    
    SSPInstanceGenerator() : _alg("RAND") {
           _gen.seed(_rd());//Standard mersenne_twister_engine seeded with rd();
    }
    
    virtual void generate(long size,  std::vector< long> &input,  long &value); 
    
    virtual void generate(std::string newalg, long size,  std::vector< long> &input,  long &value) {
        setAlg(newalg);
        generate(size,input,value);
    }
    
    void setAlg(std::string newalg) { _alg = newalg; }
    std::string getAlg() { return _alg ;};
    
protected:
    
    void fillRAND(long size, std::vector< long> &input,  long &value);
    void fillP(int order, long size, std::vector< long> &input,  long &value);
    void fillEvenOdd(long size, std::vector< long> &input,  long &value) ;
    void fillTodd(long size, std::vector< long> &input,  long &value) ;
    void fillAvis(long size, std::vector< long> &input,  long &value) ;
    
    std::string _alg; /// algorithm
    
    //random stuff
    std::random_device _rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 _gen; //Standard mersenne_twister_engine seeded with rd()

    
}; //class


#endif
