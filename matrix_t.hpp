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

#include "vector_t.hpp"

using namespace std;

template<class T> class matrix_t {
public:
  matrix_t(const int = 0, const int = 0);
  //NO HACE FALTA EL CONSTRUCTOR DE COPIA YA QUE DE ESO SE ENCARGA EL VECTOR_T
  ~matrix_t();
  
  void resize(const int, const int);
  
  // Getters
  int get_m(void) const;
  int get_n(void) const;
  
  // Getters-setters
  T& at(const int, const int);
  T& operator()(const int, const int);
  
  // Getters constantes
  const T& at(const int, const int) const;
  const T& operator()(const int, const int) const;


  // vector_t<T> get_row(const int i);
  // vector_t<T> SumOfPairs();
  
  // Operaciones y operadores
  void multiply(const matrix_t<T>&, const matrix_t<T>&);

  void write(ostream& = cout) const;
  void read(istream& = cin);

private:
  int m_, n_; // m_ filas y n_ columnas
  vector_t<T> v_;
  
  int pos(const int, const int) const;
};



template<class T> matrix_t<T>::matrix_t(const int m, const int n) { 
  m_ = m;
  n_ = n;
  v_.resize(m_ * n_);
}



// No hace falta liberar ningun espacio de memoria, ya que no utilizamos punteros
template<class T> matrix_t<T>::~matrix_t() {}



template<class T> void matrix_t<T>::resize(const int m, const int n) {
  assert(m > 0 && n > 0);
  m_ = m;
  n_ = n;
  v_.resize(m_ * n_);
}



template<class T> inline int matrix_t<T>::get_m() const {
  return m_;
}



template<class T> inline int matrix_t<T>::get_n() const {
  return n_;
}



template<class T> T& matrix_t<T>::at(const int i, const int j) {
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return v_[pos(i, j)]; //EL OPERADOR [] ESTA SOBRECARGADO EN LA CLASE VECTOR_T
}



// PREGUNTA DEL ENUNCIADO DE LA PRACRICA.
/*La sobrecarga del operador () en la clase matrix_t se utiliza para acceder a los 
elementos de una matriz utilizando una sintaxis de dos índices. Es decir, cuando se 
escribe m(i, j), se devuelve el elemento en la fila i y columna j de la matriz m. 
La sobrecarga del operador () se utiliza porque permite el acceso a los elementos de 
la matriz de manera muy natural y fácil de entender, lo que hace que la clase matrix_t 
sea más fácil de usar.
*/
template<class T> T& matrix_t<T>::operator()(const int i, const int j) {
  return at(i, j);
}



// Setter (sin const y con una referencia) permite hacer A.at(1,1) = 5;
template<class T> const T& matrix_t<T>::at(const int i, const int j) const {
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return v_[pos(i, j)];
}



template<class T> const T& matrix_t<T>::operator()(const int i, const int j) const {
  return at(i, j);
}


//Es un metodo que solicita los valores de cada elemento de la matriz
template<class T> void matrix_t<T>::write(ostream& os) const { 
  os << get_m() << "x" << get_n() << endl;
  for (int i = 1; i <= get_m(); ++i) {
    for (int j = 1; j <= get_n(); ++j)
      os << at(i, j) << "\t";
    os << endl;
  }
  os << endl;
}


//Es un metodo para imprimir por pantalla los valores de la matriz
template<class T> void matrix_t<T>::read(istream& is)
{
  is >> m_ >> n_;
  resize(m_, n_);
  for (int i = 1; i <= get_m(); ++i)
    for (int j = 1; j <= get_n(); ++j)
      is >> at(i, j);
}


template<class T> inline int matrix_t<T>::pos(const int i, const int j) const {
  assert(i > 0 && i <= get_m());
  assert(j > 0 && j <= get_n());
  return (i - 1) * get_n() + (j - 1);
}



// FASE III: producto matricial
template <class T> void matrix_t<T>::multiply(const matrix_t<T>& A, const matrix_t<T>& B) {
  T result;
  assert(A.get_n() == B.get_m());
  m_ = A.get_m();
  n_ = B.get_n();
  v_.resize(m_ * n_);
  for (int i = 1; i <= A.get_m(); i++) {
    for (int j = 1; j <= B.get_n(); j++) {
      for (int a = 1; a <= B.get_m(); a++) {
        at(i, j) = at(i, j) + A(i, a) * B(a, j);
      }
    }
  }
}



// template<class T>
// matrix_t<T> 
// operator+(const matrix_t<T>& a, const matrix_t<T>& b)
// {
//   assert(a.get_m() == b.get_m() && a.get_n() == b.get_n());
//   matrix_t<T> matriz_resultado;
//   matriz_resultado.resize(a.get_m(), b.get_n());

//   for(int i = 1; i <= a.get_m(); i++)
//   {
//     for(int j = 1; j <= b.get_n(); j++)
//     {
//       matriz_resultado.at(i, j) = a(i, j) + b(i , j); 
//     }
//   }
//   return matriz_resultado;
// }



// template<class T>
// matrix_t<T> 
// operator-(const matrix_t<T>& a, const matrix_t<T>& b)
// {
//   assert(a.get_m() == b.get_m() && a.get_n() == b.get_n());
//   matrix_t<T> matriz_resultado;
//   matriz_resultado.resize(a.get_m(), b.get_n());

//   for(int i = 1; i <= a.get_m(); i++)
//   {
//     for(int j = 1; j <= b.get_n(); j++)
//     {
//       matriz_resultado.at(i, j) = a(i, j) - b(i , j); 
//     }
//   }
//   return matriz_resultado;
// }



// template<class T>
// matrix_t<T> 
// operator*(const matrix_t<T>& a, const matrix_t<T>& b)
// {
//   matrix_t<T> matriz_resultado;
//   matriz_resultado.multiply(a,b);
//   return matriz_resultado;
// }


// template<class T>
// vector_t<T> matrix_t<T>::get_row(const int i)
// {
//   assert(i >= 1 && i <= get_m()); // Verificar que el índice de fila sea válido

//   vector_t<T> fila(get_n());

//   for (int j = 1; j <= get_n(); j++) {
//     fila[j - 1] = at(i, j);
//   }

//   return fila;
// }

// template<class T> vector_t<T> matrix_t<T>::SumOfPairs()
// {
//   vector_t<T> sum;
//   sum.resize(get_n());
//   for(int i = 1; i <= get_m(); i++)
//   {
//     if(i % 2 == 0)
//     {
//       sum = sum + get_row(i);
//     }
//   }
//   return sum;
// }