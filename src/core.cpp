#include "sensor/sensor.h"
#include "uart.h"
#include "util/delay.h"
class Core {
private:
  bool SensorState = true; // true/false = on/off
  bool CommunicationState = false;

  Sensor SensorSystem;
  Communication CommunicationSystem;

public:
  void set_sensor_state() { SensorState = !SensorState; }

  void set_communication_state() { CommunicationState = !CommunicationState; }

  bool get_sensor_state() { return SensorState; }

  inline void init() {
    SensorSystem.init();
    // Communication system gets initialized on usage
  };

  inline void run_service() {
    while (true) {
      if (SensorState) {
        SensorSystem.read_distance();
        set_sensor_state();
        set_communication_state();
      }
      if (CommunicationState) {
        uint32_t CurrentDistance = SensorSystem.get_distance();
        CommunicationSystem.write_string("Distance: ");
        CommunicationSystem.write_uint32(CurrentDistance);
        CommunicationSystem.write_line(" cm");
        set_communication_state();
        set_sensor_state();
      }
      _delay_ms(1000);
    }
  }
};
