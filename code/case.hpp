#ifndef CASE_HPP
#define CASE_HPP
#include <vector>
#include <functional>
template <class T,class U>
class Iter
{
  public:
  T x;
  Iter(T a):  x(a){};

  bool operator!=(Iter &i2) const { return x != i2.x; }
  void operator++() { x++; }
  void operator+=(int b) { x += b; }
  decltype(T()-T()) operator-(const Iter &i2) const { return x - i2.x; }

  U& operator*() const {

    return x->get();
  }
  U& operator->() {
    return operator*();
  }

  typedef std::random_access_iterator_tag iterator_category;
  typedef U value_type;
  typedef decltype(T()-T()) difference_type;
  typedef U* pointer;
  typedef U& reference;
};

class Case
{
public :
     public :
    std::string nom;
    Case(std::string n) :nom(n) {};
    using iterator = Iter<std::vector<std::reference_wrapper<Case>>::iterator,Case>;
    iterator begin() { return iterator(voisins.begin());}
    iterator end() { return iterator(voisins.end());}

        void addVoisin(Case& voisin){ voisins.push_back({voisin}) ;};

    private :
        std::vector<std::reference_wrapper<Case>> voisins;
};
#endif // CASE_HPP
