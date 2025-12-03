# Pasta `drivers/`

A pasta `drivers/` contém implementações **dependentes do hardware**.

## Propósito

- Código acoplado ao microcontrolador (ESP32, STM32 etc.).
- Manipulação de periféricos:
  - I2C
  - SPI
  - UART
  - Timers
  - ADC/DAC

## Funções típicas

- `driver_i2c.*` — inicialização e leitura bruta de sensores.
- `driver_spi.*` — comunicação SPI.
- `driver_uart.*` — envio/recebimento serial.

Esta camada **não** deve conter lógica de aplicação.
