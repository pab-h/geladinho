# Pasta `hal/` — Hardware Abstraction Layer

A HAL é uma camada intermediária entre as tasks e os drivers de hardware.

## Propósito

- Fornecer **funções de alto nível e portáveis**.
- Esconder detalhes específicos de registradores / APIs do MCU.
- Permitir trocar o hardware ou driver sem alterar tasks.

## Exemplo

  - `hal_sensor.*`
  - `initSensor()`
  - `readSensor()`

As tasks nunca devem falar diretamente com I2C/SPI/UART — apenas com HAL.
