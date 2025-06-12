#include <stdio.h>
#include <string.h>

#include "modbus/modbus_builder.c"

/* Define structure of a Modbus RTU frame */
#define NUMBER_BYTES_SLAVE_ADDRESS   1
#define NUMBER_BYTES_FUNCTION_CODE   1
#define NUMBER_BYTES_START_ADDRESS   2
#define NUMBER_BYTES_NUMBER_BIT_READ 2

#define SUM_BYTES_USED               15

char frameData[SUM_BYTES_USED] = "";

/*function convert int number to hexa string*/
void intToHex(int value, char* hexString, int numberChar) {
    if (numberChar * 2 == 2) {
        sprintf(hexString, "%02X", value);
    } else if (numberChar * 2 == 4) {
        sprintf(hexString, "%04X", value);
    }
}

void createFrameData(char* framedata, int slaveAddress, int functionCode, int startAddress, int numberBitsRead) {
    char hexString[5];
    for (int i = 1; i <= 4; ++i) {
        switch (i) {
            case 1:
                intToHex(slaveAddress, hexString, NUMBER_BYTES_SLAVE_ADDRESS);
                strcat(framedata, hexString);
                break;
            case 2:
                intToHex(functionCode, hexString, NUMBER_BYTES_FUNCTION_CODE);
                strcat(framedata, hexString);
                break;
            case 3:
                intToHex(startAddress, hexString, NUMBER_BYTES_START_ADDRESS);
                strcat(framedata, hexString);
                break;
            case 4:
                intToHex(numberBitsRead, hexString, NUMBER_BYTES_NUMBER_BIT_READ);
                strcat(framedata, hexString);
                break;
            default: break;
        }
        printf("Hex String for case %d: %s\n", i, hexString);
    }
}

int main() {
    // Initialize the Builder
    MODBUS_Builder builder = MODBUS_Builder_Init();

    // Configure Modbus read request function using the Builder
    MODBUS_ReadRequestFunction_Config_t modbusConfig = builder.setSlaveAddress(&builder, 2)
                                                           ->setFunctionCode(&builder, FUNC_READ_COIL)
                                                           ->setStartAddress(&builder, FUNC_READ_COIL, 40)
                                                           ->setNumberBitsRead(&builder, 10)
                                                           ->build(&builder);

    // Create the frame data
    createFrameData(frameData,
                    modbusConfig.slaveAddress,
                    modbusConfig.functionCode,
                    modbusConfig.startAddress,
                    modbusConfig.numberBitsRead);

    // Print the result
    printf("Request: %s\n", frameData);

    return 0;
}
