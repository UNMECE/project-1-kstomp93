#include <iostream>
#include <iomanip>
#include <cmath>
#include "capacitor.h"

// Constants
const double dt = 1e-10;          // Time step (s)
const double finalTime = 5e-6;    // Final time (s)
const int numTimesteps = static_cast<int>(finalTime / dt); // Number of timesteps
const double R = 1e3;             // Resistance (ohms)
const double C = 100e-12;         // Capacitance (F)
const double I_constant = 1e-2;   // Constant current (A)
const double V0 = 10.0;           // Initial voltage for constant voltage source (V)



// Function to initialize the capacitor
void initializeCapacitor(Capacitor &cap, double capacitance) {
    cap.C = capacitance;
    cap.time = new double[numTimesteps];
    cap.voltage = new double[numTimesteps];
    cap.current = new double[numTimesteps];

    // Initialize time array
    for (int i = 0; i < numTimesteps; i++) {
        cap.time[i] = i * dt;
    }

    // Initialize voltage and current to 0 at time t = 0
    cap.voltage[0] = 0.0;
    cap.current[0] = I_constant;
}

// Function to simulate constant current charging
void constantCurrentCharge(Capacitor &cap) {
    for (int t = 1; t < numTimesteps; t++) {
        cap.voltage[t] = cap.voltage[t - 1] + (cap.current[t - 1] * dt / cap.C);
        cap.current[t] = I_constant;  // Constant current
        if (t % 200 == 0) {
            std::cout << "Timestep " << t << ": Voltage = " << cap.voltage[t]
                      << " V, Current = " << cap.current[t] << " A" << std::endl;
        }
    }
}

// Function to simulate constant voltage charging
void constantVoltageCharge(Capacitor &cap) {
    for (int t = 1; t < numTimesteps; t++) {
        cap.current[t] = cap.current[t - 1] - ((cap.current[t - 1] * dt) / (R * cap.C));
        cap.voltage[t] = V0 - (cap.current[t] * R);
        if (t % 200 == 0) {
            std::cout << "Timestep " << t << ": Voltage = " << cap.voltage[t]
                      << " V, Current = " << cap.current[t] << " A" << std::endl;
        }
    }
}

// Function to free the dynamically allocated memory
void freeMemory(Capacitor &cap) {
    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;
}

// Main function
int main() {
    Capacitor cap;

    std::cout << std::fixed << std::setprecision(10);

    // Initialize the capacitor
    initializeCapacitor(cap, C);

    // Simulate constant current charging
    std::cout << "\nConstant Current Charging:\n";
    constantCurrentCharge(cap);

    // Reset initial conditions for constant voltage simulation
    cap.voltage[0] = 0.0;
    cap.current[0] = V0 / R;  // Initial current for constant voltage

    // Simulate constant voltage charging
    std::cout << "\nConstant Voltage Charging:\n";
    constantVoltageCharge(cap);

    // Free dynamically allocated memory
    freeMemory(cap);

    return 0;
}
