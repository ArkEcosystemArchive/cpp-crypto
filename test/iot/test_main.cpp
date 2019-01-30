#if (defined PLATFORMIO && defined UNIT_TEST)

#include <AUnit.h>

// Set Dummy Time for testing board
#include <sys/time.h>
void setDummyTime() {
  // set board time to: 21 March 2019(in seconds)
  // 2 years after Mainnet launch.
  struct timeval tv;
  tv.tv_sec = 1553173200ull; 
  settimeofday(&tv, NULL);
};

void setup() {
  Serial.begin(115200);

  setDummyTime();

  aunit::TestRunner::setTimeout(0);

  delay(1000);
}

void loop() {
  aunit::TestRunner::run();
}

#endif
