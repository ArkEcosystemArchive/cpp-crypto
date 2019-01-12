#if (defined PLATFORMIO && defined UNIT_TEST)

#include <AUnit.h>

void setup() {
    Serial.begin(115200);
    
	while (!Serial) { delay(100); };
	// ^for the Arduino Leonardo/Micro only
	
	aunit::TestRunner::setTimeout(0);
	
	delay(1000);
}

void loop() { aunit::TestRunner::run(); }

#endif