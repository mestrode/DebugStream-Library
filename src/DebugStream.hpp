#pragma once

#ifdef PLATFORMIO_UNIT_TEST
    #include <MockStream.h>
    using Stream = MockStream;
#else
    #include <Stream.h>
#endif

#include <cstdio>
#include <cstdarg>

constexpr auto BUFFERSIZE = 256;

class DebugStream : public Stream
{
private:
    Stream *stream;        // Pointer to a Stream object
    int8_t debugLevel = 0; // Current debug level

public:
    // Constructor that initializes the debug level and a Stream object
    explicit DebugStream(Stream *s, uint8_t level) : stream(s), debugLevel(level)
    {
        static_assert(sizeof(*s) != 0, "Stream pointer cannot be null");
    }

    // Sets the debug level
    void setDebugLevel(const int8_t level)
    {
        debugLevel = level;
    }

    // Returns the current debug level
    uint8_t getDebugLevel() const
    {
        return debugLevel;
    }

    // Overloaded print functions that forward to the underlying stream
    template <typename T>
    size_t print(const int8_t level, const T &value)
    {
        if (level > debugLevel)
        {
            return 0;
        }

        return stream->print(value);
    }

    // Print function for hexadecimal format
    template <typename T>
    size_t print(const int8_t level, const T &value, int base)
    {
        if (level > debugLevel)
        {
            return 0;
        }

        return stream->print(value, base);
    }

    // println function with no parameters for a new line
    size_t println(int8_t level)
    {
        if (level > debugLevel)
        {
            return 0;
        }
        
        return stream->println();
    }

    // Overloaded println functions that forward to the underlying stream
    template <typename T>
    size_t println(int8_t level, const T &value)
    {
        if (level > debugLevel)
        {
            return 0;
        }

        return stream->println(value);
    }

    // Println function for hexadecimal format
    template <typename T>
    size_t println(int8_t level, T value, int base)
    {
        if (level > debugLevel)
        {
            return 0;
        }

        return stream->println(value, base);
    }

    // Formatted print function using printf-style formatting
    size_t printf(int8_t level, const char *format, ...)
    {
        if (level > debugLevel)
        {
            return 0;
        }

        size_t result{0};
        va_list args;
        va_start(args, format);
        char buffer[BUFFERSIZE];                         // Temporary buffer for formatted output
        vsnprintf(buffer, sizeof(buffer), format, args); // Format the string
        result = stream->print(buffer);                  // Output the formatted string to the stream
        va_end(args);
        return result;
    }

    // Required to inherit from Stream
    virtual size_t write(uint8_t c) override { return stream->write(c); }
    virtual size_t write(const uint8_t *buffer, size_t size) override { return stream->write(buffer, size); }
    virtual int available() override { return stream->available(); }
    virtual int read() override { return stream->read(); }
    virtual int peek() override { return stream->peek(); }
    virtual void flush() override { stream->flush(); }
};
