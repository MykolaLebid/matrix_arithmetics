#include<gmock/gmock.h>
// src file for matrix
#include<matrix.h> 

#include <iostream>       // std::cerr
#include <stdexcept>      // std::length_error
using namespace mtx;
TEST(TestMatrix, CreateAndInit2DMatrix){
	Matrix<int> m(2,2);	
	m(0,0)=1;
	m(0,1)=2;
	m(1,0)=3;
	m(1,1)=4;
	ASSERT_THAT(m(0,0),testing::Eq(1));
	ASSERT_THAT(m(0,1),testing::Eq(2));	
	ASSERT_THAT(m(1,0),testing::Eq(3));
	ASSERT_THAT(m(1,1),testing::Eq(4));
};

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
