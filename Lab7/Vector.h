
#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>


/*
 * Type traits for Vector
For given class Vector<T,N> define template class vector_traits<T> that for given type T defines:
• How arguments of type T are passed from or to methods get and set of a Vector<T>.
By default they should be passed by const reference, but for types int and double by value.
• The type of scalar in
 Vector operator * ( scalar, const Vector & x)
By default it should be T, but for std::string it should be int.
• Operation used in operator *. By default it should be multiplication by scalar, but strings
should be multiplied like this 3 * [„to”, „A”] → [„tototo”,”AAA”],
• Static method that returns the default value of type T :
zero for arithmetic types and "0" for strings.
 Modify class template Vector<T,N> but do not define its specializations.
 */

template <typename T>
class vector_traits {
 public:
  typedef const T& argument_type;
  typedef T scalar_type;
  typedef T result_type;
  static T default_value() {
    return T();
  }
};

template <>
class vector_traits<int> {
 public:
  typedef int argument_type;
  typedef int scalar_type;
  typedef int result_type;
  static int default_value() {
    return 0;
  }
};

template <>
class vector_traits<double> {
 public:
  typedef double argument_type;
  typedef double scalar_type;
  typedef double result_type;
  static double default_value() {
    return 0.0;
  }
};

template <typename T, size_t N >
class Vector {
  T data[N];
 public:
  typedef T value_type;
  typedef std::size_t  size_type;
  typedef T* pointer;
  typedef T& reference;
  typedef const T& const_reference;

  Vector() = default;
  Vector(const Vector & v) = default;
  Vector &operator=(const Vector & m) = default;

  Vector(const std::initializer_list<T> &list){
	std::copy(list.begin(), list.end(), data);
  }
  size_type size() const {
	return N;
  }

  const_reference get(size_type index) const {
	return data[index];
  }

  void set(size_type index, const_reference value) {
	data[index] = value;
  }

  friend Vector operator* (const T & x, const Vector & v ){
	Vector result;
	for(int i=0; i < v.size(); ++i){
	  result.set(i, x * v.get(i));
	}
	return result;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
	for(int i=0; i < v.size(); ++i){
	  out << v.get(i) << " ";
	}
	return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector & v) {
	Vector::value_type value;
	for(int i=0; i < v.size(); ++i){
	  in >> value;
	  if(in)
		v.set(i, value);
	}
	return in;
  }

};

#endif // LAB8_VECTOR_H