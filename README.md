# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Bluetooth Low Energy (BLE) Lab
The Bluetooth Low Energy (BLE) lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* Pololu Gearmotor with Encoder - [Product Link](https://www.pololu.com/product/3675)
* Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE) Module - [Product Link](https://www.adafruit.com/product/2479)

## Pre-Lab

1. What is Bluetooth Low Energy (BLE)? How does it differ from regular Bluetooth in terms of power consumption?

	BLE is a wireless personal area network technology that is used in short-range communication with little power consumption. It differs from Bluetooth by only using 0.01-0.5W and 10-15mA. 

2. What does GAP stand for and what is its purpose? What is the difference between Peripheral and Central devices in the context of BLE?

	GAP stands for Generic Access Profile (for BLE). It controls connections and advertising in Bluetooth. It determines when a device is visible for communication with another device. A central device is the initiator that scans for connections with peripheral devices. Peripheral devices accept connection requests from central devices.

3. What is GATT in BLE, and how does it structure data exchange between connected devices? Provide definitions for the following: Profile, Service, and Characteristic.

	GATT is Generic ATTribute and it defines the way that two BLE devices transfer data back and forth using services and characteristics. 
Profile - a collection of services designed to fulfill a specific use
Service - a collection of related data and features that are grouped for a specific function
Characteristic - lowest level of data in the hierarchy

4. What is an advertising packet in BLE and what information can it contain?

An advertising packet in BLE is a short message sent periodically by a peripheral device to announce its presence to any nearby central device without establishing a connection.

5. What is a UUID used for in BLE and why are 128-bit UUIDs used?

A UUID is used to uniquely identify and standardize GATT structured data like services and characteristics. 128-bit UUIDs are used to ensure that each UUID can have a unique combination to avoid colliding with other devices.

6. What bit from which register determines if the UART data is received or transmitted MSB or LSB first? Refer to the eUSCI_A UART Registers section (24.4) of the MSP432P4xx Technical Reference Manual (SLAU356I).

UCMSB (Bit 13) determines if the data is received or transmitted MSB or LSB first.

7. Provide the mnemonic and primary module function for each pin listed. Refer to Table 6-45 (Default Mapping) on page 126 of the MSP432P401R Datasheet.

P2.2
PM_UCA1RXD/PM_UCA1SOMI
eUSCI_A1 UART RXD (direction controlled by eUSCI - Input)
eUSCI_A1 SPI slave out master in (diction controlled by eUSCI)
P2.3
PM_UCA1TXD/PM_UCA1SIMO
eUSCI_A1 SPI SIMO / UART TXD
eUSCI_A1 UART TXD / SPI SIMO
P3.2
PM_UCA2RXD/PM_UCA2SOMI
eUSCI_A2 UART RXD / SPI SOMI
eUSCI_A2 SPI SOMI / UART RXD
P3.3
PM_UCA2TXD/PM_UCA2SIMO
eUSCI_A2 SPI SIMO / UART TXD
eUSCI_A2 UART TXD / SPI SIMO

8. Write a void function named P2_2_and_P2_3_Init that takes no arguments and configures the following pins to use primary function mode: P2.2 and P2.3. It is not necessary to set the direction of the pins. Refer to the following documents:
Section 12.2.6 - “Function Select Registers (PxSEL0, PxSEL1)” of the MSP432P4xx Technical Reference Manual (SLAU356I)
Section 4.1 - “Pin Diagrams” and Section 6.12.2 - “Port P2 (P2.0 to P2.3) Input/Output With Schmitt Trigger” of the MSP432P401R Datasheet

void P2_2_and_P2_3_Init()
{
	P2->SEL0 |= 0x0C;
	P2->SEL1 &= ~0x0C;
}


## Known Issues or Limitations
- Had to rebuild our bot because it got stolen (RIP).

## Author Contributions
- Code : Erik Santos and Daniel Adrayan
- Pre-Lab : Erik Santos
- Waveforms : Daniel Adrayan

## References
- Lab 4 Documentation
- https://www.ezurio.com/resources/blog/bluetooth-low-energy-vs-bluetooth-classic-what-s-the-difference
- https://www.geeksforgeeks.org/computer-networks/bluetooth-vs-bluetooth-low-energy/
- https://cdn-learn.adafruit.com/downloads/pdf/introduction-to-bluetooth-low-energy.pdf
- https://novelbits.io/bluetooth-low-energy-advertisements-part-1/
