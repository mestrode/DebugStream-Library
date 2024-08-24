#pragma once

#include <Stream.h>
#include <cstdio>
#include <cstdarg>

class DebugStream : public Stream {
private:
    Stream* stream;      // Pointer to a Stream object
    uint8_t debugLevel;  // Current debug level

public:
    // Constructor that initializes the debug level and a Stream object
    explicit DebugStream(Stream* s, uint8_t level) : stream(s), debugLevel(level) {}

    // Sets the debug level
    void setDebugLevel(uint8_t level) {
        debugLevel = level;
    }

    // Returns the current debug level
    uint8_t getDebugLevel() const {
        return debugLevel;
    }

    // Overloaded print functions that forward to the underlying stream
    template<typename T>
    void print(uint8_t level, const T& value) {
        if (level <= debugLevel) {
            stream->print(value);
        }
    }

    // Print function for hexadecimal format
    void print(uint8_t level, unsigned long value, int base) {
        if (level <= debugLevel) {
            stream->print(value, base);
        }
    }

    // println function with no parameters for a new line
    void println(uint8_t level) {
        if (level <= debugLevel) {
            stream->println();
        }
    }

    // Overloaded println functions that forward to the underlying stream
    template<typename T>
    void println(uint8_t level, const T& value) {
        if (level <= debugLevel) {
            stream->println(value);
        }
    }

    // Formatted print function using printf-style formatting
    void printf(uint8_t level, const char* format, ...) {
        if (level <= debugLevel) {
            va_list args;
            va_start(args, format);
            char buffer[256]; // Temporary buffer for formatted output
            vsnprintf(buffer, sizeof(buffer), format, args); // Format the string
            stream->print(buffer); // Output the formatted string to the stream
            va_end(args);
        }
    }

    // Required to inherit from Stream
    virtual size_t write(uint8_t c) override {
        return stream->write(c);
    }

    virtual size_t write(const uint8_t* buffer, size_t size) override {
        return stream->write(buffer, size);
    }

    virtual int available() override {
        return stream->available();
    }

    virtual int read() override {
        return stream->read();
    }

    virtual int peek() override {
        return stream->peek();
    }

    virtual void flush() override {
        stream->flush();
    }
};
