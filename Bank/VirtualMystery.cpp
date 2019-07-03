/* Mystery.cpp, by M. Hazen after M. Winstanley
   CSE 374 class inheritance.
*/

#include <iostream>
    
using namespace std;
    
class A {
public:      
  A() { cout << "a()" << endl; }
  virtual ~A() { cout << "~a" << endl; }
  virtual void m1() { cout << "a1" << endl; }
  virtual void m2() { cout << "a2" << endl; }
};

class B : public A {
public:
  B() { cout << "b()" << endl; }
  virtual ~B() { cout << "~b" << endl; }
  virtual void m1() override { cout << "b1" << endl; }
  virtual void m2() override { cout << "b2" << endl; }
  void m3() { cout << "b3" << endl; }
};

int main() {
  //B* x = new B();
  A* x = new B();
  B* y = new B();
  x->m1();
  x->m2();
  y->m3();
  delete x;
  delete y;
}
