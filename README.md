# ProgramRobotTani
Program robot penanam benih semangka menggunakan:
- Mikrokontroler Arduino Mega 2560
- Dinamo (sebagai penghisap benih)
- Dua Motor DC (sebagai penggerak robot)
- Dua Motor Stepper (sebagai penggerak posisi penanaman benih semangka)
- Driver Stepper A4988
- Driver Motor DC BTS7960  


LIST PINOUT

#Driver Motor DC (BTS7960)
- Motor 1:
RPWM 6
LPWM 5
R_EN 36
L_EN 36

- Motor 2:
RPWM 7
LPWM 4
R_EN 38
L_EN 38

#Driver Stepper (A4988)
- Stepper 1:
DIR 37
STEP 3
MS1 43
MS2 41
MS3 39
EN 35

- Stepper 2:
DIR 42
STEP 2
MS1 49
MS2 47
MS3 45
EN 40

#Relay(for Dinamo) 44
