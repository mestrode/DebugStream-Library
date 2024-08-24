#include "MockStream.h"
#include <cstdio>
#include <iostream>
#include <cstring>

#if defined(_WIN32) || defined(_WIN64)
constexpr std::string_view lineBreak = "\r\n";
#else
constexpr std::string_view lineBreak = "\n";
#endif

MockStream::MockStream()
    : expectBuffer(std::make_shared<std::ostringstream>()),
      outputBuffer(std::make_shared<std::ostringstream>())
{
}

MockStream::~MockStream() {}

void MockStream::begin(unsigned long) {}
void MockStream::begin(unsigned long, uint8_t) {}
void MockStream::end() {}

int MockStream::available() { return 0; }
int MockStream::peek() { return -1; }
int MockStream::read() { return -1; }
void MockStream::flush() { outputBuffer->flush(); }

size_t MockStream::write(uint8_t c)
{
    outputBuffer->put(c);
    return 1;
}

size_t MockStream::write(const uint8_t *buffer, size_t size)
{
    outputBuffer->write(reinterpret_cast<const char *>(buffer), size);
    return size;
}

size_t MockStream::write(unsigned long n)
{
    return write(static_cast<uint8_t>(n));
}

size_t MockStream::write(long n)
{
    return write(static_cast<uint8_t>(n));
}

size_t MockStream::write(unsigned int n)
{
    return write(static_cast<uint8_t>(n));
}

size_t MockStream::write(int n)
{
    return write(static_cast<uint8_t>(n));
}

size_t MockStream::print(const char *pValue)
{
    if (!pValue) // avoid nil pointer
    {
        return 0;
    }

    size_t len = strlen(pValue);
    outputBuffer->write(pValue, len);
    return len;
}

size_t MockStream::print(char pChar)
{
    outputBuffer->put(pChar);
    return 1;
}

// Implementierung für int
size_t MockStream::print(const int value, int pBase)
{
    char buffer[100];
    if (pBase == DEC)
    {
        snprintf(buffer, sizeof(buffer), "%d", value);
    }
    else if (pBase == HEX)
    {
        snprintf(buffer, sizeof(buffer), "%X", value);
    }
    else
    {
        return 0; // Unbekannte Basis
    }

    std::string str(buffer);
    outputBuffer->write(str.c_str(), str.length());
    return str.length();
}

size_t MockStream::print(const unsigned int pValue, int pBase)
{
    return print(static_cast<int>(pValue), pBase); // oder eine spezielle Implementierung
}

// Implementierung für short
size_t MockStream::print(short value, int pBase)
{
    return print(static_cast<int>(value), pBase);
}

// Implementierung für long
size_t MockStream::print(const long value, int pBase)
{
    char buffer[100];
    if (pBase == DEC)
    {
        snprintf(buffer, sizeof(buffer), "%ld", value);
    }
    else if (pBase == HEX)
    {
        snprintf(buffer, sizeof(buffer), "%lX", value);
    }
    else
    {
        return 0; // Unbekannte Basis
    }

    std::string str(buffer);
    outputBuffer->write(str.c_str(), str.length());
    return str.length();
}

// Implementierung für unsigned long
size_t MockStream::print(const unsigned long pValue, int pBase)
{
    char buffer[100];
    if (pBase == DEC)
    {
        snprintf(buffer, sizeof(buffer), "%lu", pValue);
    }
    else if (pBase == HEX)
    {
        snprintf(buffer, sizeof(buffer), "%lX", pValue);
    }
    else
    {
        return 0; // Unbekannte Basis
    }

    std::string str(buffer);
    outputBuffer->write(str.c_str(), str.length());
    return str.length();
}

// Implementierung für unsigned long long
size_t MockStream::print(const unsigned long long pValue, int pBase)
{
    char buffer[100];
    if (pBase == DEC)
    {
        snprintf(buffer, sizeof(buffer), "%llu", pValue);
    }
    else if (pBase == HEX)
    {
        snprintf(buffer, sizeof(buffer), "%llX", pValue);
    }
    else
    {
        return 0; // Unbekannte Basis
    }

    std::string str(buffer);
    outputBuffer->write(str.c_str(), str.length());
    return str.length();
}

size_t MockStream::print(double pValue, int pPrecision)
{
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%.*f", pPrecision, pValue);
    size_t len = strlen(buffer);
    outputBuffer->write(buffer, len);
    return len;
}

size_t MockStream::println(const char *pString)
{
    std::string str(pString);
    outputBuffer->write(str.c_str(), str.length());
    size_t written = str.length();
    written += println();
    return written;
}

size_t MockStream::println(char pChar)
{
    outputBuffer->put(pChar);
    size_t written = 1;
    written += println();
    return written;
}

size_t MockStream::println(unsigned char pValue, int pBase)
{
    size_t written = print(pValue, pBase);
    written += println();
    return written;
}

size_t MockStream::println(int pValue, int pBase)
{
    size_t written = print(pValue, pBase);
    written += println();
    return written;
}

size_t MockStream::println(unsigned int pValue, int pBase)
{
    size_t written = print(pValue, pBase);
    written += println();
    return written;
}

size_t MockStream::println(long pValue, int pBase)
{
    size_t written = print(pValue, pBase);
    written += println();
    return written;
}

size_t MockStream::println(unsigned long pValue, int pBase)
{
    size_t written = print(pValue, pBase);
    written += println();
    return written;
}

size_t MockStream::println(double pValue, int pPrecision)
{
    size_t written = print(pValue, pPrecision);
    written += println();
    return written;
}

size_t MockStream::println()
{
    outputBuffer->write(lineBreak.data(), lineBreak.size());
    return lineBreak.length();
}

void MockStream::expectPrint()
{
}

void MockStream::expectPrint(const std::string_view &str)
{
    expectBuffer->write(str.data(), str.size());
}

void MockStream::expectPrintln(const std::string_view &str)
{
    expectPrint(str);
    expectPrintln();
}

void MockStream::expectPrintln()
{
    expectPrint(lineBreak);
}

std::string MockStream::getOutput() const
{
    return outputBuffer->str();
}

std::string MockStream::getExpectation() const
{
    return expectBuffer->str();
}

bool MockStream::compareOutput()
{
    // cout << "expect" << getExpectation() << endl;
    // cout << "output" << getOutput() << endl;

    bool result = expectBuffer->str() == outputBuffer->str();
    if (result)
    {
        this->resetExpectations();
    }
    return result;
}

void MockStream::resetExpectations()
{
    expectBuffer->str("");
    expectBuffer->clear();
    outputBuffer->str("");
    outputBuffer->clear();
}
