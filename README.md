
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

Date : 24/06/2024
1. is_drive_mode flag added to check whether vehicle is in drive mode (ign 1) or not.
2. Publish 10 second packet only when is_drive_mode == true.
3. Testing on VP05, VP06 and VP10 (with Diksha).
4. SOC mapping removed from VP05.
5. SOC mapping added in VP06, VP10.

Date : 25/06/2024
1. DC to DC converter charging logic updated (commented).
2. Needs testing on VP07 and other vehicles (48V battery connection is only done for VP07).
3. ADC2, ADC3 testing.

Date : 26/06/2024
1. DC to DC converter charging logic still commented.
2. New CPIS (0x8000100 500kbps) changes added needs testing.
3. ADC2, ADC3 testing.

Date : 27/06/2024
1. New CPIS (0x8000100 500kbps) tested.
2. ADC2, ADC3 testing (SPI0 clock settings conflict with SD card).

Date : 28/06/2024
1. Gradually increase/decrease compressor RPM until matches desired RPM based on temperature received from CPIS rotor.
2. New compressor logic where no rotor will be there and compressor RPM will be dependent on cabin temperature. Logic commented.  
3. Cabin temperature new formula added needs testing.