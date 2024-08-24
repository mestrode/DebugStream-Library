#include "DebugStream.hpp"

DebugStream Debug(&Serial, 2);

void setup() {
    Serial.begin(9600);

    Debug.setDebugLevel(1);
    Debug.print(1, "Debug level 1\n");  // Wird auf Serial1 ausgegeben
    Debug.print(2, "Debug level 2\n");  // Wird nicht ausgegeben
    Debug.println(0, "Hello World");    // Wird auf Serial1 ausgegeben
    Debug.printf(1, "Formatted number: %d\n", 42); // Wird auf Serial1 ausgegeben
}

void loop() {

}
