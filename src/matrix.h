

#ifndef Matrix_h
#define Matrix_h

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace mtx {
// ADDITIONS
// we can put parameters rowN and colN as additional template types
//"template <type NumType, rowN, colN>"
// to do the job at the compile time with fixed size matix, but we lose runtime
// flexibility. So, class design depences on an exersice.
template <typename NumType> class Matrix {
  // we want to work with arithmetic types
  static_assert(std::is_arithmetic<NumType>::value, "");

public:
  // Special member functions
  // Constructors
  Matrix() : rowN_{0}, colN_{0} {};
  Matrix(const size_t _rowN, const size_t _colN);
  Matrix(const std::vector<NumType> &vec)
      : rowN_{1}, colN_{vec.size()}, m{vec} {}; // for vectors
  // Copying
  Matrix(const Matrix &) = default;
  Matrix &operator=(const Matrix &) = delete;
  // Moving
  Matrix(Matrix &&) = default;
  Matrix &operator=(Matrix &&) = default;
  // Mathematical operations with matrices
  Matrix operator+(const Matrix &rhs);
  void operator+=(const Matrix &rhs);
  // SCALAR multiplication
  Matrix &operator*=(const NumType &rhs);
  // lhs miltiplication is added too
  Matrix operator*(const NumType &rhs);
  // MATRIX multiplication
  Matrix operator*(const Matrix &rhs);
  Matrix operator&(const Matrix &rhs); // optimized multiplication
  Matrix operator^(const Matrix &rhs); // Reordered multiplication
  Matrix getTranspose() const;
  // Setter and Getter
  // TODO create one from the following 2 functions
  NumType &operator()(size_t row, size_t col);      // Set
  NumType operator()(size_t row, size_t col) const; // Get
private:
  // Main data structures
  size_t rowN_;
  size_t colN_;
  size_t m_size;
  using m_type = std::vector<NumType>;
  m_type m;
  // Check exeption functions
  void check_range(const size_t rowIndex, const size_t colIndex);
  void is_dim_equal_with(const Matrix &rhs) const;
  void is_multi_possible(const Matrix &rhs) const;
}; // class Matrix{

// Exception handling
class MatrixException : public std::exception {
private:
  std::string m_error;

public:
  MatrixException(std::string error) : m_error(error){};
  const char *what() const noexcept { return m_error.c_str(); }
}; // class MatrixException

////////////////////
// Definitions
////////////////////

// Constructors
template <typename NumType>
inline Matrix<NumType>::Matrix(const size_t _rowN, const size_t _colN)
    : rowN_{_rowN}, colN_{_colN}, m_size{_rowN * _colN} {
  try {
    m.resize(m_size);
    // vector throws a length_error if resized above max_size
  } catch (const std::length_error &le) {
    throw MatrixException("out of memory");
  }
  if (m_size == 0)
    throw MatrixException("degenerate matrix");
}
// Setter
template <typename NumType>
inline NumType &Matrix<NumType>::operator()(size_t row, size_t col) {
  try {
    return m.at(row * colN_ + col);
  } catch (const std::out_of_range &oor) {
    throw MatrixException("matrix index out of range");
  }
}
// Getter
template <typename NumType>
inline NumType Matrix<NumType>::operator()(size_t row, size_t col) const {
  try {
    return m.at(row * colN_ + col);
  } catch (const std::out_of_range &oor) {
    throw MatrixException("matrix index out of range");
  };
}
// Setter
template <typename NumType>
inline void Matrix<NumType>::is_dim_equal_with(const Matrix &rhs) const {
  if ((rowN_ != rhs.rowN_) || (colN_ != rhs.colN_))
    throw MatrixException("different size matrices");
}
// Exception functions
template <typename NumType>
inline void Matrix<NumType>::is_multi_possible(const Matrix &rhs) const {
  if (colN_ != rhs.rowN_)
    throw MatrixException("matrix miltiplication is mot pssible");
}
// Matix addition
template <typename NumType>
inline void Matrix<NumType>::operator+=(const Matrix &rhs) {
  // TODO parallelisation with respect to size of a vector C++17
  is_dim_equal_with(rhs);
  std::transform(m.begin(), m.end(), rhs.m.begin(), m.begin(),
                 std::plus<NumType>());
}

template <typename NumType>
inline Matrix<NumType> Matrix<NumType>::operator+(const Matrix &rhs) {
  is_dim_equal_with(rhs);
  Matrix<NumType> m_local = (*this);
  m_local += rhs;
  return m_local; // named RWO is expacted
}

// SCALAR multiplication
template <typename NumType>
inline Matrix<NumType> &Matrix<NumType>::operator*=(const NumType &rhs) {
  // TODO parallelisation with respect to size of a vector C++17
  transform(m.begin(), m.end(), m.begin(), [&rhs](auto &c) { return c * rhs; });
  return *this;
}

template <typename NumType>
inline Matrix<NumType> Matrix<NumType>::operator*(const NumType &rhs) {
  Matrix<NumType> m_local = (*this);
  m_local *= rhs;
  return m_local; // named RWO is expacted
}

template <typename NumType>
inline Matrix<NumType> operator*(const NumType &lhs,
                                 const Matrix<NumType> &rhs) {
  Matrix<NumType> m_local = rhs;
  m_local *= lhs;
  return m_local; // named RWO is expacted
}

template <typename NumType>
inline Matrix<NumType> Matrix<NumType>::getTranspose() const {
  Matrix<NumType> m_local(colN_, rowN_);
  for (unsigned int i = 0; i < colN_; i++)
    for (unsigned int j = 0; j < rowN_; j++)
      m_local.m[i * rowN_ + j] = m[j * colN_ + i];
  return m_local;
};

// Naive multiplication
template <typename NumType>
inline Matrix<NumType> Matrix<NumType>::operator*(const Matrix &rhs) {
  is_multi_possible(rhs);
  Matrix<NumType> result_m(rowN_, rhs.colN_);
  for (size_t i = 0; i < rowN_; i++)
    for (size_t j = 0; j < rhs.colN_; j++) {
      size_t index = i * rhs.colN_ + j;
      for (unsigned int k = 0; k < colN_; k++)
        result_m.m[index] += m[i * colN_ + k] * rhs.m[k * rhs.colN_ + j];
    };
  return result_m;
};
// Multiplication with transposition
template <typename NumType>
inline Matrix<NumType> Matrix<NumType>::operator&(const Matrix &rhs) {
  is_multi_possible(rhs);
  Matrix<NumType> result_m(rowN_, rhs.colN_);
  Matrix<NumType> tr(rhs.getTranspose());
  
  for (size_t i = 0; i < rowN_; i++)
    for (size_t j = 0; j < tr.rowN_; j++) {
      size_t index = i * tr.rowN_ + j;
      for (unsigned int k = 0; k < colN_; k++)
        result_m.m[index] += m[i * colN_ + k] * tr.m[j * tr.colN_ + k];
    };
  return result_m;
};

// Reordered multiplication
template <typename NumType>
inline Matrix<NumType> Matrix<NumType>::operator^(const Matrix &rhs) {
  is_multi_possible(rhs);
  Matrix<NumType> result_m(rowN_, rhs.colN_);
  for (size_t i = 0; i < rowN_; i++)
    for (size_t k = 0; k < colN_; k++)
      for (size_t j = 0; j < rhs.colN_; j++) {
        size_t index = i * rhs.colN_ + j;
        result_m.m[index] += m[i * colN_ + k] * rhs.m[k * rhs.colN_ + j];
      };
  return result_m;
};
}; // namespace mtx
#endif
