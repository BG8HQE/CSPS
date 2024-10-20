#include "KCORES_CSPS.h"
#include "esphome.h"

CSPS PowerSupply(0x5F, 0x57,true);

class CSPSPower : public PollingComponent {
  public:
  	TextSensor *name = new TextSensor();
  	TextSensor *ct = new TextSensor();
    Sensor *fan_speed = new Sensor();
    Sensor *temp1 = new Sensor();
    Sensor *power_in = new Sensor();
    Sensor *power_out = new Sensor();
    Sensor *current_out = new Sensor();
    Sensor *voltage_out = new Sensor();
    Sensor *voltage_in = new Sensor();

    CSPSPower(): PollingComponent(5000) { }

    void setup() override {
      Wire.setClock(100000);

      ESP_LOGD("Power Supply", "Spare Part No: %s", PowerSupply.getSPN().c_str());
      ESP_LOGD("Power Supply", "Manufacture Date: %s", PowerSupply.getMFG().c_str());
      ESP_LOGD("Power Supply", "Manufacturer: %s", PowerSupply.getMFR().c_str());
      ESP_LOGD("Power Supply", "Power Name: %s", PowerSupply.getName().c_str());
      ESP_LOGD("Power Supply", "Option Kit No: %s", PowerSupply.getOKN().c_str());
      ESP_LOGD("Power Supply", "CT Date Codes: %s", PowerSupply.getCT().c_str());
    }

    void update() override {
      name->publish_state(PowerSupply.getName().c_str());
      ct->publish_state(PowerSupply.getCT().c_str());
      fan_speed->publish_state(PowerSupply.getFanRPM());
      temp1->publish_state(PowerSupply.getTemp1());
      power_out->publish_state(PowerSupply.getOutputPower());
      power_in->publish_state(PowerSupply.getInputPower());
      current_out->publish_state(PowerSupply.getOutputCurrent());
      voltage_out->publish_state(PowerSupply.getOutputVoltage());
      voltage_in->publish_state(PowerSupply.getInputVoltage());
    }
    
    void set_fan_rpm(float state) {
      PowerSupply.setFanRPM(state);
    }
};