/*
 * CÉREBRO DE COMBATE - V2.8 UniAmérica (Precisão de Combate)
 *
 * ATUALIZAÇÃO FINAL (Calibração do Usuário):
 * - Velocidade máxima reduzida para 200 para maior precisão e controle,
 * conforme testes e observação.
 */

//----------------------------------------------------------------
// 1. CONFIGURAÇÕES E CALIBRAÇÃO
//----------------------------------------------------------------
#define VELOCIDADE_MAXIMA 175      // (AJUSTADO) Mais controle e precisão.
#define VELOCIDADE_GIRO 120     // (AJUSTADO) Para uma busca lenta e precisa.
#define DISTANCIA_ATAQUE 45        // Distância em cm para iniciar o ataque.
#define NUMERO_LEITURAS_PARA_ATACAR 3 // Quantas vezes precisa ver o inimigo para atacar.
#define TEMPO_RECUO_EVASAO 550     // Em ms, tempo que ele recua ao ver a borda.
#define TEMPO_GIRO_EVASAO 500      // Em ms, tempo que ele vira após recuar.

//----------------------------------------------------------------
// 2. MAPEAMENTO DE PINOS
//----------------------------------------------------------------
const int pinoENA = 9; const int pinoIN1 = 2; const int pinoIN2 = 3;
const int pinoENB = 10; const int pinoIN3 = 4; const int pinoIN4 = 5;
const int pinoTrig = 7; const int pinoEcho = 8;
const int pinoIRFrontal = 11;
const int pinoIRTraseiroEsquerdo = 12;
const int pinoIRTraseiroDireito = 6;

//----------------------------------------------------------------
// 3. VARIÁVEIS GLOBAIS E MÁQUINA DE ESTADOS
//----------------------------------------------------------------
enum EstadoRobo { PARADO, PROCURANDO, ATACANDO, EVADINDO_FRENTE, EVADINDO_ATRAS };
EstadoRobo estadoAtual = PARADO;
unsigned long tempoInicioEstado = 0;
int leiturasAtaqueConsecutivas = 0;

//----------------------------------------------------------------
// 4. SETUP
//----------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(pinoENA, OUTPUT); pinMode(pinoIN1, OUTPUT); pinMode(pinoIN2, OUTPUT);
  pinMode(pinoENB, OUTPUT); pinMode(pinoIN3, OUTPUT); pinMode(pinoIN4, OUTPUT);
  pinMode(pinoTrig, OUTPUT); pinMode(pinoEcho, INPUT);
  pinMode(pinoIRFrontal, INPUT_PULLUP);
  pinMode(pinoIRTraseiroEsquerdo, INPUT_PULLUP);
  pinMode(pinoIRTraseiroDireito, INPUT_PULLUP);
  
  parar();
  delay(3000); // Pausa regulamentar de 3 segundos
  estadoAtual = PROCURANDO;
}

//----------------------------------------------------------------
// 5. FUNÇÕES DE MOVIMENTO
//----------------------------------------------------------------
void mover(int velEsq, int velDir) {
  if (velEsq > 0) { digitalWrite(pinoIN1, HIGH); digitalWrite(pinoIN2, LOW); }
  else { digitalWrite(pinoIN1, LOW); digitalWrite(pinoIN2, HIGH); }
  analogWrite(pinoENA, min(abs(velEsq), VELOCIDADE_MAXIMA));

  if (velDir > 0) { digitalWrite(pinoIN3, HIGH); digitalWrite(pinoIN4, LOW); }
  else { digitalWrite(pinoIN3, LOW); digitalWrite(pinoIN4, HIGH); }
  analogWrite(pinoENB, min(abs(velDir), VELOCIDADE_MAXIMA));
}
void parar() { mover(0, 0); }

//----------------------------------------------------------------
// 6. FUNÇÃO DE LEITURA DE SENSOR
//----------------------------------------------------------------
int lerDistancia() {
  digitalWrite(pinoTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);
  long duracao = pulseIn(pinoEcho, HIGH, 25000);
  return duracao * 0.034 / 2;
}

//----------------------------------------------------------------
// 7. LOOP PRINCIPAL
//----------------------------------------------------------------
void loop() {
  if (estadoAtual == PARADO) return;

  int dist = lerDistancia();
  bool veLinhaFrente = (digitalRead(pinoIRFrontal) == LOW);
  bool veLinhaAtrasEsq = (digitalRead(pinoIRTraseiroEsquerdo) == LOW);
  bool veLinhaAtrasDir = (digitalRead(pinoIRTraseiroDireito) == LOW);

  // --- Lógica de Transição de Estados ---
  if (veLinhaFrente) {
    estadoAtual = EVADINDO_FRENTE;
    tempoInicioEstado = millis();
    leiturasAtaqueConsecutivas = 0;
  } 
  else if (veLinhaAtrasEsq || veLinhaAtrasDir) {
    estadoAtual = EVADINDO_ATRAS;
    tempoInicioEstado = millis();
    leiturasAtaqueConsecutivas = 0;
  } 
  else if (dist > 0 && dist < DISTANCIA_ATAQUE) {
    leiturasAtaqueConsecutivas++;
    if (leiturasAtaqueConsecutivas >= NUMERO_LEITURAS_PARA_ATACAR) {
      estadoAtual = ATACANDO;
    }
  } else {
    leiturasAtaqueConsecutivas = 0;
    if (estadoAtual != EVADINDO_FRENTE && estadoAtual != EVADINDO_ATRAS) {
      estadoAtual = PROCURANDO;
    }
  }

  // --- Execução do Estado Atual ---
  switch (estadoAtual) {
    case PROCURANDO:
      mover(-VELOCIDADE_GIRO, VELOCIDADE_GIRO);
      break;

    case ATACANDO:
      mover(VELOCIDADE_MAXIMA, VELOCIDADE_MAXIMA);
      break;

    case EVADINDO_FRENTE:
      if (millis() - tempoInicioEstado < TEMPO_RECUO_EVASAO) {
        mover(-VELOCIDADE_MAXIMA, -VELOCIDADE_MAXIMA);
      } else if (millis() - tempoInicioEstado < TEMPO_RECUO_EVASAO + TEMPO_GIRO_EVASAO) {
        mover(VELOCIDADE_MAXIMA, -VELOCIDADE_MAXIMA);
      } else {
        estadoAtual = PROCURANDO;
      }
      break;

    case EVADINDO_ATRAS:
      if (millis() - tempoInicioEstado < TEMPO_RECUO_EVASAO) {
        mover(VELOCIDADE_MAXIMA, VELOCIDADE_MAXIMA);
      } else {
        estadoAtual = PROCURANDO;
      }
      break;
  }
}
