#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"

TEST(matri, empty) {
  otus::Matrix<int, -1> m { };
  EXPECT_EQ(m.size(), 0);
  for (size_t i { }; i < 100; ++i) {
    for (size_t j { }; j < 100; ++j) {
      EXPECT_EQ(m[i][j], -1);
      EXPECT_NE(m[i][j], 0);
    }
  }
}

TEST(matri, values) {
  otus::Matrix<int, -1> m { };

  m[100][100] = 1;
  m[100][101] = 2;
  m[101][100] = 3;

  EXPECT_EQ(m.size(), 3);

  for (size_t i { }; i < 100; ++i) {
    for (size_t j { }; j < 100; ++j) {
      EXPECT_EQ(m[i][j], -1);
      EXPECT_NE(m[i][j], 0);
    }
  }

  std::array<std::tuple<size_t, size_t, int>, 3> a {
    std::make_tuple(100, 100, 1),
    std::make_tuple(100, 101, 2),
    std::make_tuple(101, 100, 3)
  };
  for (auto i: m) {
    bool found { false };
    std::for_each(
      a.begin(),
      a.end(),
      [&i, &found](auto item) { if (i == item) found = true; });
    EXPECT_TRUE(found);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
