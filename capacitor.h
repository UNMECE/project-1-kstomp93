#ifndef CAPACITOR_H
#define CAPACITOR_H

// Capacitor structure definition
struct _capacitor {
    double *time;       // Time array
    double *voltage;    // Voltage array
    double *current;    // Current array
    double C;           // Capacitance value
};
typedef struct _capacitor Capacitor;

#endif