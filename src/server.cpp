#include <server.h>
#include <Arduino.h>
#include <WiFi.h>
#include <motor.h>

WiFiServer server(80);
Motor motor_ser;

void PrivateServer::initialize()
{
    Serial.begin(115200);
  

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
                if (c == '\n')
                {              // If the byte is a newline character
                    if (currentLine.length() == 0) 
                    {
                       client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");
                        client.println("<style>html { font-family: monospace; text-align: center;}</style>");
                        client.println("</head><body><h1>ESP32 Web Server</h1>");
                        client.println("<p><a href=\"/update_sensors\"><button style='font-size:20px; padding:10px;'>Update Sensors</button></a></p>");
                        client.println("<p><a href=\"/stop_motors\"><button style='font-size:20px; padding:10px;'>Stop Motors</button></a></p>");
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

            if (header.indexOf("GET /update_sensors") >= 0)
            {
                Serial.println("Sensor update requested.");
                sensorsEnabled = true;  
                header = "";         

            } 
            
            if (header.indexOf("GET /stop_motors") >= 0) 
            {     

                Serial.println("Stop Motors Requested.");               
                sensorsEnabled = false;   
                header = "";            
            }          

        }
        client.flush();
        client.stop();
        Serial.println("Client disconnected.");
    }
}
