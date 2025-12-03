# Pasta `utils/`

Contém **código utilitário** e independente de hardware ou lógica de aplicação.

## Propósito

- Reutilização entre vários módulos.
- Manter o código organizado, evitando “bagunça” dentro das tasks.

## Exemplos comuns

- `logger.*` — logs e debug.
- `ring_buffer.*` — buffers circulares.
- `crc.*` — funções de cálculo.
- `timing.*` — utilitários de tempo.

Regra geral: se não é task, não é HAL, não é driver → é utilitário.
