#include <WiFi.h>
#include <WebServer.h>

// ================= WIFI (ESP32 ACCESS POINT) =================
const char* ssid = "smart farm automation";
const char* password = "1234567890";

WebServer server(80);

// ================= PINS =================
#define SOIL_PIN 4
#define WATER_PIN 5
#define SMOKE_PIN 6   // your requested pin

// ================= GRAPH STORAGE =================
#define MAX_POINTS 60

int soilData[MAX_POINTS];
int waterData[MAX_POINTS];
int pos = 0;

void addData(int soil, int water) {
  soilData[pos] = soil;
  waterData[pos] = water;
  pos = (pos + 1) % MAX_POINTS;
}

// ================= SENSOR API =================
void handleData() {

  int soil = analogRead(SOIL_PIN);
  int water = analogRead(WATER_PIN);
  int smoke = digitalRead(SMOKE_PIN);

  addData(soil, water);

  String json = "{";
  json += "\"soil\":" + String(soil) + ",";
  json += "\"water\":" + String(water) + ",";
  json += "\"smoke\":" + String(smoke);
  json += "}";

  server.send(200, "application/json", json);
}

// ================= WEB DASHBOARD =================
void handleRoot() {

  String page = R"rawliteral(

<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Smart Farm automation system</title>
</head>

<body style="font-family:Arial;text-align:center;">

<h2>🌱 Smart Farm Dashboard</h2>

<button onclick="document.getElementById('alarm').play()">
Enable Alerts (tap once)
</button>

<br><br>

<!-- SOIL GRAPH -->
<canvas id="soilGraph" width="320" height="150" style="border:1px solid black;"></canvas>
<h3 id="soilText">Soil Loading...</h3>

<!-- WATER LEVEL -->
<h3>💧 Water Level</h3>
<div style="width:300px;height:25px;border:1px solid black;margin:auto;">
  <div id="waterBar" style="height:100%;width:0%;background:blue;"></div>
</div>
<h4 id="waterText"></h4>

<!-- SMOKE -->
<h2 id="smokeText">🚨 Smoke: Loading...</h2>

<!-- SOUND -->
<audio id="alarm">
  <source src="https://actions.google.com/sounds/v1/alarms/alarm_clock.ogg" type="audio/ogg">
</audio>

<script>

let soil = [];
let water = [];
let alarmPlayed = false;

// DRAW SOIL GRAPH (LINE GRAPH)
function drawSoil(){
  let c = document.getElementById("soilGraph");
  let ctx = c.getContext("2d");

  ctx.clearRect(0,0,320,150);

  ctx.beginPath();

  for(let i=0;i<soil.length;i++){
    let x = (i/60)*320;
    let y = 150 - (soil[i]/4095)*150;
    ctx.lineTo(x,y);
  }

  ctx.strokeStyle = "green";
  ctx.stroke();
}

// UPDATE DATA FROM ESP
function update(){

  fetch('/data')
  .then(res => res.json())
  .then(d => {

    // 🌱 SOIL
    document.getElementById("soilText").innerHTML = "Soil: " + d.soil;

    soil.push(d.soil);
    if(soil.length > 60) soil.shift();
    drawSoil();

    // 💧 WATER LEVEL (BAR)
    let percent = Math.round((d.water / 4095) * 100);
    document.getElementById("waterBar").style.width = percent + "%";
    document.getElementById("waterText").innerHTML = percent + "% full";

    // 🚨 SMOKE ALERT
    if(d.smoke == 1){
      document.getElementById("smokeText").innerHTML = "🚨 SMOKE DETECTED!";
      document.getElementById("smokeText").style.color = "red";

      if(!alarmPlayed){
        document.getElementById("alarm").play();
        alarmPlayed = true;
      }

    } else {
      document.getElementById("smokeText").innerHTML = "✅ Air Safe";
      document.getElementById("smokeText").style.color = "green";
      alarmPlayed = false;
    }

  });

}

setInterval(update, 1000);

</script>

</body>
</html>

)rawliteral";

  server.send(200, "text/html", page);
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  pinMode(SMOKE_PIN, INPUT);

  WiFi.softAP(ssid, password);

  Serial.println("ESP32 AP Started");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
}

// ================= LOOP =================
void loop() {
  server.handleClient();
}