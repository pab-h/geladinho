# Pasta `app/`

A pasta `app/` contém o código responsável pela **orquestração** do firmware.

## Propósito

- Coordenar a inicialização do sistema.
- Inicializar drivers, HAL, filas, semáforos e recursos FreeRTOS.
- Criar e iniciar as tasks do sistema.
- Representar a lógica de alto nível (“aplicação”) acima das camadas de hardware.

## Arquivos típicos

- **app_init.cpp / app_init.hpp** — funções:
  - `initHardware()` — configura GPIOs, inicializa periféricos.
  - `initSystem()` — cria filas, mutexes, timers etc.
  - `startTasks()` — cria todas as tasks FreeRTOS.

Esta camada *não contém lógica de hardware direto*: ela coordena o sistema.
