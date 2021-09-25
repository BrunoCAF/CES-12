
#include <IndexPointsAluno.h>

/// returns the number of elements in the index
long IndexPointsAluno::size() { return _size;}

/// adds new element to the index. 
void IndexPointsAluno::add (float key, long idx ) { 
  //_map.insert(std::make_pair(key,idx)) ; 

  _size++;
  RBNode *z = new RBNode(RED, key, idx);
  RBNode *y = _nil, *x = _root;
  while (x != _nil){
    y = x;
    x = (z->key < x->key) ? x->left : x->right;
  }
  z->p = y;
  if (y == _nil) _root = z;
  else ((z->key < y->key) ? y->left : y->right) = z;
  z->left = z->right = _nil;
  RBEnforceConsistence(z);
}

/// enforces the validity of the red-black properties after insertion. 
void IndexPointsAluno::RBEnforceConsistence(RBNode *z){
  RBNode *y;
  while (z->p->color == RED){
    if (z->p == z->p->p->left){
      y = z->p->p->right;
      if (y->color == RED){
        y->color = z->p->color = BLACK; z->p->p->color = RED;
        z = z->p->p;
      } else {
        if (z == z->p->right) (z = z->p, LeftRotate(z));
        z->p->color = BLACK; z->p->p->color = RED;
        RightRotate(z->p->p);
      }
    }else{
      y = z->p->p->left;
      if (y->color == RED){
        y->color = z->p->color = BLACK; z->p->p->color = RED;
        z = z->p->p;
      } else {
        if (z == z->p->left) (z = z->p, RightRotate(z));
        z->p->color = BLACK; z->p->p->color = RED;
        LeftRotate(z->p->p);
      }
    }
  }
  _root->color = BLACK;
}

/// left rotates around node x. 
void IndexPointsAluno::LeftRotate(RBNode *x){
  RBNode *y = x->right; //define y
  
  // Primeiro elo: transfere a subárvore
  x->right = y->left; 
  if (y->left != _nil) y->left->p = x;
  
  // Segundo elo: transfere a paternidade
  y->p = x->p;
  if (x->p == _nil) _root = y;
  else ((x == x->p->left) ? x->p->left : x->p->right) = y;
  
  // Terceiro elo: inverte a relação pai-filho
  y->left = x; x->p = y;
}

/// right rotates around node y.
void IndexPointsAluno::RightRotate(RBNode *y){
  RBNode *x = y->left; // define x

  // Primeiro elo: transfere a subárvore
  y->left = x->right;
  if (x->right != _nil) x->right->p = y;

  // Segundo elo: transfere a paternidade
  x->p = y->p;
  if (y->p == _nil) _root = x;
  else ((y == y->p->right) ? y->p->right : y->p->left) = x;

  // Terceiro elo: inverte a relação pai-filho
  x->right = y; y->p = x;
}

void IndexPointsAluno::find(std::vector<long> &res, float first, float last) {
  
  InOrderEsperto(_root, res, first, last);

  // it is float, so it is not possible to compare with ==
  // the only thing that makes sense is too look for a range from
  // a min value to a max value. 
  // stl::multimap implements this using iterators 
  // you do not need to use iterators, but you need to fill the answer in O(k + logn)
  // where k is the number of elements in the range from first to last
  // in other words: NAO VALE FAZER INORDER COMPLETO E SELECIONAR O RANGE
  // PRECISA UM INORDER ESPERTO QUE ACHA O FIRST em O(log n) E CONTINUA ATE O LAST
  //auto itlow = _map.lower_bound (first);  // itlow points to first
  //auto itup = _map.upper_bound (last);   // itup points to next after last (not to last)

  // print range [itlow,itup), which is the same as [itlow, last] or [first, last]
  //for (auto it=itlow; it!=itup; ++it)
    //std::cout << (*it).first << " => " << (*it).second << '\n';
    //res.push_back((*it).second);
  
}//find

/// o famigerado InOrder esperto. 
void IndexPointsAluno::InOrderEsperto(RBNode *n, std::vector<long> &res, float first, float last){
  if (n == _nil) return;

  if(n->key < first) return InOrderEsperto(n->right, res, first, last);
  if(n->key > last ) return InOrderEsperto(n->left , res, first, last);

  InOrderEsperto(n->left, res, first, last);
  res.push_back(n->idx);
  InOrderEsperto(n->right, res, first, last);
}

