# 🌐 SafeZone IoT – Monitoramento de Riscos com ESP32, DHT22, MPU6050 e LED

Este projeto é parte da iniciativa **SafeZone**, uma plataforma de apoio em situações de emergência.  
Nesta etapa IoT, utilizamos sensores simulados no **Wokwi** para coletar dados ambientais e enviar a um canal **ThingSpeak** em tempo real.

---

## 🔧 Componentes utilizados

- ESP32 DevKit v1 (Wokwi)
- Sensor de temperatura/umidade **DHT22**
- Sensor de aceleração **MPU6050**
- LED de alerta (acende quando a temperatura ultrapassa 30°C)
- Conexão Wi-Fi (simulada via Wokwi)
- Canal de monitoramento na nuvem via **ThingSpeak**

---

## 🧪 Sensores e Dados Coletados

| Field | Nome no ThingSpeak        | Origem          | Unidade           |
|-------|---------------------------|------------------|-------------------|
| 1     | Temperatura               | DHT22            | °C                |
| 2     | Umidade                   | DHT22            | %                 |
| 3     | DX                        | MPU6050 (Eixo X) | aceleração bruta  |
| 4     | DY                        | MPU6050 (Eixo Y) | aceleração bruta  |
| 5     | DZ                        | MPU6050 (Eixo Z) | aceleração bruta  |
| 6     | Acima de 30ºC             | LED              | 1 (ligado) / 0 (desligado) |

---

## 🚀 Como rodar no Wokwi

1. Acesse o Wokwi: [https://wokwi.com](https://wokwi.com)
2. Clone ou importe o projeto com o circuito configurado (incluindo DHT22, MPU6050 e LED): [Project SafeZone Sensors Template - Wokwi](https://wokwi.com/projects/433056821173481473)
3. Substitua a linha no código:

   `const String writeAPIKey = "YOUR_THINGSPEAK_WRITE_API_KEY";`

   ...pela sua **Write API Key** do ThingSpeak.

4. Clique em **Start Simulation**
5. Para modificar os valores dos sensores:
   - Clique sobre o **DHT22** e ajuste a temperatura ou umidade
   - Clique sobre o **MPU6050** e altere os eixos X, Y e Z
6. Os dados são enviados automaticamente a cada **15 segundos** para o canal ThingSpeak

---

## 🌐 Como configurar o canal no ThingSpeak

1. Acesse [https://thingspeak.com](https://thingspeak.com) e crie uma conta gratuita
2. Vá em **Channels > New Channel**
3. Ative os campos de 1 a 6 com os seguintes nomes:

   - Field 1: **Temperatura**
   - Field 2: **Umidade**
   - Field 3: **DX**
   - Field 4: **DY**
   - Field 5: **DZ**
   - Field 6: **Acima de 30ºC**

4. Clique em **Save Channel**
5. Vá em **API Keys** e copie a **Write API Key**
6. Insira a chave no seu código no lugar indicado

---

## 💡 Observações

- O LED é ativado automaticamente quando a **temperatura > 30°C**
- Os dados são enviados via **HTTP GET** para o ThingSpeak
- A taxa de envio padrão do ThingSpeak é de **1 atualização a cada 15 segundos**
- Você pode simular condições de risco alterando os sensores em tempo real no Wokwi

---

## 📸 Exemplo de circuito no Wokwi

> ![image](https://github.com/user-attachments/assets/69246748-d83b-4d55-ba85-75733d8ede84)

---

## 📊 Exemplo de gráfico no ThingSpeak

> ![image](https://github.com/user-attachments/assets/59a2a8d4-bff9-49af-b43c-696b6c905608)

---

## 👥 Autores

- Ellie de Oliveira - RM552824
- Ives Jundi Chiba - RM553243
- Nathalia Comeron Freire - RM553233

---

## 🛠️ Tecnologias usadas

- [x] Wokwi (simulador de circuitos)
- [x] C++ para ESP32
- [x] ThingSpeak API
- [x] Sensor DHT22
- [x] Sensor MPU6050
- [x] WiFi + HTTPClient

---

## ✅ Status

✅ Projeto funcional no Wokwi  
✅ Dados chegando corretamente no ThingSpeak  
✅ LED reagindo à temperatura  

---
