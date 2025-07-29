
# Sacibô - Robô Sumô Campeão

  

## 🏆 Sobre o Projeto

**Sacibô** é um robô de sumô autônomo desenvolvido por alunos do 1º Período do curso de [ANALISE E DESSENVOLVIMENTO DE SISTEMAS] para a competição interna de calouros da **Uniamérica Descomplica**.

Este projeto sagrou-se **campeão** no Festival de Inovação de 2025, demonstrando um design robusto, uma programação eficiente e uma estratégia de combate superior. O robô foi projetado para detectar e empurrar o oponente para fora da arena (dohyō), enquanto se mantém dentro dos limites demarcados.

## 🛠️ Hardware Utilizado

A construção do Sacibô foi realizada com os seguintes componentes:

| Componente | Especificação | Descrição |
| :--- | :--- | :--- |
| **Microcontrolador** | Arduino Uno | O cérebro do robô, responsável por processar os sensores e controlar os motores. |
| **Motores** | Motores DC N20 com caixa de redução | Fornecem o torque e a velocidade necessários para o combate. |
| **Driver de Motor** | L298N | Ponte H que permite o controle de direção e velocidade dos motores DC. |
| **Sensores de Distância**| Sensores Ultrassônicos HC-SR04 | Utilizados para detectar a presença e a distância do robô oponente. |
| **Sensores de Linha** | Sensores Infravermelhos TCRT5000 | Utilizados para detectar a borda branca da arena e evitar a desclassificação. |
| **Alimentação** | Bateria LiPo/Li-Ion | Fornece a energia para todo o sistema eletrônico.  |
| **Estrutura** | Chassi em Acrílico/MDF | Estrutura física que abriga e protege todos os componentes do robô. |
| **Placa de Circuito** | Placa de Circuito Impresso (PCB) | (Opcional) Placa personalizada para organizar e otimizar as conexões. |

## 💻 Software e Linguagens

O código do Sacibô foi desenvolvido utilizando as seguintes tecnologias:

  * **Linguagem:** C++ (padrão do ecossistema Arduino)
  * **IDE:** Arduino IDE
 

## 🔌 Montagem e Conexões

Para que o robô funcione corretamente, conecte os componentes conforme o diagrama e as instruções abaixo.

```
Diagrama de Conexões (Exemplo):

      +-----------------+      +-----------------+
      |    Arduino      |      |   Driver L298N  |
      |                 |      |                 |
      |   Pino Digital X|----->| IN1             |
      |   Pino Digital Y|----->| IN2             |
      |             ... |      | ...             |
      |                 |      |                 |
      |   Pino Z (Trig) |----->| HC-SR04 Trig    |
      |   Pino W (Echo) |<-----| HC-SR04 Echo    |
      |                 |      |                 |
      |   Pino A0       |<-----| TCRT5000 (Esq)  |
      |   Pino A1       |<-----| TCRT5000 (Meio) |
      |   Pino A2       |<-----| TCRT5000 (Dir)  |
      +-----------------+      +-------+---------+
                                       |
                               +-------+---------+
                               |     Bateria     |
                               +-----------------+
```

  * **Motores:** Conectados às saídas do driver de motor. O driver, por sua vez, está conectado aos pinos digitais **X** e **Y** do Arduino para controle.
  * **Sensores Ultrassônicos:** O pino `Trigger (Trig)` do sensor deve ser conectado ao pino **Z** do Arduino, e o pino `Echo` ao pino **W**.
  * **Sensores Infravermelhos:** Conecte os pinos de saída dos sensores às portas analógicas **A0**, **A1** e **A2** para ler as variações na reflexão da luz.
  * **Bateria:** Conecte a saída da bateria à entrada de alimentação do driver de motor e ao pino `Vin` do Arduino (utilize um regulador de tensão, se necessário, para não danificar a placa).

## 🚀 Status do Projeto

Este projeto foi desenvolvido como um requisito acadêmico para a disciplina de [ANALISE E DESENVOLVIMENTO DE SISTEMAS] e está concluído em sua versão para a competição.

## 🤝 Como Contribuir

Contribuições externas são muito bem-vindas\! Se você tem ideias para melhorias, otimizações de código ou encontrou algum bug, sinta-se à vontade para:

1.  **Abrir uma [Issue](https://www.google.com/search?q=https://github.com/VitorCassel/SaciBo/issues):** Para relatar um bug detalhadamente ou para sugerir uma nova funcionalidade.
2.  **Fazer um [Pull Request](https://www.google.com/search?q=https://github.com/VitorCassel/SaciBo/issues)):** Com suas próprias correções e melhorias.

-----

