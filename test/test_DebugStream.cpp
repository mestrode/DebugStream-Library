#include <unity.h>

#include <iostream>

#include <MockStream.h>
#include "DebugStream.hpp"

MockStream mockStream;

void test_SetAndGetDebugLevel()
{
    DebugStream debugStream(&mockStream, 3);
    TEST_ASSERT_EQUAL(3, debugStream.getDebugLevel());

    debugStream.setDebugLevel(5);
    TEST_ASSERT_EQUAL(5, debugStream.getDebugLevel());
}

void test_PrintWithDebugLevel()
{
    DebugStream debugStream(&mockStream, 3);

    // Expect mockStream.print to be called
    mockStream.expectPrint();
    debugStream.print(4, "Hello"); // Should not print, debugLevel is 3
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    mockStream.expectPrint("World");
    debugStream.print(3, "World"); // Should print, debugLevel is 3
    TEST_ASSERT_TRUE(mockStream.compareOutput());
}

void test_PrintlnWithDebugLevel()
{
    DebugStream debugStream(&mockStream, 2);

    // Expect mockStream.println to be called
    mockStream.expectPrint();
    debugStream.println(3, "Hello"); // Should not print, debugLevel is 2
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    mockStream.expectPrintln("aa");
    debugStream.println(2, "aa"); // Should print, debugLevel is 2
    TEST_ASSERT_TRUE(mockStream.compareOutput());
}

void test_PrintfWithDebugLevel()
{
    DebugStream debugStream(&mockStream, 3);

    // Expect mockStream.print to be called with formatted string
    mockStream.expectPrint("Formatted 42");
    debugStream.printf(3, "Formatted %d", 42); // Should print, debugLevel is 3
}

void test_PrintReturnBytes()
{
    DebugStream debugStream(&mockStream, 3);

    // Test für verschiedene Typen von Daten
    size_t bytesPrinted;

    // Test für char
    mockStream.expectPrint("A");
    bytesPrinted = debugStream.print(3, 'A');
    TEST_ASSERT_EQUAL(1, bytesPrinted);
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für int
    mockStream.expectPrint("123");
    bytesPrinted = debugStream.print(3, 123);
    TEST_ASSERT_EQUAL(3, bytesPrinted);
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für unsigned int
    mockStream.expectPrint("456");
    bytesPrinted = debugStream.print(3, 456U);
    TEST_ASSERT_EQUAL(3, bytesPrinted);
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für long
    mockStream.expectPrint("7890");
    bytesPrinted = debugStream.print(3, 7890L);
    TEST_ASSERT_EQUAL(4, bytesPrinted);
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für unsigned long
    mockStream.expectPrint("12345");
    bytesPrinted = debugStream.print(3, 12345UL);
    TEST_ASSERT_EQUAL(5, bytesPrinted);
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für double
    mockStream.expectPrint("3.14");
    bytesPrinted = debugStream.print(3, 3.14, 2);
    TEST_ASSERT_EQUAL(4, bytesPrinted);
    TEST_ASSERT_TRUE(mockStream.compareOutput());
}

void test_PrintlnReturnBytes()
{
    DebugStream debugStream(&mockStream, 2);

    // Test für verschiedene Typen von Daten
    size_t bytesPrinted;

    // Test für char
    mockStream.expectPrintln("B");
    bytesPrinted = debugStream.println(2, 'B');
    TEST_ASSERT_EQUAL(2, bytesPrinted); // 1 Byte für 'B' und 1 Byte für '\n'
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für int
    mockStream.expectPrintln("456");
    bytesPrinted = debugStream.println(2, 456);
    TEST_ASSERT_EQUAL(4, bytesPrinted); // 3 Bytes für "456" und 1 Byte für '\n'
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für unsigned int
    mockStream.expectPrintln("789");
    bytesPrinted = debugStream.println(2, 789U);
    TEST_ASSERT_EQUAL(4, bytesPrinted); // 3 Bytes für "789" und 1 Byte für '\n'
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für long
    mockStream.expectPrintln("101112");
    bytesPrinted = debugStream.println(2, 101112L);
    TEST_ASSERT_EQUAL(7, bytesPrinted); // 6 Bytes für "101112" und 1 Byte für '\n'
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für unsigned long
    mockStream.expectPrintln("131415");
    bytesPrinted = debugStream.println(2, 131415UL);
    TEST_ASSERT_EQUAL(7, bytesPrinted); // 6 Bytes für "131415" und 1 Byte für '\n'
    TEST_ASSERT_TRUE(mockStream.compareOutput());

    // Test für double
    mockStream.expectPrintln("6.28");
    bytesPrinted = debugStream.println(2, 6.28, 2); // 2 Dezimalstellen
    // std::cout << "Expected '" << mockStream.getExpectation() << "'" << std::endl;
    // std::cout << "Output   '" << mockStream.getOutput() << "'" << std::endl;
    // std::cout << "bytesPrinted: " << bytesPrinted << std::endl;
    TEST_ASSERT_EQUAL(5, bytesPrinted); // 4 Bytes für "6.28" und 1 Byte für '\n'
    TEST_ASSERT_TRUE(mockStream.compareOutput());
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_SetAndGetDebugLevel);
    RUN_TEST(test_PrintWithDebugLevel);
    RUN_TEST(test_PrintlnWithDebugLevel);
    RUN_TEST(test_PrintfWithDebugLevel);
    RUN_TEST(test_SetAndGetDebugLevel);
    RUN_TEST(test_PrintWithDebugLevel);
    RUN_TEST(test_PrintlnWithDebugLevel);
    RUN_TEST(test_PrintfWithDebugLevel);
    RUN_TEST(test_PrintReturnBytes);
    RUN_TEST(test_PrintlnReturnBytes);
    UNITY_END();
    return 0;
}