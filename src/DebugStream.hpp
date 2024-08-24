#pragma once

#include <Stream.h>
#include <optional>
#include <cstdio>
#include <cstdarg>

class DebugStream : public Stream {
private:
    Stream* stream;      // Zeiger auf ein Stream-Objekt
    uint8_t debugLevel;  // Der aktuelle Debug-Level

public:
    // Konstruktor, der den Anfangs-Debug-Level und ein Stream-Objekt festlegt
    explicit DebugStream(Stream* s, uint8_t level) : stream(s), debugLevel(level) {}

    // Setzt den Debug-Level
    void setDebugLevel(uint8_t level) {
        debugLevel = level;
    }

    // Gibt den aktuellen Debug-Level zurück
    uint8_t getDebugLevel() const {
        return debugLevel;
    }

    // Überladene print-Funktionen, die den Stream weiterleiten
    template<typename T>
    void print(uint8_t level, const T& value) {
        if (level <= debugLevel) {
            stream->print(value);
        }
    }

    // Überladene println-Funktionen, die den Stream weiterleiten
    template<typename T>
    void println(uint8_t level) {
        if (level <= debugLevel) {
            stream->println();
        }
    }

    // Überladene println-Funktionen, die den Stream weiterleiten
    template<typename T>
    void println(uint8_t level, const T& value) {
        if (level <= debugLevel) {
            stream->println(value);
        }
    }

    // Überladene printf-Funktion, die den Stream weiterleitet
    void printf(uint8_t level, const char* format, ...) {
        if (level <= debugLevel) {
            va_list args;
            va_start(args, format);
            char buffer[256]; // Temporärer Puffer für das formatierte Ergebnis
            vsnprintf(buffer, sizeof(buffer), format, args); // Formatieren der Zeichenkette
            stream->print(buffer); // Ausgabe an den Stream
            va_end(args);
        }
    }

    // Notwendige Methoden, um von Stream zu erben
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
