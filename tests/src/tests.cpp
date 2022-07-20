#include <gtest/gtest.h>
#include <es/string.h>

// Test for basic initialization of strings.
TEST(tests, InitString) {
    String str1 = string_init("Test String");
    String str2 = string_init("");

    ASSERT_EQ(str1.length, strlen("Test String"));
    ASSERT_EQ(str1.capacity, strlen("Test String") + 1);
    ASSERT_EQ(string_compare_cstr(str1, "Test String"), 1);
    ASSERT_NE(str1.contents, nullptr);

    ASSERT_EQ(str2.length, strlen(""));
    ASSERT_EQ(str2.capacity, strlen("") + 1);
    ASSERT_EQ(string_compare_cstr(str2, ""), 1);
    ASSERT_NE(str2.contents, nullptr);

    string_free(str1);
    string_free(str2);
}

// Test for concatenation of String structs.
TEST(tests, ConcatenationOfString) {
    String str1 = string_init("Hello,");
    String str2 = string_init(" World");
    String str3 = string_init("");

    string_concat(&str1, str2);

    ASSERT_EQ(str1.length, strlen("Hello,") + strlen(" World"));
    ASSERT_EQ(str1.capacity, strlen("Hello,") + strlen(" World") + 1);
    ASSERT_EQ(string_compare_cstr(str1, "Hello, World"), 1);
    ASSERT_NE(str1.contents, nullptr);
    ASSERT_EQ(str1.contents[str1.length], '\0');

    // Check for the concatenation of an empty string to an existing string.
    string_concat(&str1, str3);

    ASSERT_EQ(str1.length, strlen("Hello,") + strlen(" World"));
    ASSERT_EQ(str1.capacity, strlen("Hello,") + strlen(" World") + 1);
    ASSERT_EQ(string_compare_cstr(str1, "Hello, World"), 1);
    ASSERT_NE(str1.contents, nullptr);
    ASSERT_EQ(str1.contents[str1.length], '\0');

    // Check for the concatenation of an existing string to an empty string.
    string_concat(&str3, str1);

    ASSERT_EQ(str3.length, strlen("Hello,") + strlen(" World"));
    ASSERT_EQ(str3.capacity, strlen("Hello,") + strlen(" World") + 1);
    ASSERT_EQ(string_compare_cstr(str3, "Hello, World"), 1);
    ASSERT_NE(str3.contents, nullptr);
    ASSERT_EQ(str3.contents[str1.length], '\0');

    string_free(str1);
    string_free(str2);
    string_free(str3);
}

// Test for concatenation of a String struct and a c string.
TEST(tests, ConcatenationofStringWithCStr) {
    String str1 = string_init("Hello,");

    string_concat_cstr(&str1, " World");

    ASSERT_EQ(str1.length, strlen("Hello, World"));
    ASSERT_EQ(str1.capacity, strlen("Hello, World") + 1);
    ASSERT_EQ(string_compare_cstr(str1, "Hello, World"), 1);
    ASSERT_NE(str1.contents, nullptr);
    ASSERT_EQ(str1.contents[str1.length], '\0');

    // Check for the concatenation of an empty c string to an existing string.
    string_concat_cstr(&str1, "");

    ASSERT_EQ(str1.length, strlen("Hello, World"));
    ASSERT_EQ(str1.capacity, strlen("Hello, World") + 1);
    ASSERT_EQ(string_compare_cstr(str1, "Hello, World"), 1);
    ASSERT_NE(str1.contents, nullptr);
    ASSERT_EQ(str1.contents[str1.length], '\0');

    // Check for the concatenation of a large buffer.
    string_concat_cstr(&str1, ". Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book");

    ASSERT_EQ(str1.length, strlen("Hello, World. Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book"));
    ASSERT_EQ(str1.capacity, strlen("Hello, World. Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book") + 1);
    ASSERT_EQ(string_compare_cstr(str1, "Hello, World. Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book"), 1);
    ASSERT_NE(str1.contents, nullptr);
    ASSERT_EQ(str1.contents[str1.length], '\0');

    string_free(str1);
}

// Test to find a given String in another String
TEST(tests, FindStringinString) {
   String str1 = string_init("hello this is a test string");
   String str2 = string_init("test string");
   String str3 = string_init("");

   ASSERT_EQ(string_find(str1, str2), 16);
   ASSERT_EQ(string_find(str1, str3), 0);
   ASSERT_EQ(string_find(str2, str3), 0);
   ASSERT_EQ(string_find(str2, str1), ES_STRING_ERROR);
   ASSERT_EQ(string_find(str3, str1), ES_STRING_ERROR);
   ASSERT_EQ(string_find(str3, str2), ES_STRING_ERROR);

   string_free(str1);
   string_free(str2);
   string_free(str3);
}

// Test to find a given c string in a String.
TEST(tests, FindCStrInString) {
    String str1 = string_init("hello this is a test string");

    ASSERT_EQ(string_find_cstr(str1, "test string"), 16);
    ASSERT_EQ(string_find_cstr(str1, ""), 0);
    ASSERT_EQ(string_find_cstr(str1, "lorem"), ES_STRING_ERROR);

    string_free(str1);
}

// Test to check if a String starts with the given String.
TEST(tests, StartsWith) {
    String str1 = string_init("Hello, World");
    String str2 = string_init("Hello");
    String str3 = string_init("World");
    String str4 = string_init("");

    ASSERT_EQ(string_startswith(str1, str2), 1);
    ASSERT_EQ(string_startswith(str1, str3), 0);
    ASSERT_EQ(string_startswith(str1, str4), 1);

    string_free(str1);
    string_free(str2);
    string_free(str3);
    string_free(str4);
}

// Test to check if a String starts with the given c string
TEST(tests, StartsWithCStr) {
    String str1 = string_init("Hello, World");

    ASSERT_EQ(string_startswith_cstr(str1, "Hello") , 1);
    ASSERT_EQ(string_startswith_cstr(str1, "World"), 0);
    ASSERT_EQ(string_startswith_cstr(str1, ""), 1);

    string_free(str1);
}

// Test to check if a String ends with the given String.
TEST(tests, EndsWith) {
    String str1 = string_init("Hello, World");
    String str2 = string_init("World");
    String str3 = string_init("Hello");
    String str4 = string_init("");

    ASSERT_EQ(string_endswith(str1, str2), 1);
    ASSERT_EQ(string_endswith(str1, str3), 0);
    ASSERT_EQ(string_endswith(str1, str4), 1);

    string_free(str1);
    string_free(str2);
    string_free(str3);
    string_free(str4);
}

// Test to check if a String ends with the given c string
TEST(tests, EndsWithCStr) {
    String str1 = string_init("Hello, World");

    ASSERT_EQ(string_endswith_cstr(str1, "World") , 1);
    ASSERT_EQ(string_endswith_cstr(str1, "Hello"), 0);
    ASSERT_EQ(string_endswith_cstr(str1, ""), 1);

    string_free(str1);
}

// Test to check if a String is equal to the given String.
TEST(tests, Compare) {
    String str1 = string_init("Hello, World!");
    String str2 = string_init("Hello, World!");
    String str3 = string_init("Test String");
    String str4 = string_init("");

    ASSERT_EQ(string_compare(str1, str2), 1);
    ASSERT_EQ(string_compare(str1, str3), 0);
    ASSERT_EQ(string_compare(str1, str4), 0);
    ASSERT_EQ(string_compare(str4, str4), 1);

    string_free(str1);
    string_free(str2);
    string_free(str3);
    string_free(str4);
}

// Test to check if a String is equal to the given c string.
TEST(tests, CompareCStr) {
    String str1 = string_init("Hello, World!");
    String str2 = string_init("");

    ASSERT_EQ(string_compare_cstr(str1, "Hello, World!"), 1);
    ASSERT_EQ(string_compare_cstr(str1, "Test String"), 0);
    ASSERT_EQ(string_compare_cstr(str1, ""), 0);
    ASSERT_EQ(string_compare_cstr(str2, ""), 1);

    string_free(str1);
    string_free(str2);
}

// Test to slice a string
TEST(tests, Slice) {
    String str1 = string_init("foo bar baz");
    String str2 = string_slice(str1, 4, 7);
    String str3 = string_slice(str1, 8, 11);

    ASSERT_EQ(string_compare_cstr(str2, "bar"), 1);
    ASSERT_EQ(string_compare_cstr(str3, "baz"), 1);

    string_free(str1);
    string_free(str2);
    string_free(str3);
}

TEST(tests, ReadFile) {

    #if defined(_WIN32)
    FILE *fp = fopen("..\\..\\src\\data\\file.txt", "r");
    #else
    FILE *fp = fopen("../src/data/file.txt", "r");
    #endif

    String str = string_read_file(fp);

    ASSERT_EQ(string_compare_cstr(str, "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."), 1);

    fclose(fp);
    string_free(str);
}