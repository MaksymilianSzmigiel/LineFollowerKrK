#include <server.h>
#include <Arduino.h>
#include <WiFi.h>
#include <motor.h>

WiFiServer server(80);
Motor motor1;

void PrivateServer::initialize()
{
     Serial.begin(115200);
  
  pinMode(output16, OUTPUT);      // set the LED pin mode
  digitalWrite(output16, 0);      // turn LED off by default
  pinMode(output17, OUTPUT);      // set the LED pin mode
  digitalWrite(output17, 0);      // turn LED off by default

  WiFi.softAP(ssid,password);
  
  // Print IP address and start web server
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();

}

void PrivateServer::clients()
{
    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {                             // If a new client connects,
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New Client.");        // Print a message in the serial port
        String currentLine = "";              // Make a String to hold incoming data from the client

        while (client.connected() && currentTime - previousTime <= timeoutTime) {
            currentTime = millis();
            if (client.available()) {         // If there's bytes to read from the client,
                char c = client.read();       // Read a byte
                Serial.write(c);              // Print it out the serial monitor
                header += c;
                if (c == '\n') {              // If the byte is a newline character
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code and a content-type
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // Turn GPIOs on and off based on HTTP request
                        if (header.indexOf("GET /16/on") >= 0) {
                            statePin16 = "on";
                            digitalWrite(output16, HIGH); // Turn LED on
                        } else if (header.indexOf("GET /16/off") >= 0) {
                            statePin16 = "off";
                            digitalWrite(output16, LOW);  // Turn LED off
                        }

                        if (header.indexOf("GET /17/on") >= 0) {
                            statePin17 = "on";
                            digitalWrite(output17, HIGH); // Turn LED on
                        } else if (header.indexOf("GET /17/off") >= 0) {
                            statePin17 = "off";
                            digitalWrite(output17, LOW);  // Turn LED off
                        }

                        // Motor control via HTTP request
                        if (header.indexOf("GET /motor/start") >= 0) {
                            motor1.motorState = "on";
                            digitalWrite(motor1.AIN1, HIGH);     // Turn motor on
                            digitalWrite(motor1.BIN1, HIGH);
                        } else if (header.indexOf("GET /motor/stop") >= 0) {
                            motor1.motorState = "off";
                            digitalWrite(motor1.AIN1, LOW);      // Turn motor off
                            digitalWrite(motor1.BIN1, LOW);
                        }

                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html { font-family: monospace; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: yellowgreen; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 32px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: gray;}</style></head>");

                        client.println("<body><h1>ESP32 Web Server</h1>");
                        client.println("<p>Control LED State</p>");

                        if (statePin16 == "off") {
                            client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
                        } else {
                            client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
                        }
                        if (statePin17 == "off") {
                            client.println("<p><a href=\"/17/on\"><button class=\"button\">ON</button></a></p>");
                        } else {
                            client.println("<p><a href=\"/17/off\"><button class=\"button button2\">OFF</button></a></p>");
                        }

                        // Motor control buttons
                        client.println("<p>Motor Control</p>");
                        if (motor1.motorState == "off") {
                            client.println("<p><a href=\"/motor/start\"><button class=\"button\">Start Motor</button></a></p>");
                        } else {
                            client.println("<p><a href=\"/motor/stop\"><button class=\"button button2\">Stop Motor</button></a></p>");
                        }

                        client.println("</body></html>");

                        // The HTTP response ends with another blank line
                        client.println();
                        break;
                    } else { // Clear currentLine on new line
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;  // Add to currentLine
                }
            }
        }
        header = "";  // Clear the header variable
        client.stop();
        Serial.println("Client disconnected.");
    }
}