# Pasta `tasks/`

A pasta `tasks/` contém **todas as tasks FreeRTOS**, cada uma isolada em seu próprio módulo.

## Propósito

- Separar claramente o comportamento concorrente do sistema.
- Facilitar debug e testes unitários.
- Permitir escalabilidade, adicionando tasks sem quebrar outras partes.

## Estrutura típica

- `task_sensor.*` — lê dados do HAL e envia para filas.
- `task_comm.*` — comunicação externa (Serial, MQTT, WiFi, etc.).
- `task_control.*` — lógica de controle, atuadores, PID, etc.

## Boas práticas

- Cada task deve ter:
  - Seu `.cpp` e `.hpp`.
  - Depender apenas de HAL e utils.
  - Usar filas/semáforos, nunca chamar outra task diretamente.

Task = unidade lógica independente.
