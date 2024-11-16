#include "tmatrix.h"

#include <gtest.h>

template <typename T>
class TestTDynamicVector : public ::testing::Test
{
public:
	TDynamicVector<T> *v, *v1, *v2, *v3, *v4, *v5, *v6, *v7;
	void SetUp()
	{
		v = new TDynamicVector<T>(10);
	}
	void SetUp2(std::size_t n)
	{
		v = new TDynamicVector<T>(n);
	}
	void SetUp3()
	{
		T* a = new T[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		v1= new TDynamicVector<T>(a, 10);
		delete[] a;

		v = new TDynamicVector<T>(*v1);

		T* b = new T[10] {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		v2 = new TDynamicVector<T>(b, 10);
		delete[] b;

		T* c = new T[8] {4, 54, 98, 24, 342, 548, 45, 10};
		v3 = new TDynamicVector<T>(c, 8);
		delete[] c;

		T* d = new T[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		v4 = new TDynamicVector<T>(d, 10);
		delete[] d;

		T* e = new T[10]{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
		v5 = new TDynamicVector<T>(e, 10);
		delete[] e;

		T* f = new T[10]{ 3, 6, 9, 12, 15, 18, 21, 24, 27, 30 };
		v6 = new TDynamicVector<T>(f, 10);
		delete[] f;

		T* g = new T[10]{ -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
		v7 = new TDynamicVector<T>(g, 10);
		delete[] g;
	}
	void TearDown()
	{
		delete v;
	}
	void TearDown3()
	{
		delete v1;
		delete v2;
		delete v3;
		delete v4;
		delete v5;
		delete v6;
		delete v7;
	}
};

TYPED_TEST_CASE_P(TestTDynamicVector);

TYPED_TEST_P(TestTDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(this->SetUp2(10));
}

TYPED_TEST_P(TestTDynamicVector, cant_create_too_large_vector) 
{
  ASSERT_ANY_THROW(this->SetUp2(MAX_VECTOR_SIZE + 1));
}

TYPED_TEST_P(TestTDynamicVector, throws_when_create_vector_with_negative_length) 
{
  ASSERT_ANY_THROW(this->SetUp2(-5));
}

TYPED_TEST_P(TestTDynamicVector, can_create_copied_vector)
{
  ASSERT_NO_THROW(this->SetUp3());
}

TYPED_TEST_P(TestTDynamicVector, copied_vector_is_equal_to_source_one) 
{
	this->SetUp3();
	EXPECT_EQ(*(this->v),*(this->v1));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, copied_vector_has_its_own_memory) 
{
	this->SetUp3();
	EXPECT_NE(this->v, this->v1);
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_get_size) 
{
  EXPECT_EQ(10, this->v->size());
}

TYPED_TEST_P(TestTDynamicVector, can_set_and_get_element)
{
  this->v[0][0] = 4;

  EXPECT_EQ(4, (this->v[0][0]));
}

TYPED_TEST_P(TestTDynamicVector, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(this->v->at(-1) = 4);
}

TYPED_TEST_P(TestTDynamicVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(this->v->at(50) = 4);
}

TYPED_TEST_P(TestTDynamicVector, can_assign_vector_to_itself)
{
	*(this->v) = *(this->v);

	EXPECT_EQ(*(this->v), *(this->v));
}

TYPED_TEST_P(TestTDynamicVector, can_assign_vectors_of_equal_size) 
{
	this->SetUp3();
	*(this->v) = *(this->v2);

	EXPECT_EQ(*(this->v), *(this->v2));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, assign_operator_change_vector_size)
{
	this->SetUp3();
	*(this->v) = *(this->v3);
	EXPECT_EQ(this->v->size(),this->v3->size());
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_assign_vectors_of_different_size) 
{
	this->SetUp3();
	*(this->v3) = *(this->v);
	EXPECT_EQ(this->v->size(), this->v3->size());

	EXPECT_EQ(*(this->v3), *(this->v));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, compare_equal_vectors_return_true)
{
	EXPECT_EQ(1, *(this->v)==*(this->v));
}

TYPED_TEST_P(TestTDynamicVector, compare_vector_with_itself_return_true) 
{
	EXPECT_EQ(1, *(this->v) == *(this->v));
}

TYPED_TEST_P(TestTDynamicVector, vectors_with_different_size_are_not_equal)
{
	this->SetUp3();
	EXPECT_EQ(0, *(this->v) == *(this->v3));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_add_scalar_to_vector) 
{
	this->SetUp3();
	*(this->v) = *(this->v) + 1;

	EXPECT_EQ(*(this->v), *(this->v2));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_subtract_scalar_from_vector)
{
	this->SetUp3();

	*(this->v) = *(this->v) - 1;

	EXPECT_EQ(*(this->v), *(this->v4));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_multiply_scalar_by_vector) 
{
	this->SetUp3();
	EXPECT_EQ(*(this->v) * 2 , *(this->v) + *(this->v));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_add_vectors_with_equal_size)
{
	this->SetUp3();
	EXPECT_EQ(*(this->v)+*(this->v5), *(this->v6));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, cant_add_vectors_with_not_equal_size) 
{
	this->SetUp3();
	ASSERT_ANY_THROW(*(this->v) + *(this->v3));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_subtract_vectors_with_equal_size)
{
	this->SetUp3();
	EXPECT_EQ(*(this->v)-*(this->v5), *(this->v7));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	this->SetUp3();
	ASSERT_ANY_THROW(*(this->v) - *(this->v3));
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, can_multiply_vectors_with_equal_size)
{
	this->SetUp3();
	int res = 285;
	int res2 = *(this->v4) * *(this->v4);

	EXPECT_EQ(res, res2);
	this->TearDown3();
}

TYPED_TEST_P(TestTDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	this->SetUp3();
	ASSERT_ANY_THROW(*(this->v) * *(this->v3));
	this->TearDown3();
}

//placeholder for test bodies
REGISTER_TYPED_TEST_CASE_P(TestTDynamicVector, can_create_vector_with_positive_length, cant_create_too_large_vector, throws_when_create_vector_with_negative_length,
	can_create_copied_vector, copied_vector_is_equal_to_source_one, copied_vector_has_its_own_memory, can_get_size, can_set_and_get_element, throws_when_set_element_with_negative_index,
	throws_when_set_element_with_too_large_index, can_assign_vector_to_itself, can_assign_vectors_of_equal_size, assign_operator_change_vector_size, can_assign_vectors_of_different_size,
	compare_equal_vectors_return_true, compare_vector_with_itself_return_true, vectors_with_different_size_are_not_equal, can_add_scalar_to_vector, can_subtract_scalar_from_vector, can_multiply_scalar_by_vector,
	can_add_vectors_with_equal_size, cant_add_vectors_with_not_equal_size, can_subtract_vectors_with_equal_size, cant_subtract_vectors_with_not_equal_size, can_multiply_vectors_with_equal_size, cant_multiply_vectors_with_not_equal_size);
typedef::testing::Types<int, float, double, long, long long> VectorTypes;
INSTANTIATE_TYPED_TEST_CASE_P(VectorTypesInstantiation, TestTDynamicVector, VectorTypes); 
