/*
 * gps.c
 *
 *  Created on: 15-03-2024
 *      Author: Diksha Jadhav
 */

#define MAX_DATA_CHUNK_SIZE  30

#include "string.h"
#include "DAVE.h"
#include "GPS.h"
#include "Vcu_Init.h"
#include "Vcu_Config.h"

uint32_t getout;

void clear_readbuff(char string[])
{
	for(int i = 0; i < 65; i++)
		string[i] = '\0';
}

void data_tx4g(char tx_cmd[])//uint8_t
{
	UART_Transmit(&UART_0, (uint8_t*)tx_cmd, (uint32_t)strlen(tx_cmd));

	//Delay(5);
}

void Gps_init(){

	char SendGPSData20[]="AT+QGPSCFG=\"outport\",\"none\"\r\n";
	char SendGPSData21[]="AT+QGPS=1\r\n";

	data_tx4g(SendGPSData20);
	data_rx4g();
	data_tx4g(SendGPSData21);
	data_rx4g();
}

void Get_CurrentLocation() {
    DIGITAL_IO_SetOutputHigh(&RTS);
    //delay(5000);
    bool cts_in = DIGITAL_IO_GetInput(&CTS);
    char SendGPSData5[] = "AT+QGPSLOC=1\r\n";
    //SuperLooptime_Start();
    data_tx4g(SendGPSData5);
    //SuperLooptime_End();

    // Read GPS data four times and concatenate
    char receivedData[MAX_DATA_CHUNK_SIZE * 12 + 1];  // Increased buffer size for four readings
    receivedData[0] = '\0'; // Ensure string is empty initially
    //SuperLooptime_Start();
    for (int i = 0; i < 4; ++i) {
        strcat(receivedData, data_rx4gps());
    }
    //SuperLooptime_End();
    char* startToken = strstr(receivedData, "+QGPSLOC:");
    if (startToken != NULL) {
        char *token;
        token = strtok(startToken, ",");
        int field_count = 0;
        char latitude[12], longitude[13], hdop[5], altitude[6], direction[7];
        while (token != NULL) {
            if (field_count == 1) { // Latitude
                strncpy(latitude, token, 10);
                latitude[10] = '\0';
                GPS_data_val.latitude = ((atoi(latitude))*100000);
                GPS_data_val.latitude += (atoi(latitude+5));
            } else if (field_count == 3) { // Longitude
                strncpy(longitude, token, 11);
                longitude[11] = '\0';
                GPS_data_val.longitude = ((atoi(longitude))*100000);
                GPS_data_val.longitude += (atoi(longitude+6));
            } else if (field_count == 6) { // Altitude
                strncpy(altitude, token, 5);
                altitude[5] = '\0';
                GPS_data_val.altitude =  ((atoi(altitude))*10);
                GPS_data_val.altitude +=( atoi(altitude+4));
            } else if (field_count == 8) { // COG as direction
                strncpy(direction, token, 6);
                direction[6] = '\0';
                GPS_data_val.direction = atoi(direction) * 10;
                break; // Stop parsing after direction field
            }
            field_count++;
            token = strtok(NULL, ",");
        }
    }

    // Clear read buffer
    clear_readbuff(receivedData);

    getout = 0;
}


char* data_rx4gps() {
    static char ReadData[MAX_DATA_CHUNK_SIZE + 1] = {0};
    clear_readbuff(ReadData);

    for (int i = 0; i < MAX_DATA_CHUNK_SIZE; i++) {

        ReadData[i] = UART_GetReceivedWord(&UART_0);

#if EN_SERIAL
        UART_Transmit(&UART_0, &ReadData[i], 1);
#endif


        if (i > 0 && ReadData[i] == '\n' && ReadData[i - 1] == '\n') {
            break;
        }
    }


    Delay(5);

    return ReadData;
}
