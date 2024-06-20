
Changelog -

Date : 17/06/2024
Search for //hifire in the code to find the changes that are done.
1. Hifire compressor CAN ids added 0x8000530 (Tx index = 9), 0x8000250 (Rx index = 8).
2. Previous compressor ids removed.
3. Needs testing.

Date : 18/06/2024
1. Tested on VP10 (with Lokesh, Ankit), having Hifire compressor and IRP MCU.
2. BMS SOC mapping removed by Suchit (can_matrix_cluster.c line no. 128, 129).
3. Uploaded on VP05 and VP09.
4. VP05 - Speedometer and Power Dial not getting updated.

Date : 19/06/2024
1. Tested on VP05 again (Devendra), working alright.

Date : 20/06/2024
1. Added battery 12V monitor for DC to DC converter
2. AUX_EFUSE3 output pin is connected to 48V battery input.
