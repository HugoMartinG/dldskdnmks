// AUTOR: Hugo Martín Gámez
// FECHA: 01/03/2023
// EMAIL: alu0101562476@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 2
// COMENTARIOS: se indican entre [] las pautas de estilo aplicadas de
//              "C++ Programming Style Guidelines"
//              https://geosoft.no/development/cppstyle.html


#pragma once


#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

template<class T> class vector_t {
public:
  vector_t(const int = 0);
  ~vector_t();
  
  void resize(const int);
  
  // getters
  T get_val(const int) const;
  int get_size(void) const;
  
  // setters
  void set_val(const int, const T);

  void MetodoPropuesto(const vector_t<T>& v);

  // getters-setters
  T& at(const int);
  T& operator[](const int);
  
  // getters constantes
  const T& at(const int) const;
  const T& operator[](const int) const;

  void write(ostream& = cout) const;
  void read(istream& = cin);

private:
  T *v_;
  int sz_;
  
  void build(void);
  void destroy(void);
};


// Constructor de la clase
template<class T> vector_t<T>::vector_t(const int n) { 
  sz_ = n;
  build();
}


// Destructor
template<class T> vector_t<T>::~vector_t() {
  destroy();
}


// Metodo build para el constructor de la clase
template<class T> void vector_t<T>::build() {
  v_ = NULL; // Buena practica ponerlo a NULL antes
  if (sz_ != 0) { // Si sz_ no es cero, entonces se asigna memoria dinámica para el vector de elementos utilizando el operador new
    v_ = new T[sz_]; 
    assert(v_ != NULL); // Para comprobar si la asignación fue exitosa
  }
}


// Metodo destroy para el destructor de la clase
template<class T> void vector_t<T>::destroy() {
  if (v_ != NULL) {
    delete[] v_; // Libera la memoria dinámica asignada al vector de elementos utilizando el operador delete[]
    v_ = NULL;
  }
  sz_ = 0;
}


// Metodo para darle un nuevo tamaño al vector
template<class T> void vector_t<T>::resize(const int n) {
  destroy();
  sz_ = n;
  build();
}


// Getter del valor de cada elemento del vector
template<class T> inline T vector_t<T>::get_val(const int i) const {
  assert(i >= 0 && i < get_size());
  return v_[i];
}


// Getter de sz_
template<class T> inline int vector_t<T>::get_size() const {
  return sz_;
}


// Setter 
template<class T> void vector_t<T>::set_val(const int i, const T d) {
  assert(i >= 0 && i < get_size());
  v_[i] = d;
}


// Setter de cada elemento del vector
template<class T> T& vector_t<T>::at(const int i) {
  assert(i >= 0 && i < get_size());
  return v_[i];
}


// Sobrecarga del operador de asignacion [] 
template<class T> T& vector_t<T>::operator[](const int i) {
  return at(i);
}


// const
template<class T> const T& vector_t<T>::at(const int i) const {
  assert(i >= 0 && i < get_size());
  return v_[i];
}


/*La sobrecarga del operador [] en la clase vector_t se utiliza para acceder a los elementos del 
vector a través de un índice entero. Es decir, cuando se escribe v[i], se devuelve el elemento en 
la posición i-ésima del vector v. La sobrecarga del operador [] se utiliza porque permite el acceso 
a los elementos de una manera muy intuitiva y natural, lo que hace que la clase vector_t sea más fácil 
de usar.
*/  
template<class T> const T& vector_t<T>::operator[](const int i) const {
  return at(i);
}


// Metodo write para pedir los elementos del vector
template<class T> void vector_t<T>::write(ostream& os) const { 
  os << get_size() << ":\t";
  for (int i = 0; i < get_size(); i++)
    os << at(i) << "\t";
  os << endl;
}


// Metodo para imprimir por pantalla cada elemento del vector 
template<class T> void vector_t<T>::read(istream& is) {
  is >> sz_;
  resize(sz_);
  for (int i = 0; i < sz_; ++i)
    is >> at(i);
}


// FASE II: 
// producto escalar
template<class T> T scal_prod(const vector_t<T>& v, const vector_t<T>& w) {
  assert(v.get_size() == w.get_size());
  T result = T();
  for (int i = 0; v.get_size() > i; i++)
  {
    result = result + v[i] * w[i]; 
  }
  return result;
}


//Producto escalar double
double scal_prod(const vector_t<rational_t>& v, const vector_t<rational_t>& w) {
  assert(v.get_size() == w.get_size());
  double result = 0.0;
  for (int i = 0; v.get_size() > i; i++)
  {
    result = result + v[i].value() * w[i].value(); 
  }
  return result;
}

//Metodo propuesto
template<class T> void vector_t<T>::MetodoPropuesto(const vector_t<T>& v){
  vector_t<T> vector_resultado;
  vector_resultado.resize(v.get_size()-1);
  for(int i = 0; i < v.get_size()-1; i++){
    vector_resultado[i] = v[i] + v[i+1];
  }
  vector_resultado.write();
}

// template<class T>
// vector_t<T> operator+(const vector_t<T>& a, const vector_t<T>& b)
// {
//   assert(a.get_size() == b.get_size());
//   vector_t<T> vector_resultado(a.get_size());
//   for(int i = 0; i < a.get_size(); i++)
//   {
//     vector_resultado.at(i) = a.at(i) + b.at(i);
//   }
//   return vector_resultado;
// }

// template<class T>
// vector_t<T> operator-(const vector_t<T>& a, const vector_t<T>& b)
// {
//   assert(a.get_size() == b.get_size());
//   vector_t<T> vector_resultado(a.get_size());
//   for(int i = 0; i < a.get_size(); i++)
//   {
//     vector_resultado.at(i) = a.at(i) - b.at(i);
//   }
//   return vector_resultado;
// }
