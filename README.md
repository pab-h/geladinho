# ❄️ Projeto Geladinho

**Sistema Embarcado de Resfriamento de Líquido Controlado com ESP32**

O **Geladinho** é um projeto de firmware para controle preciso de temperatura de líquidos. O sistema utiliza um módulo Peltier para resfriamento, tudo gerenciado por um ESP32 rodando **FreeRTOS** com uma arquitetura em camadas (HAL, Tasks, Application).

---

## 🚀 Funcionalidades

- **Monitoramento de Temperatura:** Leitura contínua via termistor NTC (ou simulação via LDR).
- **Controle de Resfriamento:** Atuação sobre pastilha Peltier (futuro: controle PID/ON-OFF).
- **Agitação:** Controle de motor para movimentação do líquido.
- **Interface:** Feedback visual via LCD e sonoro via Buzzer.
- **Multitarefa Real-Time:** Arquitetura baseada em FreeRTOS para não-bloqueio.

---

## 🛠️ Hardware

- **MCU:** ESP32 (DevKit V1 / Upesy Wroom)
- **Sensor:** Termistor NTC 10k (Beta 3380)
- **Atuador Térmico:** Pastilha Peltier (com Driver/Relé)
- **Agitador:** Motor DC
- **Display:** Oled

---

## 🏗️ Arquitetura de Software

O projeto segue o princípio de **separação de responsabilidades**:

```text
├── src/
│   ├── app/           # Lógica de Negócio e Estado Global (State Machine)
│   ├── hal/           # Hardware Abstraction Layer (Drivers diretos do ESP32)
│   ├── tasks/         # Tarefas do FreeRTOS (Loops infinitos)
│   ├── freertos/      # Configurações do SO
│   └── main.cpp       # Entry point (Setup do Hardware e Tasks)
└── lib/               # Bibliotecas auxiliares
```

## 👥 Autores

Este projeto foi desenvolvido com a colaboração de:

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/Miguel-Edson">
        <img src="https://github.com/Miguel-Edson.png" width="100px;" alt=""/>
        <br />
        <sub><b>Miguel Edson</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/pab-h">
        <img src="https://github.com/pab-h.png" width="100px;" alt=""/>
        <br />
        <sub><b>pab-h</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/RyamLael">
        <img src="https://github.com/RyamLael.png" width="100px;" alt=""/>
        <br />
        <sub><b>RyamLael</b></sub>
      </a>
    </td>
  </tr>
</table>

---
