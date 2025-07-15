#include <stdio.h>
#include <stdlib.h>
#include "modbus_builder.h"

static MODBUS_Builder* setSlaveAddress(MODBUS_Builder* builder, int slaveAddress) {
    if (slaveAddress < 0 || slaveAddress > 20) {
        printf("Error: Invalid slaveAdress. Must be between 0 and 20.\n");
        return builder;
    }
    builder->config.slaveAddress = slaveAddress;
    return builder;
}

static MODBUS_Builder* setFunctionCode(MODBUS_Builder* builder, int functionCode) {
    if (functionCode != 1 && functionCode != 2) {
        printf("Error: Invalid function code. Must be 1 or 2.\n");
        return builder;
    }
    builder->config.functionCode = functionCode;
    return builder;
}

static MODBUS_Builder* setStartAddress(MODBUS_Builder* builder, int functionCode, int startAddress) {
    if (functionCode == 1 && (startAddress < 0 || startAddress > 9999)) {
        printf("Error: Invalid start address. Must be between 0 and 9999.\n");
        return builder;
    }
    if (functionCode == 2 && (startAddress < 10000 || startAddress > 19999)) {
        printf("Error: Invalid start address. Must be between 10000 and 19999.\n");
        return builder;
    }
    builder->config.startAddress = startAddress;
    return builder;
}

static MODBUS_Builder* setNumberBitsRead(MODBUS_Builder* builder, int numberBitsRead) {
    if (numberBitsRead < 0 || numberBitsRead > 10000) {
        printf("Error: Invalid number bits read. Must be between 0 and 10000.\n");
        return builder;
    }
    builder->config.numberBitsRead = numberBitsRead;
    return builder;
}

static MODBUS_ReadRequestFunction_Config_t build(MODBUS_Builder* builder) {
    return builder->config;
}

MODBUS_Builder MODBUS_Builder_Init() {
    MODBUS_Builder builder;
    
    builder.config.slaveAddress = 0;
    builder.config.functionCode = FUNC_READ_COIL;
    builder.config.startAddress = 0x00;
    builder.config.numberBitsRead = 1;

    builder.setSlaveAddress = setSlaveAddress;
    builder.setFunctionCode = setFunctionCode;
    builder.setStartAddress = setStartAddress;
    builder.setNumberBitsRead = setNumberBitsRead;
    builder.build = build;
    return builder;
}