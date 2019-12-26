#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
//#include <stdexcept> 

namespace mtx{
//ADDITIONS 
//we can put parameters rowN and colN as additional template types 
//"template <type NumType, rowN, colN>"
//to do the job at the compile time with fixed size matix, but we lose runtime flexibility.
//So, class design depences on an exersice.
template<typename NumType> 
class Matrix
{
	static_assert(std::is_arithmetic<NumType>::value,""); // we want to work with arithmetic types
	public:
//Special member functions	
	//constructor
	Matrix(const size_t _rowN, const size_t _colN);
	//Matrix() = delete;
	//copying 
	Matrix(const Matrix&) = default;
	Matrix& operator=(const Matrix&) = delete;
	//moving
	Matrix(Matrix&&) = default;
	Matrix& operator=(Matrix &&) = default;
        //destuctor	
	//virtual ~Matrix(){};
//Mathematical operations
	Matrix operator+(const Matrix& rhs);
	void operator+=(const Matrix& rhs);
	//Matrix operator-(const Matrix& rhs);
	//Matrix& operator-=(const Matrix& rhs);
	Matrix operator*(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix& operator*(const NumType& rhs);
	Matrix& operator/(const NumType& rhs);
//Set and Get
//TODO create one from the following 2 functions
	NumType& operator() (size_t row, size_t col); // Set        
        NumType  operator() (size_t row, size_t col) const; // Get 

	private:		
//Main data structures
	size_t rowN_;
	size_t colN_;
	size_t m_size;	
	using m_type = std::vector<NumType>;
	m_type m; 
//Check exeption functions
	void check_range(const size_t rowIndex,
		         const size_t colIndex);
	void is_dim_equal_with(const Matrix& rhs) const;
};// class Matrix{

class MatrixException: public std::exception
{
private:
	std::string m_error;
public:
	MatrixException(std::string error) : m_error(error){};
	const char* what() const noexcept { return m_error.c_str(); }
};// class MatrixException

template<typename NumType>
inline Matrix<NumType>::Matrix(const size_t _rowN,const size_t _colN):
      	rowN_{_rowN}, colN_{_colN}, m_size{_rowN*_colN}{
	try { 		
		m.resize(m_size);	
// vector throws a length_error if resized above max_size
	} catch (const std::length_error& le) {
  		throw MatrixException("out of memory");
	}
	if (m_size == 0) throw MatrixException("degenerate matrix");
}

template<typename NumType>
inline NumType& Matrix<NumType>::operator()(size_t row, size_t col){
	try {
		return m.at(row*rowN_ + col);
        } catch(const std::out_of_range& oor){
		throw MatrixException("matrix index out of range");
	}
}

template<typename NumType>
inline NumType Matrix<NumType>::operator()(size_t row, size_t col) const {
	try {
		return m.at(row*rowN_ + col);
        } catch(const std::out_of_range& oor){
		throw MatrixException("matrix index out of range");
	};
}

template<typename NumType>
inline void Matrix<NumType>::is_dim_equal_with(const Matrix& rhs) const{
	if ((rowN_!=rhs.rowN_)||(colN_!=rhs.colN_))
		throw MatrixException("different size matrices");
}

template<typename NumType>
inline void Matrix<NumType>::operator+=(const Matrix& rhs){
	//TODO parallelisation with respect to size of a vector C++17
	is_dim_equal_with(rhs);
	std::transform (m.begin(), m.end(), 
			rhs.m.begin(), m.begin(), 
			std::plus<NumType>());
}

template<typename NumType>
inline Matrix<NumType> Matrix<NumType>::operator+(const Matrix& rhs){ 
	is_dim_equal_with(rhs);
	Matrix<NumType> m_local = (*this);
	m_local+=rhs;
	return m_local; //named RWO is expacted
}
//template<typename NumType>
//inline Matrix::Matrix(unsigned rows, unsigned cols)
//  : rows_ (rows)
//  , cols_ (cols)
////, data_ ← initialized below after the if...throw statement
//{
//  if (rows == 0 || cols == 0)
//    throw BadIndex("Matrix constructor has 0 size");
//  data_ = new double[rows * cols];
//}
//template<typename NumType>
//class Vector: public Matrix<NumType>{
//
//};

// custom allocator example
//#include <cstddef>
//#include <iostream>
//#include <memory>
//#include <vector>
//
//template <class T>
//struct custom_allocator {
//  typedef T value_type;
//  custom_allocator() noexcept {}
//  template <class U> custom_allocator (const custom_allocator<U>&) noexcept {}
//  T* allocate (std::size_t n) { return static_cast<T*>(::operator new(n*sizeof(T))); }
//  void deallocate (T* p, std::size_t n) { ::delete(p); }
//};
//
//template <class T, class U>
//constexpr bool operator== (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
//{return true;}
//
//template <class T, class U>
//constexpr bool operator!= (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
//{return false;}



};//namespace mtx{ 
#endif
