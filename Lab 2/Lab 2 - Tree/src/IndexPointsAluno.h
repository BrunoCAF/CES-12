#ifndef CES12_ALUNOINDEXPOINTS_H
#define CES12_ALUNOINDEXPOINTS_H

#include <vector>
#include <map>
#include <IndexPointsAbstract.h>

enum Color : bool {BLACK, RED};

/**
 * Em dezembro de 81
 * Botou os ingleses na roda
 * 3 a 0 no Liverpool
 * Ficou marcado na história
 * E no Rio não tem outro igual
 * Só o Flamengo é campeão mundial
 * E agora seu povo
 * Pede o mundo de novo
 * 
 * Dá-lhe, dá-lhe, dá-lhe, Mengo
 * Pra cima deles, Flamengo!
 * Dá-lhe, dá-lhe, dá-lhe, Mengo
 * Pra cima deles, Flamengo!        (2x)
 */

class RBNode {
public:
    RBNode(Color c) : color(c) {}
    RBNode(Color c, float k, long i) : color(c), key(k), idx(i) {}
    RBNode * p, * left, * right;
    float key;
    long idx;
    Color color;
};

class IndexPointsAluno : public IndexPointsAbstract {
    
public:
    
    IndexPointsAluno() : _size(0) {
        _nil = new RBNode(BLACK);
        _root->left = _root->right = _root->p = _root = _nil;
    }

    long size() ;
        
    void add (float key, long idx ) ;
    
    //look for a range of values
    void find(std::vector<long> &res, float first, float last ) ;
    
private: 
    // ALUNO DEVE IMPLEMENTAR ALGO COM O MESMO COMPORTAMENTO DE MULTIMAP
    //std::multimap<float, long> _map;

    long _size;
    RBNode *_nil;
    RBNode *_root;
    
    void LeftRotate(RBNode *x);
    void RightRotate(RBNode *y);
    void RBEnforceConsistence(RBNode *z);

    void InOrderEsperto(RBNode *n, std::vector<long> &res, float first, float last);
    
};//class

#endif
