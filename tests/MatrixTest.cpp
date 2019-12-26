#include<gmock/gmock.h>
// src file for matrix
#include<matrix.h> 

#include <iostream>       // std::cerr
#include <stdexcept>      // std::length_error
using namespace mtx;

class TestMatrixClass: public testing::Test {
	public:	

	Matrix<int> GetMatrix_0(){
 		Matrix<int> m(2,2);
		m(0,0)=0; m(0,1)=0;
		m(1,0)=0; m(1,1)=0;
		return m;
	};
	Matrix<int> GetMatrix_1(){
 		Matrix<int> m(2,2);
		m(0,0)=1; m(0,1)=2;
		m(1,0)=3; m(1,1)=4;
		return m;
	};
	Matrix<int> GetMatrix_2(){
		Matrix<int> m(2,2);
		m(0,0)=2; m(0,1)=5;
		m(1,0)=10; m(1,1)=20;
		return m;
	};
	Matrix<int> GetMatix2times3(){
		Matrix<int> m(2,3);
		m(0,0) = 1; m(0,1) = 2; m(0,2) = 3;	
		m(0,0) = 4; m(0,1) = 5; m(0,2) = 6;
		return m;
	};

	Matrix<int> GetMatix3times2(){
		Matrix<int> m(3,2);
		m(0,0) = 1; m(0,1) = 2;
	       	m(1,0) = 3; m(1,1) = 4; 
		m(2,0) = 5; m(2,1) = 6;
		return m;
	};
};
	
TEST_F(TestMatrixClass, CreateAndInit2DMatrix){
	Matrix<int> m = GetMatrix_1();  
	ASSERT_THAT(m(0,0),testing::Eq(1)); 
	ASSERT_THAT(m(0,1),testing::Eq(2));	
	ASSERT_THAT(m(1,0),testing::Eq(3));
	ASSERT_THAT(m(1,1),testing::Eq(4));
};

TEST_F(TestMatrixClass, AddEqOperator){
	Matrix<int> m = GetMatrix_1();
	Matrix<int> m2 = GetMatrix_1();
	m+=m2;
	ASSERT_THAT(m(0,0),testing::Eq(2));
	ASSERT_THAT(m(0,1),testing::Eq(4));	
	ASSERT_THAT(m(1,0),testing::Eq(6));
	ASSERT_THAT(m(1,1),testing::Eq(8));
};

TEST_F(TestMatrixClass, InitAddOperator){
	Matrix<int> m1 = GetMatrix_1();
	Matrix<int> m2 = GetMatrix_2();
	Matrix<int> m = (m1 + m2) ;	
	ASSERT_THAT(m(0,0),testing::Eq(3));
	ASSERT_THAT(m(0,1),testing::Eq(7));	
	ASSERT_THAT(m(1,0),testing::Eq(13));
	ASSERT_THAT(m(1,1),testing::Eq(24));
};


TEST_F(TestMatrixClass, MathAddOperator){
	Matrix<int> m1 = GetMatrix_1();
	Matrix<int> m2 = GetMatrix_2();
	Matrix<int> m = (m1 + m2) ;	
	m = m + m1; 
	ASSERT_THAT(m(0,0),testing::Eq(4));
	ASSERT_THAT(m(0,1),testing::Eq(9));	
	ASSERT_THAT(m(1,0),testing::Eq(16));
	ASSERT_THAT(m(1,1),testing::Eq(24));
};

TEST_F(TestMatrixClass, InitAddTwoDifferentDimMatricesExeption){
bool is_thrown = false;
Matrix<int> m0 = GetMatrix_0();
Matrix<int> m1 = GetMatix2times3();
	
try{
	m0+=m1;
} 
catch(const MatrixException& me ){
	is_thrown = true;
	ASSERT_STREQ( "different size matrices ", me.what());
  }
};
//TEST(TestMatrix, CreateAndInit2DMatrix){
//	Matrix<int> m(2,2);	
//	m(0,0)=1;
//	m(0,1)=2;
//	m(1,0)=3;
//	m(1,1)=4;
//	ASSERT_THAT(m(0,0),testing::Eq(1));
//	ASSERT_THAT(m(0,1),testing::Eq(2));	
//	ASSERT_THAT(m(1,0),testing::Eq(3));
//	ASSERT_THAT(m(1,1),testing::Eq(4));
//};

TEST(TestMatrix, CheckOutOfMemoryExeption){
bool is_thrown = false;
try{
	std::vector<float> v_f;
	Matrix<float> mt(v_f.max_size(),2);}
catch(const MatrixException& me ){
	is_thrown = true;
	ASSERT_STREQ( "out of memory", me.what());
  }

ASSERT_THAT(is_thrown, testing::Eq(true));

};

TEST(TestMatrix, CheckDegenerateMatrixExeption){
bool is_thrown = false;
try{	
	Matrix<double> mt(12,0);
} 
catch (const MatrixException& me){
	is_thrown =true;
	ASSERT_STREQ("degenerate matrix", me.what());	  
}

ASSERT_THAT(is_thrown, testing::Eq(true));
};

TEST(TestMatrix, CheckOutOfRangeColIndexExeption){
};
