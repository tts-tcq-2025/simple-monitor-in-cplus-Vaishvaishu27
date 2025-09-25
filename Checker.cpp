#include <iostream>
#include <assert.h>

using namespace std;

// Enum to identify parameters
typedef enum Parameter_ge {
    TEMPERATURE_e,
    SOC_e,
    CHARGE_RATE_e,
} Parameter_te;

//Error messages
const char* errorMessages[] = {
    "Temperature out of range!",
    "State of Charge out of range!",
    "Charge Rate out of range!"
};

// Threshold constants
const float MIN_TEMPERATURE = 0.0f;
const float MAX_TEMPERATURE = 45.0f;

const float MIN_SOC = 20.0f;
const float MAX_SOC = 80.0f;

const float MAX_CHARGE_RATE = 0.8f;

// Console printer for parameter errors
void PrintConsole(int type) {
    if(type >= 0 && type < 3) {
        cout << errorMessages[type] << endl;
    }
}

// Generic range checker
bool ValidateRange(float value, float min, float max, Parameter_te type, void (*console)(int)) {
    bool isOk = (value >= min && value <= max);
    if (!isOk) {
        console(type);
    }
    return isOk;
}

//Only Max range checker
bool ValidateMaxRange(float value, float max, Parameter_te type, void (*console)(int)) {
    bool isOk = (value <= max);
    if (!isOk) {
        console(type);
    }
    return isOk;
}

// Individual checks using ValidateRange
bool TemperatureIsOk(float temperature, void (*console)(int)) {
    return ValidateRange(temperature, MIN_TEMPERATURE, MAX_TEMPERATURE, TEMPERATURE_e, console);
}

bool SocIsOk(float soc, void (*console)(int)) {
    return ValidateRange(soc, MIN_SOC, MAX_SOC, SOC_e, console);
}

bool ChargeRateIsOk(float chargeRate, void (*console)(int)) {
    return ValidateMaxRange(chargeRate, MAX_CHARGE_RATE, CHARGE_RATE_e, console);
}

//Checks battery health status
bool batteryIsOk(float temperature, float soc, float chargeRate) {

    return TemperatureIsOk(temperature, PrintConsole)
        && SocIsOk(soc, PrintConsole)
        && ChargeRateIsOk(chargeRate, PrintConsole);
}

int main() {
    // Good case
    assert(batteryIsOk(25, 70, 0.7) == true);

    //Failed cases
    assert(batteryIsOk(-1, 50, 0.7) == false);  // Temp low
    assert(batteryIsOk(48, 70, 0.6) == false);  // Temp high
    assert(batteryIsOk(32, 18, 0.5) == false);  // SOC low
    assert(batteryIsOk(33, 81, 0.4) == false);  // SOC high
    assert(batteryIsOk(40, 65, 0.9) == false);  // Charge rate high
    assert(batteryIsOk(-3, 15, 1.0) == false);  // All parameters out of range

    // Boundary check
    assert(batteryIsOk(0, 20, 0.0) == true);
    assert(batteryIsOk(45, 80, 0.8) == true);

    // Edge + one parameter fail scenario
    assert(batteryIsOk(46, 80, 0.8) == false);   // Temp high
    assert(batteryIsOk(0, 80, 0.9) == false);    // Charge rate high
    assert(batteryIsOk(45, 19, 0.8) == false);   // Soc high
    
    
    return 0;
    
}
