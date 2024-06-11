#include "pch.h"
#include "String.h"

TEST(StringTest, DefaultConstructor) {
    String s;
    EXPECT_EQ(s.get(0), '\0');
}

TEST(StringTest, CStrConstructor) {
    String s("hello");
    EXPECT_EQ(s.get(0), 'h');
    EXPECT_EQ(s.get(1), 'e');
    EXPECT_EQ(s.get(2), 'l');
    EXPECT_EQ(s.get(3), 'l');
    EXPECT_EQ(s.get(4), 'o');
}

TEST(StringTest, CopyConstructor) {
    String s1("hello");
    String s2(s1);
    EXPECT_EQ(s2.get(0), 'h');
    EXPECT_EQ(s2.get(1), 'e');
    EXPECT_EQ(s2.get(2), 'l');
    EXPECT_EQ(s2.get(3), 'l');
    EXPECT_EQ(s2.get(4), 'o');
}

TEST(StringTest, AssignmentOperator) {
    String s1("hello");
    String s2 = s1;
    EXPECT_EQ(s2.get(0), 'h');
    EXPECT_EQ(s2.get(1), 'e');
    EXPECT_EQ(s2.get(2), 'l');
    EXPECT_EQ(s2.get(3), 'l');
    EXPECT_EQ(s2.get(4), 'o');
}

TEST(StringTest, CopyOnChange) {
    String s1("hello");
    String s2 = s1;
    s1.set(0, 'H');
    EXPECT_EQ(s1.get(0), 'H');
    EXPECT_EQ(s2.get(0), 'h');
}

TEST(StringTest, SetMethod) {
    String s("hello");
    s.set(0, 'H');
    EXPECT_EQ(s.get(0), 'H');
}

TEST(StringTest, Concatenation) {
    String s1("hello");
    String s2("world");
    String s3 = s1 + s2;
    EXPECT_EQ(s3.get(0), 'h');
    EXPECT_EQ(s3.get(5), 'w');
    EXPECT_EQ(s3.get(9), 'd');
}

TEST(StringTest, OutputOperator) {
    String s("hello");
    std::stringstream ss;
    ss << s;
    EXPECT_EQ(ss.str(), "hello");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
