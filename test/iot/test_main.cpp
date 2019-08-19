#if (defined PLATFORMIO && defined UNIT_TEST)

#include <gtest/gtest.h>

#include <Arduino.h>

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

  testing::InitGoogleTest();

  auto __attribute__((unused)) run = RUN_ALL_TESTS();
}

void loop() {
  // do nothing
}

#endif
