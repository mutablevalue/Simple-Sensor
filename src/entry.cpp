#include "sensor/sensor.h"

int main() {
  Sensor sensor;

  sensor.init();

  while (true) {
    sensor.read_distance();
  }

  return 0;
}
