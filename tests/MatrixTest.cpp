
#include <gmock/gmock.h>
// src file for matrix
#include <matrix.h>

using namespace mtx;

TEST(TestMatrix, CheckOutOfMemoryExeption) {
  bool is_thrown = false;

  try {
    std::vector<float> v_f;
    Matrix<float> mt(v_f.max_size(), 2);
  } catch (const MatrixException &me) {
    is_thrown = true;
    ASSERT_STREQ("out of memory", me.what());
  }

  ASSERT_THAT(is_thrown, testing::Eq(true));
};

TEST(TestMatrix, CheckDegenerateMatrixExeption) {
  bool is_thrown = false;

  try {
    Matrix<double> mt(12, 0);
  } catch (const MatrixException &me) {
    is_thrown = true;
    ASSERT_STREQ("degenerate matrix", me.what());
  }

  ASSERT_THAT(is_thrown, testing::Eq(true));
};

class TestMatrixClass : public testing::Test {
public:
  Matrix<int> GetMatrix_0() {
    Matrix<int> m(2, 2);
    m(0, 0) = 0;
    m(0, 1) = 0;
    m(1, 0) = 0;
    m(1, 1) = 0;
    return m;
  };
  Matrix<int> GetMatrix_1() {
    Matrix<int> m(2, 2);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    return m;
  };
  Matrix<int> GetMatrix_2() {
    Matrix<int> m(2, 2);
    m(0, 0) = 2;
    m(0, 1) = 5;
    m(1, 0) = 10;
    m(1, 1) = 20;
    return m;
  };
  Matrix<int> GetMatix2times3() {
    Matrix<int> m(2, 3);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(0, 2) = 3;
    m(1, 0) = 4;
    m(1, 1) = 5;
    m(1, 2) = 6;
    return m;
  };

  Matrix<int> GetMatix3times2() {
    Matrix<int> m(3, 2);
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    m(2, 0) = 5;
    m(2, 1) = 6;
    return m;
  };
};

TEST_F(TestMatrixClass, CreateAndInit2DMatrix) {
  Matrix<int> m = GetMatrix_1();
  ASSERT_THAT(m(0, 0), testing::Eq(1));
  ASSERT_THAT(m(0, 1), testing::Eq(2));
  ASSERT_THAT(m(1, 0), testing::Eq(3));
  ASSERT_THAT(m(1, 1), testing::Eq(4));
};

TEST_F(TestMatrixClass, AddEqOperator) {
  Matrix<int> m = GetMatrix_1();
  Matrix<int> m2 = GetMatrix_1();
  m += m2;
  ASSERT_THAT(m(0, 0), testing::Eq(2));
  ASSERT_THAT(m(0, 1), testing::Eq(4));
  ASSERT_THAT(m(1, 0), testing::Eq(6));
  ASSERT_THAT(m(1, 1), testing::Eq(8));
};

TEST_F(TestMatrixClass, InitAddOperator) {
  Matrix<int> m1 = GetMatrix_1();
  Matrix<int> m2 = GetMatrix_2();
  Matrix<int> m = (m1 + m2);
  ASSERT_THAT(m(0, 0), testing::Eq(3));
  ASSERT_THAT(m(0, 1), testing::Eq(7));
  ASSERT_THAT(m(1, 0), testing::Eq(13));
  ASSERT_THAT(m(1, 1), testing::Eq(24));
};

TEST_F(TestMatrixClass, MathAddOperator) {
  Matrix<int> m1 = GetMatrix_1();
  Matrix<int> m2 = GetMatrix_2();
  Matrix<int> m = (m1 + m2);
  m = m + m1;
  ASSERT_THAT(m(0, 0), testing::Eq(4));
  ASSERT_THAT(m(0, 1), testing::Eq(9));
  ASSERT_THAT(m(1, 0), testing::Eq(16));
  ASSERT_THAT(m(1, 1), testing::Eq(28));
};

TEST_F(TestMatrixClass, InitAddTwoDifferentDimMatricesExeption) {
  bool is_thrown = false;
  Matrix<int> m0 = GetMatrix_0();
  Matrix<int> m1 = GetMatix2times3();

  try {
    m0 += m1;
  } catch (const MatrixException &me) {
    is_thrown = true;
    ASSERT_STREQ("different size matrices", me.what());
  }
};

TEST_F(TestMatrixClass, InitNumMultiplication) {
  Matrix<int> m = GetMatrix_1();
  const int multiplier = 3;

  m *= multiplier;

  ASSERT_THAT(m(0, 0), testing::Eq(3));
  ASSERT_THAT(m(0, 1), testing::Eq(6));
  ASSERT_THAT(m(1, 0), testing::Eq(9));
  ASSERT_THAT(m(1, 1), testing::Eq(12));
};

TEST_F(TestMatrixClass, LhsMultiplication) {
  Matrix<int> m1 = GetMatrix_1();
  const int multiplier = 4;

  Matrix<int> m = m1 * multiplier;

  ASSERT_THAT(m(0, 0), testing::Eq(4));
  ASSERT_THAT(m(0, 1), testing::Eq(8));
  ASSERT_THAT(m(1, 0), testing::Eq(12));
  ASSERT_THAT(m(1, 1), testing::Eq(16));
};

TEST_F(TestMatrixClass, RhsMultiplication) {
  Matrix<int> m1 = GetMatrix_1();
  const int multiplier = 5;

  Matrix<int> m = multiplier * m1;

  ASSERT_THAT(m(0, 0), testing::Eq(5));
  ASSERT_THAT(m(0, 1), testing::Eq(10));
  ASSERT_THAT(m(1, 0), testing::Eq(15));
  ASSERT_THAT(m(1, 1), testing::Eq(20));
};

TEST_F(TestMatrixClass, LhsMultiplicationAndCopyAssignment) {
  Matrix<int> m1 = GetMatrix_1();
  const int multiplier = 4;
  Matrix<int> m;

  m = m1 * multiplier;

  ASSERT_THAT(m(0, 0), testing::Eq(4));
  ASSERT_THAT(m(0, 1), testing::Eq(8));
  ASSERT_THAT(m(1, 0), testing::Eq(12));
  ASSERT_THAT(m(1, 1), testing::Eq(16));
};

TEST_F(TestMatrixClass, Transpose) {
  Matrix<int> m = GetMatix2times3();

  m = m.getTranspose();

  // m(0,0) = 1; m(0,1) = 2; m(0,2) = 3;
  // m(1,0) = 4; m(1,1) = 5; m(1,2) = 6;
  // first row
  ASSERT_THAT(m(0, 0), testing::Eq(1));
  ASSERT_THAT(m(0, 1), testing::Eq(4));
  // second row
  ASSERT_THAT(m(1, 0), testing::Eq(2));
  ASSERT_THAT(m(1, 1), testing::Eq(5));
  // last row
  ASSERT_THAT(m(2, 0), testing::Eq(3));
  ASSERT_THAT(m(2, 1), testing::Eq(6));
}

TEST_F(TestMatrixClass, MatrixSquare) {
  Matrix<int> m1 = GetMatrix_1();

  Matrix<int> m(m1 * m1);

  ASSERT_THAT(m(0, 0), testing::Eq(7));
  ASSERT_THAT(m(0, 1), testing::Eq(10));
  ASSERT_THAT(m(1, 0), testing::Eq(15));
  ASSERT_THAT(m(1, 1), testing::Eq(22));
};

TEST_F(TestMatrixClass, Multiply3By2With2By3Matrices) {
  Matrix<int> m_n = GetMatix3times2();
  Matrix<int> m_t(m_n.getTranspose());

  Matrix<int> m(m_n * m_t);

  //		m(0,0) = 1; m(0,1) = 2;
  //	       	m(1,0) = 3; m(1,1) = 4;
  //		m(2,0) = 5; m(2,1) = 6;
  // first row
  ASSERT_THAT(m(0, 0), testing::Eq(5));
  ASSERT_THAT(m(0, 1), testing::Eq(11));
  ASSERT_THAT(m(0, 2), testing::Eq(17));
  // second row
  ASSERT_THAT(m(1, 0), testing::Eq(11));
  ASSERT_THAT(m(1, 1), testing::Eq(25));
  ASSERT_THAT(m(1, 2), testing::Eq(39));
  // third row
  ASSERT_THAT(m(2, 0), testing::Eq(17));
  ASSERT_THAT(m(2, 1), testing::Eq(39));
  ASSERT_THAT(m(2, 2), testing::Eq(61));
};
TEST_F(TestMatrixClass, MultiplyNew3By2With2By3Matrices) {
  Matrix<int> m_n = GetMatix3times2();
  Matrix<int> m_t(m_n.getTranspose());

  Matrix<int> m(m_n & m_t);
  //		m(0,0) = 1; m(0,1) = 2;
  //	       	m(1,0) = 3; m(1,1) = 4;
  //		m(2,0) = 5; m(2,1) = 6;

  // first row
  ASSERT_THAT(m(0, 0), testing::Eq(5));
  ASSERT_THAT(m(0, 1), testing::Eq(11));
  ASSERT_THAT(m(0, 2), testing::Eq(17));
  // second row
  ASSERT_THAT(m(1, 0), testing::Eq(11));
  ASSERT_THAT(m(1, 1), testing::Eq(25));
  ASSERT_THAT(m(1, 2), testing::Eq(39));
  // third row
  ASSERT_THAT(m(2, 0), testing::Eq(17));
  ASSERT_THAT(m(2, 1), testing::Eq(39));
  ASSERT_THAT(m(2, 2), testing::Eq(61));
};

TEST_F(TestMatrixClass, MultiplyReoderedNew3By2With2By3Matrices) {
  Matrix<int> m_n = GetMatix3times2();
  Matrix<int> m_t(m_n.getTranspose());

  Matrix<int> m(m_n ^ m_t);
  //		m(0,0) = 1; m(0,1) = 2;
  //	       	m(1,0) = 3; m(1,1) = 4;
  //		m(2,0) = 5; m(2,1) = 6;

  // first row
  ASSERT_THAT(m(0, 0), testing::Eq(5));
  ASSERT_THAT(m(0, 1), testing::Eq(11));
  ASSERT_THAT(m(0, 2), testing::Eq(17));
  // second row
  ASSERT_THAT(m(1, 0), testing::Eq(11));
  ASSERT_THAT(m(1, 1), testing::Eq(25));
  ASSERT_THAT(m(1, 2), testing::Eq(39));
  // third row
  ASSERT_THAT(m(2, 0), testing::Eq(17));
  ASSERT_THAT(m(2, 1), testing::Eq(39));
  ASSERT_THAT(m(2, 2), testing::Eq(61));
};

TEST_F(TestMatrixClass, RhsMultiplicationAndCopyAssignment) {
  Matrix<int> m1 = GetMatrix_1();
  const int multiplier = 5;
  Matrix<int> m;

  m = multiplier * m1;

  ASSERT_THAT(m(0, 0), testing::Eq(5));
  ASSERT_THAT(m(0, 1), testing::Eq(10));
  ASSERT_THAT(m(1, 0), testing::Eq(15));
  ASSERT_THAT(m(1, 1), testing::Eq(20));
};

TEST_F(TestMatrixClass, VertorSum) {
  std::vector<int> vec_1{1, 2, 3}, vec_2{7, 8, 9};
  Matrix<int> m_1(vec_1), m_2(vec_2), m_sum;

  m_sum = m_1 + m_2;

  ASSERT_THAT(m_sum(0, 0), testing::Eq(8));
  ASSERT_THAT(m_sum(0, 1), testing::Eq(10));
  ASSERT_THAT(m_sum(0, 2), testing::Eq(12));
};

TEST_F(TestMatrixClass, SpeedNaiveMulti) {
  size_t rowN = 200;
  size_t colN = 200;
  Matrix<int> m(rowN, colN);
  for (size_t i = 0; i < rowN; i++)
    for (size_t j = 0; j < colN; j++)
      m(i, j) = i + j;

  Matrix<int> m_multi(m * m);
};

TEST_F(TestMatrixClass, SpeedWithTransformMulti) {
  size_t rowN = 200;
  size_t colN = 200;
  Matrix<int> m(rowN, colN);
  for (size_t i = 0; i < rowN; i++)
    for (size_t j = 0; j < colN; j++)
      m(i, j) = i + j;

  Matrix<int> m_multi(m * m);
};

TEST_F(TestMatrixClass, SpeedWithReorderedMulti) {
  size_t rowN = 200;
  size_t colN = 200;
  Matrix<int> m(rowN, colN);
  for (size_t i = 0; i < rowN; i++)
    for (size_t j = 0; j < colN; j++)
      m(i, j) = i + j;

  Matrix<int> m_multi(m ^ m);
}
