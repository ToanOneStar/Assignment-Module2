#include <stdio.h>
#include "uart-builder.h"

int main() {
    UART_Builder builder = UART_Builder_Init();

    UART_Config_t uartConfig = builder.setBaudRate(&builder, BAUDRATE_115200)
                                   ->setParity(&builder, ODD)
                                   ->setStopBits(&builder, 2)
                                   ->setDataBits(&builder, 9)
                                   ->build(&builder);

    printf("UART Configuration:\n");
    printf("Baud Rate: %d\n", uartConfig.baudRate);
    printf("Parity: %d\n", uartConfig.parity);
    printf("Stop Bits: %d\n", uartConfig.stopBits);
    printf("Data Bits: %d\n", uartConfig.dataBits);

    return 0;
}