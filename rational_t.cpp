// AUTOR: Hugo Martín Gámez
// FECHA: 01/03/2023
// EMAIL: alu0101562476@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 2
// COMENTARIOS: se indican entre [] las pautas de estilo aplicadas de
//              "C++ Programming Style Guidelines"
//              https://geosoft.no/development/cppstyle.html


#include "rational_t.hpp"

rational_t::rational_t(const int n, const int d)
{
  assert(d != 0);
  num_ = n, den_ = d;
}


inline
int
rational_t::get_num() const
{
  return num_;
}



inline
int
rational_t::get_den() const
{
  return den_;
}


  
void
rational_t::set_num(const int n)
{
  num_ = n;
}


  
void
rational_t::set_den(const int d)
{
  assert(d != 0);
  den_ = d;
}



inline
double
rational_t::value() const
{ 
  return double(get_num()) / get_den();
}



rational_t 
rational_t::opposite() const
{ 
  return rational_t((-1)*get_num(), get_den());
}



rational_t
rational_t::reciprocal() const
{ 
  return rational_t(get_den(), get_num());
}



// comparaciones
bool
rational_t::is_equal(const rational_t& r, const double precision) const
{ 
  return fabs(value() - r.value()) < precision;
}



bool
rational_t::is_greater(const rational_t& r, const double precision) const
{
  return (value() - r.value()) > precision;
}



bool
rational_t::is_less(const rational_t& r, const double precision) const
{
  return r.is_greater(*this, precision);
}


// Operaciones
rational_t
rational_t::add(const rational_t& r) const
{
  return rational_t(get_num() * r.get_den() + get_den() * r.get_num(), get_den() * r.get_den());
}



rational_t
rational_t::substract(const rational_t& r) const
{
  return add(r.opposite());
}



rational_t
rational_t::multiply(const rational_t& r) const
{
  return rational_t(get_num() * r.get_num(), get_den() * r.get_den());
}



rational_t
rational_t::divide(const rational_t& r) const
{
  return multiply(r.reciprocal());
}


// FASE I: operadores
rational_t operator+(const rational_t& a, const rational_t& b) {
  int nuevo_numerador = (a.get_num() * b.get_den()) + (b.get_num() * a.get_den());
  int nuevo_denominador = a.get_den() * b.get_den();
  return rational_t(nuevo_numerador, nuevo_denominador);
}



rational_t operator-(const rational_t& a, const rational_t& b) {
  int nuevo_numerador = (a.get_num() * b.get_den()) - (b.get_num() * a.get_den());
  int nuevo_denominador = a.get_den() * b.get_den();
  return rational_t(nuevo_numerador, nuevo_denominador);
}



rational_t operator*(const rational_t& a, const rational_t& b) {
  int nuevo_numerador = a.get_num() * b.get_num();
  int nuevo_denominador = a.get_den() * b.get_den();
  return rational_t(nuevo_numerador, nuevo_denominador);
}



rational_t operator/(const rational_t& a, const rational_t& b) {
  int nuevo_numerador = a.get_num() * b.get_den();
  int nuevo_denominador = a.get_den() * b.get_num();
  return rational_t(nuevo_numerador, nuevo_denominador);
}



// E/S
void rational_t::write(ostream& os) const {
  os << get_num() << "/" << get_den() << "=" << value() << endl;
}



void rational_t::read(istream& is) {
  is >> num_ >> den_;
  assert(den_ != 0);
}

/*La sobrecarga de los operadores << y >> en la clase rational_t se utilizan para la entrada y 
salida de objetos de tipo rational_t en flujos de entrada y salida. Es decir, la sobrecarga del 
operador << permite que un objeto de tipo rational_t se escriba en un flujo de salida (como la pantalla o un archivo)
, mientras que la sobrecarga del operador >> permite que un objeto de tipo rational_t se lea de un 
flujo de entrada (como un archivo o el teclado). 
*/

ostream& operator<<(ostream& os, const rational_t& r) {
  r.write(os);
  return os;
}


istream& operator>>(istream& is, rational_t& r) {
  r.read(is);
  return is;
}