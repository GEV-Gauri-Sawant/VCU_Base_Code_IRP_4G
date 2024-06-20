
#define BUFFER_SIZE 100 // Define the buffer size according to your requirements
#define PACKET_SIZE 256
#define NUM_PACKETS 1
#include "DAVE.h"
#include "sd_card.h"

FATFS fs;  //File system object (volume work area)
FIL fil;  //File object
FRESULT res;

char uart_tx_buffer[BUFFER_SIZE];

void int_to_hex(uint32_t value, char *buffer) {
    int i;
    for (i = 7; i >= 0; i--) {
        buffer[i] = "0123456789ABCDEF"[value & 0xF];
        value >>= 4;
    }
}

void uart_send_string(const char *str, uint32_t length) {
    UART_Transmit(&UART_0, str, length);
}

void transmit_cid_over_uart(const SDMMC_BLOCK_CID_t *cid) {
    int_to_hex(cid->manufacturing_date, uart_tx_buffer);
    uart_send_string(uart_tx_buffer, 8);

    int_to_hex(cid->product_serial_num, uart_tx_buffer);
    uart_send_string(uart_tx_buffer, 8);

    int_to_hex(cid->product_rev, uart_tx_buffer);
    uart_send_string(uart_tx_buffer, 2);

    uart_send_string((char *)cid->product_name, 5);

    uart_send_string("\r\n", 2);
}

void initialize_sd_card_and_transmit_cid(void) {
    DAVE_STATUS_t status;
    SDMMC_BLOCK_STATUS_t sdmmc_status;
    SDMMC_BLOCK_CID_t cid;
    sdmmc_status = SDMMC_BLOCK_Initialize(&SDMMC_BLOCK_0);

    if (sdmmc_status != SDMMC_BLOCK_STATUS_SUCCESS) {
    }

    sdmmc_status = SDMMC_BLOCK_Ioctl(&SDMMC_BLOCK_0, SDMMC_BLOCK_MMC_GET_CID, &cid);

    if (sdmmc_status == SDMMC_BLOCK_STATUS_SUCCESS) {
        transmit_cid_over_uart(&cid);
        res = f_mount(&fs, "0:", 1);
            if (res == FR_OK) {
                UART_Transmit(&UART_0, "File system mounted\n", strlen("File system mounted\n"));

                // Check free space
                FATFS *fsp;
                DWORD fre_clust, fre_sect, tot_sect;
                fsp = &fs;
                res = f_getfree("", &fre_clust, &fsp);
                if (res == FR_OK) {
                    // Get total sectors and multiply by sector size
                    tot_sect = (fsp->n_fatent - 2) * fsp->csize;
                    UART_Transmit(&UART_0, "Free space (KB): ", strlen("Free space (KB): "));
                    UART_Transmit_Integer(&UART_0, (fre_clust * fsp->csize) / 2);
                    UART_Transmit(&UART_0, "\n", strlen("\n"));

                    UART_Transmit(&UART_0, "Total space (KB): ", strlen("Total space (KB): "));
                    UART_Transmit_Integer(&UART_0, (tot_sect) / 2);
                    UART_Transmit(&UART_0, "\n", strlen("\n"));
    } else {
        uart_send_string("Failed to retrieve CID\r\n", strlen("Failed to retrieve CID\r\n"));
    }

}
}
}


void writePacketsToFile(const char *filename, const char *packetBuffer, size_t bufferSize) {
    FIL file;
    FRESULT res;
    UINT bytesWritten;

    // Open the file for appending
    res = f_open(&file, filename, FA_OPEN_APPEND | FA_WRITE);
    if (res != FR_OK) {
        UART_Transmit(&UART_0, "Error opening file for writing.\n", strlen("Error opening file for writing.\n"));
        return;
    }

    // Write packets to the file
    for (int i = 0; i < NUM_PACKETS; i++) {
        // Write start of packet
        char startPacket[50];
        snprintf(startPacket, sizeof(startPacket), "Start %d\n", i + 1);
        res = f_write(&file, startPacket, strlen(startPacket), &bytesWritten);
        if (res != FR_OK) {
            UART_Transmit(&UART_0, "Error writing start of packet.\n", strlen("Error writing start of packet.\n"));
            f_close(&file);
            return;
        }

        // Write packet buffer
        if (bufferSize <= PACKET_SIZE) {
            res = f_write(&file, packetBuffer, bufferSize, &bytesWritten);
            if (res != FR_OK) {
                UART_Transmit(&UART_0, "Error writing packet data.\n", strlen("Error writing packet data.\n"));
                f_close(&file);
                return;
            }
        } else {
            UART_Transmit(&UART_0, "Packet size exceeds the maximum packet size. Skipping writing.\n", strlen("Packet size exceeds the maximum packet size. Skipping writing.\n"));
        }

        // Write end of packet
        char endPacket[50];
        snprintf(endPacket, sizeof(endPacket), "\nEnd %d\n\n", i + 1);
        res = f_write(&file, endPacket, strlen(endPacket), &bytesWritten);
        if (res != FR_OK) {
            UART_Transmit(&UART_0, "Error writing end of packet.\n", strlen("Error writing end of packet.\n"));
            f_close(&file);
            return;
        }
    }

    // Close the file
    res = f_close(&file);
    if (res != FR_OK) {
        UART_Transmit(&UART_0, "Error closing file.\n", strlen("Error closing file.\n"));
        return;
    }

    UART_Transmit(&UART_0, "Packets written to file successfully.\n", strlen("Packets written to file successfully.\n"));
}

void UART_Transmit_Integer(const UART_t *const handle, int value) {
    char buffer[20]; // Assuming a maximum of 20 digits for an integer
    sprintf(buffer, "%d", value); // Convert integer to string
    UART_Transmit(&UART_0, buffer, strlen(buffer)); // Transmit the string via UART
}
