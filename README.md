# Automated-hand-washing-system

Software design and simulation for an automated hand washing system based on the ATtiny13 microcontroller.

**Requirements (for simulation)**

1.)Atmel studio 6 or 7 (preferably 7) or Arduino IDE

2.)Proteus 8.x (preferably 8.6)

**How to use**

1.)Compile the source files in Atmel studio or Arduino IDE (with verbose settings enabled for compilation).

2.)Open the proteus simulation file.

3.)Click on the ATtiny13 microcontroller and locate a dialog box called **program file**.

4.)Copy the path for the hex file generated after compiling the source code.

5.)Paste the path into the **program file** dialog box in step 3.

6.)Run the simulation and enjoy yourself.

**Simulating a proximity sensor**

To simulate a situation in which a user of the device places his/her palms close to an infrared sensor, a potentiometer (RV1 in the simulation file) should be used as follows:

1)Reduce the value of the potentiometer to a value below 50%.

2)Return the value of the potentiometer to 50%.
