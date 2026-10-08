// ННГУ, ИИТММ, Курс "Методы программирования 2"
//
// Лабораторная работа 1. Тесты класса TDynamicMatrix

#include "utmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(3);
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      m[i][j] = static_cast<int>(i * 10 + j);
  TDynamicMatrix<int> m1(m);

  EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 42;
  TDynamicMatrix<int> m1(m);

  m1[0][0] = 13;
  EXPECT_EQ(42, m[0][0]);
  EXPECT_NE(&m[0][0], &m1[0][0]);
  EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);

  EXPECT_EQ(4u, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(4);
  m[1][2] = 7;

  EXPECT_EQ(7, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(4);

  ASSERT_THROW(m.at(static_cast<size_t>(-1)), out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(4);

  ASSERT_ANY_THROW(m.at(4));
  ASSERT_ANY_THROW(m.at(100));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;

  m = m;

  EXPECT_EQ(2u, m.size());
  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(3), m2(3);
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      m2[i][j] = static_cast<int>(i * 3 + j);

  m1 = m2;

  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(2), m2(5);

  m1 = m2;

  EXPECT_EQ(5u, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(2), m2(4);
  for (size_t i = 0; i < 4; i++)
    for (size_t j = 0; j < 4; j++)
      m2[i][j] = static_cast<int>(i * 10 + j);

  m1 = m2;

  EXPECT_TRUE(m1 == m2);
  EXPECT_EQ(4u, m1.size());
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(3), m2(3);
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
    {
      m1[i][j] = static_cast<int>(i + j);
      m2[i][j] = static_cast<int>(i + j);
    }

  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(3);

  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(3), m2(4);

  EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), expected(2);
  m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3; m1[1][1] = 4;
  m2[0][0] = 5; m2[0][1] = 6; m2[1][0] = 7; m2[1][1] = 8;
  expected[0][0] = 6; expected[0][1] = 8; expected[1][0] = 10; expected[1][1] = 12;

  TDynamicMatrix<int> res = m1 + m2;

  EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);

  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), expected(2);
  m1[0][0] = 5; m1[0][1] = 6; m1[1][0] = 7; m1[1][1] = 8;
  m2[0][0] = 1; m2[0][1] = 2; m2[1][0] = 3; m2[1][1] = 4;
  expected[0][0] = 4; expected[0][1] = 4; expected[1][0] = 4; expected[1][1] = 4;

  TDynamicMatrix<int> res = m1 - m2;

  EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);

  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> m(2), expected(2);
  m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
  expected[0][0] = 2; expected[0][1] = 4; expected[1][0] = 6; expected[1][1] = 8;

  TDynamicMatrix<int> res = m * 2;

  EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
  int arr[2] = { 5, 6 };
  TDynamicVector<int> v(arr, 2);

  TDynamicVector<int> res = m * v;

  TDynamicVector<int> expected(2);
  expected[0] = 17; // 1*5 + 2*6
  expected[1] = 39; // 3*5 + 4*6
  EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicVector<int> v(3);

  ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), expected(2);
  m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3; m1[1][1] = 4;
  m2[0][0] = 5; m2[0][1] = 6; m2[1][0] = 7; m2[1][1] = 8;
  expected[0][0] = 19; expected[0][1] = 22;
  expected[1][0] = 43; expected[1][1] = 50;

  TDynamicMatrix<int> res = m1 * m2;

  EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);

  ASSERT_ANY_THROW(m1 * m2);
}
