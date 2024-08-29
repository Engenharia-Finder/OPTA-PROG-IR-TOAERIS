#include <ArduinoModbus.h>
#include <ArduinoRS485.h>

constexpr auto baudrate { 38400 };
constexpr auto btime { 1.0f / baudrate };
constexpr auto predl { btime * 9.6f * 3.5f * 1e6 };
constexpr auto postdl { btime * 9.6f * 3.5f * 1e6 };

void setup() {
  Serial.begin(115200);
  delay(2000);
  RS485.setDelays(predl, postdl);
  if (!ModbusRTUClient.begin(baudrate, SERIAL_8N2)) {
    Serial.println("Erro Modbus");
    while (1);
  }
  Serial.println("Sistema pronto. Envie comandos no formato: <registro> <valor>");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    processCommand(input);
  }

  // Exemplo de leitura de dados
  //float p = readdata(0x21, 0X09BA);
  //float v = readdata(0x21, 0X09C4);
  //float i = readdata(0x21, 0X09D4);

  //Serial.println(String(p, 1) + "W " + String(v, 1) + "V " + String(i, 3) + "A ");
  //delay(3000);
}

void processCommand(String input) {
  input.trim();
  if (input.length() == 0) return;

  int spaceIndex = input.indexOf(' ');
  if (spaceIndex == -1) {
    Serial.println("Formato inválido. Use: <registro> <valor>");
    return;
  }

  String regStr = input.substring(0, spaceIndex);
  String valueStr = input.substring(spaceIndex + 1);

  int reg = regStr.toInt();
  int value = valueStr.toInt();

  if (writeData(0x1, reg, value)) {
    Serial.print("Comando enviado com sucesso para o registrador ");
    Serial.println(reg);
  } else {
    Serial.print("Erro ao enviar comando para o registrador ");
    Serial.println(reg);
  }
}


bool writeData(int addr, int reg, int value) {
  if (!ModbusRTUClient.holdingRegisterWrite(addr, reg, value)) {
    Serial.println("Erro ao enviar comando. Código de erro: " + String(ModbusRTUClient.lastError()));
    return false;
  }
  return true;
}
