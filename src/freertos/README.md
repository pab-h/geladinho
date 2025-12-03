# Pasta `freertos/`

Contém **lógica específica do FreeRTOS**, compartilhada entre tasks e sistema.

## Propósito

- Manter consistência entre configurações de tasks.
- Implementar hooks globais do FreeRTOS.
- Armazenar handles, filas, semáforos e configurações comuns.

## Arquivos típicos

- `tasks_common.hpp`
  - Prioridades
  - Tamanhos de stacks
  - Filas globais (`extern QueueHandle_t`)

- `freertos_hooks.cpp`
  - `vApplicationIdleHook`
  - `vApplicationStackOverflowHook`
  - `vApplicationMallocFailedHook`

## Opcional

- `static_alloc.cpp` para uso de `xTaskCreateStatic`.
