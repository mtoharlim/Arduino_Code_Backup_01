#include <Wire.h>
#include <Adafruit_INA219.h>
 
Adafruit_INA219 ina219;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
  //**************************************************************************/
// Configures to INA219 to be able to measure up to 16V and 30A
//**************************************************************************/
void Plugin_027_setCalibration_16V_30A(void) 
{
float ina219_calValue;
ina219_calValue = 16384;

// Set multipliers to convert raw current/power values
float ina219_currentDivider_mA;
ina219_currentDivider_mA = 1; // Current LSB = 1mA per bit (1/1 = 1)

// Set Calibration register to 'Cal' calculated above
Plugin_027_wireWriteRegister(INA219_REG_CALIBRATION, ina219_calValue);

// Set Config register to take into account the settings above
uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
INA219_CONFIG_GAIN_2_80MV |
INA219_CONFIG_BADCRES_12BIT |
INA219_CONFIG_SADCRES_12BIT_1S_532US |
INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
Plugin_027_wireWriteRegister(INA219_REG_CONFIG, config);
}

//**************************************************************************/
// Setups the HW (defaults to 16V and 30A with 2.5mohms shunt for calibration values)
//**************************************************************************/

void Plugin_027_begin(void) 
{
// Plugin_027_INA219_address = Plugin_027_INA219_address; // INA219_ADDRESS;
float ina219_currentDivider_mA;
ina219_currentDivider_mA = 1;

// Set chip to large range config values to start
Plugin_027_setCalibration_16V_30A();
}
void setup(void) 
{
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  uint32_t currentFrequency;
    
  Serial.begin(115200);
  Serial.println("14CORE | Get Current Test ");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();
 
  Serial.println("Measuring voltage and current with INA219 ...");
  

}
 
void loop(void) 
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
 
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.println("");
 
  delay(2000);
}
