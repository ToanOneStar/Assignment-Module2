#ifndef MODBUS_BUILDER_H
#define MODBUS_BUILDER_H

/*define types of modbus function code*/
#define FUNC_READ_COIL  01
#define FUNC_READ_INPUT 02

typedef struct {
    int slaveAddress;
    int functionCode;
    int startAddress;
    int numberBitsRead;
} MODBUS_ReadRequestFunction_Config_t;

/*MODBUS Builder Structure*/
typedef struct MODBUS_Builder {
    MODBUS_ReadRequestFunction_Config_t config;
    struct MODBUS_Builder* (*setSlaveAddress)(struct MODBUS_Builder*, int);
    struct MODBUS_Builder* (*setFunctionCode)(struct MODBUS_Builder*, int);
    struct MODBUS_Builder* (*setStartAddress)(struct MODBUS_Builder*, int, int);
    struct MODBUS_Builder* (*setNumberBitsRead)(struct MODBUS_Builder*, int);
    MODBUS_ReadRequestFunction_Config_t (*build)(struct MODBUS_Builder*);
} MODBUS_Builder;

// Function to initialize the Builder
MODBUS_Builder MODBUS_Builder_Init();

#endif