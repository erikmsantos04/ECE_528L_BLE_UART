/**
 * @file main.c
 *
 * @brief Main source code for the BLE_UART program.
 *
 * This file contains the main entry point for the BLE_UART program,
 * which is used to demonstrate the BLE_UART driver.
 *
 * It interfaces with the Adafruit Bluefruit LE UART Friend Bluetooth Low Energy (BLE) module, which uses the UART communication protocol.
 *  - Product Link: https://www.adafruit.com/product/2479
 *
 * @note For more information regarding the Enhanced Universal Serial Communication Interface (eUSCI),
 * refer to the MSP432Pxx Microcontrollers Technical Reference Manual
 *
 * @author Erik Santos
 *
 */

#include <stdint.h>
#include <math.h>
#include "msp.h"

#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/Motor.h"
#include "inc/BLE_UART.h"

// Initialize constant PWM duty cycle values for the motors
#define PWM_NOMINAL 3000

void Process_BLE_UART_Data(char BLE_UART_Buffer[])
{
    if (Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED GREEN"))
    {
        LED2_Output(RGB_LED_GREEN);
    }
    else if (Check_BLE_UART_Data(BLE_UART_Buffer, "RGB LED OFF"))
    {
        LED2_Output(RGB_LED_OFF);
    }
    else
    {
        printf("BLE UART Command Not Found\n");
    }
}

void Decode_Controller_Packet(const char *BLE_UART_Buffer)
{
    // 1. Verify Byte 0 is '!' (0x21) and Byte 1 is 'B' (0x42)
    if (BLE_UART_Buffer[0] != '!' || BLE_UART_Buffer[1] != 'B') {
        return; // Invalid packet or not a Button packet
    }

    // 2. Read Byte 3 to determine button state ('1' = Pressed, '0' = Released)
    uint8_t is_pressed = 0;
    if (BLE_UART_Buffer[3] == '1') {
        is_pressed = 1;
    } else if (BLE_UART_Buffer[3] == '0') {
        is_pressed = 0;
    } else {
        return; // Invalid state byte
    }

    // 3. Read Byte 2 to determine which button was pressed/released
    switch (BLE_UART_Buffer[2]) {
        case '5': // Up
            if (is_pressed) {
                // Handle Up Pressed
                Motor_Forward(3000, 3000);
            } else {
                // Handle Up Released
                Motor_Stop();
            }
            break;

        case '6': // Down
            if (is_pressed) {
                // Handle Down Pressed
                Motor_Backward(3000, 3000);
            } else {
                // Handle Down Released
                Motor_Stop();
            }
            break;

        case '7': // Left
            if (is_pressed) {
                // Handle Left Pressed
                Motor_Left(3000, 3000);
            } else {
                // Handle Left Released
                Motor_Stop();
            }
            break;

        case '8': // Right
            if (is_pressed) {
                // Handle Right Pressed
                Motor_Right(3000, 3000);
            } else {
                // Handle Right Released
                Motor_Stop();
            }
            break;

        default:
            // Unrecognized button ID
            Motor_Stop();
            break;
    }
}

/*
int main(void)
{
    // Ensure that the interrupts are disabled during initialization
    DisableInterrupts();

    // Initialize the 48 MHz Clock
    Clock_Init48MHz();

    // Initialize the RGB LED on the MSP432 microcontroller
    LED2_Init();

    // Initialize the EUSCI_A0_UART module
    EUSCI_A0_UART_Init_Printf();

    // Initialize the Adafruit Bluefruit LE UART Friend module
    BLE_UART_Init();

    // Initialize the DC motors
    Motor_Init();

    // Initialize a buffer that will be used to receive command string from the BLE module
    char BLE_UART_Buffer[BLE_UART_BUFFER_SIZE] = {0};

    // Enable the interrupts used by the modules
    EnableInterrupts();

    // Provide a short delay after initialization and reset the BLE module
    Clock_Delay1ms(1000);
    BLE_UART_Reset();

    // Send a message to the BLE module to check if the connection is stable
    BLE_UART_OutString("BLE UART Active\r\n");
    Clock_Delay1ms(1000);

    while(1)
    {
        int string_size = BLE_UART_InString(BLE_UART_Buffer, BLE_UART_BUFFER_SIZE);

        printf("BLE UART Data: ");

        for (int i = 0; i < string_size; i++)
        {
            printf("%c", BLE_UART_Buffer[i]);
        }

        printf("\n");

        Process_BLE_UART_Data(BLE_UART_Buffer);
    }
}
*/

/*
int main()
{
    // Ensure that the interrupts are disabled during initialization
        DisableInterrupts();

        // Initialize the 48 MHz Clock
        Clock_Init48MHz();

        // Initialize the RGB LED on the MSP432 microcontroller
        LED2_Init();

        // Initialize the EUSCI_A0_UART module
        EUSCI_A0_UART_Init_Printf();

        // Initialize the Adafruit Bluefruit LE UART Friend module
        BLE_UART_Init();

        // Initialize the DC motors
        Motor_Init();

        // Initialize a buffer that will be used to receive command string from the BLE module
        char BLE_UART_Buffer[BLE_UART_BUFFER_SIZE] = {0};

        // Enable the interrupts used by the modules
        EnableInterrupts();

        // Provide a short delay after initialization and reset the BLE module
        Clock_Delay1ms(1000);
        BLE_UART_Reset();

        // Send a message to the BLE module to check if the connection is stable
        BLE_UART_OutString("BLE UART Active\r\n");
        Clock_Delay1ms(1000);


        while(1){
            BLE_UART_OutChar(0xAA);
            Clock_Delay1ms(1000);
            BLE_UART_OutChar(0x55);
            Clock_Delay1ms(1000);
            BLE_UART_OutChar(0xFF);
            Clock_Delay1ms(1000);
            BLE_UART_OutChar(0x00);
            Clock_Delay1ms(1000);
        }
}
*/

/*
int main()
{
    // Ensure that the interrupts are disabled during initialization
        DisableInterrupts();

        // Initialize the 48 MHz Clock
        Clock_Init48MHz();

        // Initialize the RGB LED on the MSP432 microcontroller
        LED2_Init();

        // Initialize the EUSCI_A0_UART module
        EUSCI_A0_UART_Init_Printf();

        // Initialize the Adafruit Bluefruit LE UART Friend module
        BLE_UART_Init();

        // Initialize the DC motors
        Motor_Init();

        // Initialize a buffer that will be used to receive command string from the BLE module
        char BLE_UART_Buffer[BLE_UART_BUFFER_SIZE] = {0};

        // Enable the interrupts used by the modules
        EnableInterrupts();

        // Provide a short delay after initialization and reset the BLE module
        Clock_Delay1ms(1000);
        BLE_UART_Reset();

        // Send a message to the BLE module to check if the connection is stable
        BLE_UART_OutString("BLE UART Active\r\n");
        Clock_Delay1ms(1000);

        PMOD_SWT_Init();

        while(1){

            uint8_t switch_status = Get_PMOD_SWT_Status();
            switch(switch_status)
                {
                    case 0x01:
                    {
                        BLE_UART_OutChar(0xAA);
                        Clock_Delay1ms(1000);
                    }
                    break;

                    case 0x02:
                    {
                        BLE_UART_OutChar(0x10);
                        Clock_Delay1ms(1000);
                    }
                    break;

                    case 0x04:
                    {
                        BLE_UART_OutChar(0xF0);
                        Clock_Delay1ms(1000);
                    }
                    break;

                    case 0x08:
                    {
                        BLE_UART_OutChar(0x0F);
                        Clock_Delay1ms(1000);
                    }
                    break;

                    default:
                    {
                        BLE_UART_OutChar(0x00);
                        Clock_Delay1ms(1000);
                    }
                }
        }
}
*/

int main()
{
    // Ensure that the interrupts are disabled during initialization
        DisableInterrupts();

        // Initialize the 48 MHz Clock
        Clock_Init48MHz();

        // Initialize the RGB LED on the MSP432 microcontroller
        LED2_Init();

        // Initialize the EUSCI_A0_UART module
        EUSCI_A0_UART_Init_Printf();

        // Initialize the Adafruit Bluefruit LE UART Friend module
        BLE_UART_Init();

        // Initialize the DC motors
        Motor_Init();

        // Initialize a buffer that will be used to receive command string from the BLE module
        char BLE_UART_Buffer[BLE_UART_BUFFER_SIZE] = {0};

        // Enable the interrupts used by the modules
        EnableInterrupts();

        // Provide a short delay after initialization and reset the BLE module
        Clock_Delay1ms(1000);
        BLE_UART_Reset();

        // Send a message to the BLE module to check if the connection is stable
        BLE_UART_OutString("BLE UART Active\r\n");
        Clock_Delay1ms(1000);

        PMOD_SWT_Init();

        while(1){

            int bytes = BLE_UART_InPacket(BLE_UART_Buffer, BLE_UART_BUFFER_SIZE);

            if (bytes == 5) {
                Decode_Controller_Packet(BLE_UART_Buffer);
            }

        }
}


