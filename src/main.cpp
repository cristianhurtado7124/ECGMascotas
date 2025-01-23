#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Create an AsyncWebServer object on port 80
AsyncWebServer server(80);

// Define the HTML for the page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Button Page</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      margin-top: 50px;
      background-color: #f4f4f9;
    }

    h1 {
      color: #333;
      font-size: 2.5em;
      margin-bottom: 20px;
    }

    button {
      padding: 15px 30px;
      margin: 10px;
      font-size: 18px;
      cursor: pointer;
      border: none;
      border-radius: 10px;
      background: linear-gradient(145deg, #6e7cfc, #4b57f5);
      color: white;
      box-shadow: 3px 3px 8px rgba(0, 0, 0, 0.2), -3px -3px 8px rgba(255, 255, 255, 0.5);
      transition: all 0.3s ease;
    }

    button:hover {
      background: linear-gradient(145deg, #4b57f5, #6e7cfc);
      transform: translateY(-3px);
      box-shadow: 5px 5px 12px rgba(0, 0, 0, 0.2), -5px -5px 12px rgba(255, 255, 255, 0.5);
    }

    button:active {
      transform: translateY(2px);
      box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.2), -2px -2px 5px rgba(255, 255, 255, 0.5);
    }
  </style>
</head>
<body>
  <h1>ESP32 Web Server</h1>
  <button onclick="fetch('/button1')">Button 1</button>
  <button onclick="fetch('/button2')">Button 2</button>
  <button onclick="fetch('/button3')">Button 3</button>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  const char* ssid = "ESP32-AP";
  const char* password = "123456789";

  // Set custom IP address (e.g., 192.168.4.2) and subnet mask
  IPAddress local_ip(192, 168, 4, 2);      // Custom IP address
  IPAddress gateway(192, 168, 4, 1);       // Gateway IP (usually the same as the ESP32's IP)
  IPAddress subnet(255, 255, 255, 0);      // Subnet mask

  WiFi.softAPConfig(local_ip, gateway, subnet);  // Set custom IP config
  WiFi.softAP(ssid, password);  // Start the Access Point
  Serial.println("Access Point Started");

  // Print the custom IP address of the ESP32 Access Point
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // This will print the custom IP address

  // Serve the HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  // Define actions for the buttons
  server.on("/button1", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Button 1 was pressed");
    request->send(200, "text/plain", "Button 1 Pressed");
  });

  server.on("/button2", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Button 2 was pressed");
    request->send(200, "text/plain", "Button 2 Pressed");
  });

  server.on("/button3", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Button 3 was pressed");
    request->send(200, "text/plain", "Button 3 Pressed");
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing needed here for this example
}
