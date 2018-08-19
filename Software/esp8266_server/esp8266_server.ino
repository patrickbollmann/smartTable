/*********
  Patrick Bollmann
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <Wire.h>
// Replace with your network credentials
const char* ssid     = "Maritim";
const char* password = "MaritimGFS6";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String pState = "none";

// Assign output variables to GPIO pins
const int output5 = D5;
const int output4 = D4;

/** sendPID
 * @Author Patrick Bollmann
 * sendet ProgrammID (pid) über i2c bus an client #8 (#8 ist standard wert)
 * @params pid Programm ID
 * @params state programm State für URL (zb. glediator, pong,...)
 * @return nothing
 */
void sendPID(byte pid, String state){
   pState = state;
   Wire.beginTransmission(8); // transmit to device #8
   //Wire.write("Set pid = "+pid);        // sends five bytes
   Wire.write(pid);              // sends one byte
   Wire.endTransmission();    // stop transmitting
}
void setup() {
  Wire.begin(D1, D2); // sda, scl
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
// --------------------------------Send Program ID (pid) via I2C---------------------------------------------------------------------------------------------------------------------
            if (header.indexOf("GET /farbe/pink") >= 0) {
              sendPID(0,"Farbauswahl Pink");
            }else if (header.indexOf("GET /farbe/lila") >= 0) {
              sendPID(1,"Farbauswahl Lila");
            }else if (header.indexOf("GET /farbe/blau") >= 0) {
              sendPID(2,"Farbauswahl Blau");
            }else if (header.indexOf("GET /farbe/cyan") >= 0) {
              sendPID(3,"Farbauswahl Cyan");
            }else if (header.indexOf("GET /farbe/gruen") >= 0) {
              sendPID(4,"Farbauswahl Gruen");
            }else if (header.indexOf("GET /farbe/lime") >= 0) {
              sendPID(5,"Farbauswahl Lime");
            }else if (header.indexOf("GET /farbe/gelb") >= 0) {
              sendPID(6,"Farbauswahl Gelb");
            }else if (header.indexOf("GET /farbe/orange") >= 0) {
              sendPID(7,"Farbauswahl Orange");
            }else if (header.indexOf("GET /farbe/rot") >= 0) {
              sendPID(8,"Farbauswahl Rot");
            }else if (header.indexOf("GET /farbe/weiss") >= 0) {
              sendPID(9,"Farbauswahl Weiss");
            }else if (header.indexOf("GET /program/glediator") >= 0) {
              sendPID(10,"Glediator (Steuerung per PC)");
            }else if (header.indexOf("GET /program/pong") >= 0) {
              sendPID(11,"Pong");
            }else if (header.indexOf("GET /program/malen") >= 0) {
              sendPID(12,"Malen");
            }else if (header.indexOf("GET /program/flaschendrehen") >= 0) {
              sendPID(13,"Flaschendrehen");
            }else if (header.indexOf("GET /program/objekterkennung") >= 0) {
              sendPID(14,"Objekterkennung");
            }else if (header.indexOf("GET /program/staticcolor") >= 0) {
              sendPID(15,"Statische Farbe");
            }else if (header.indexOf("GET /off") >= 0) {
              sendPID(80,"Aus");
            }else if (header.indexOf("GET /helligkeit/10") >= 0) {
              sendPID(81,pState);
            }else if (header.indexOf("GET /helligkeit/20") >= 0) {
              sendPID(82,pState);
            }else if (header.indexOf("GET /helligkeit/30") >= 0) {
              sendPID(83,pState);
            }else if (header.indexOf("GET /helligkeit/40") >= 0) {
              sendPID(84,pState);
            }else if (header.indexOf("GET /helligkeit/50") >= 0) {
              sendPID(85,pState);
            }else if (header.indexOf("GET /helligkeit/60") >= 0) {
              sendPID(86,pState);
            }else if (header.indexOf("GET /helligkeit/70") >= 0) {
              sendPID(87,pState);
            }else if (header.indexOf("GET /helligkeit/80") >= 0) {
              sendPID(88,pState);
            }else if (header.indexOf("GET /helligkeit/90") >= 0) {
              sendPID(89,pState);
            }else if (header.indexOf("GET /helligkeit/100") >= 0) {
              sendPID(90,pState);
            }
//---------------------------------------------------------------------------------------------------------------------
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the Buttons
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; width: 300px}");
            //client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println("button:hover {box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}");
            //client.println(".button2 {background-color: #77878A;}");
            
            //der css bums fürs dropdown
            client.println(".dropbtn {background-color: #4CAF50;color: white;padding: 16px;font-size: 16px;border: none;cursor: pointer;}");
            client.println(".dropdown {position: relative;display: inline-block;}");
            client.println(".dropdown-content {display: none;position: absolute;background-color: #f9f9f9;min-width: 300px;box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);z-index: 1;}");
            client.println(".dropdown-content a {color: black;padding: 12px 16px;text-decoration: none;display: block;}");
            client.println(".dropdown-content a:hover {background-color: #f1f1f1}");
            client.println(".dropdown:hover .dropdown-content {display: block;}");
            client.println(".dropdown:hover .dropbtn {background-color: #3e8e41;}");
            client.println("</style></head>");
            
            // Web Page Headingq
            client.println("<body><h1>Tisch Programm Auswahl</h1>");
            
            // Print current pstate 
            client.println("<p>Aktuelles Programm: " + pState + "</p>");     
            // Create Buttons
            //dropdown Farbauswahl
            client.println("<div class='dropdown'><button class='button'>Farbe</button><div class='dropdown-content'><a href=\'/farbe/pink\'>Pink</a><a href=\'/farbe/lila\'>Lila</a><a href=\'/farbe/blau\'>Blau</a><a href=\'/farbe/cyan\'>Cyan</a><a href=\'/farbe/gruen\'>Gruen</a><a href=\'/farbe/lime\'>Lime</a><a href=\'/farbe/gelb\'>Gelb</a><a href=\'/farbe/orange\'>Orange</a><a href=\'/farbe/rot\'>Rot</a><a href=\'/farbe/weiss\'>Weiss</a></div></div>");
            client.println("<p></p>");
            client.println("<div class='dropdown'><button class='button'>Programme</button><div class='dropdown-content'><a href=\'/program/glediator\'>Glediator</a><a href=\'/program/pong\'>Pong</a><a href=\'/program/malen\'>Malen</a><a href=\'/program/flaschendrehen\'>Flaschendrehen</a><a href=\'/program/objekterkennung\'>Objeekterkennung</a><a href=\'/program/staticcolor\'>Statische Farbe</a></div></div>");
            client.println("<p></p>");
            client.println("<div class='dropdown'><button class='button'>Helligkeit</button><div class='dropdown-content'><a href=\'/helligkeit/10\'>10%</a><a href=\'/helligkeit/20\'>20%</a><a href=\'/helligkeit/30\'>30%</a><a href=\'/helligkeit/40\'>40%</a><a href=\'/helligkeit/50\'>50%</a><a href=\'/helligkeit/60\'>60%</a><a href=\'/helligkeit/70\'>70%</a><a href=\'/helligkeit/80\'>80%</a><a href=\'/helligkeit/90\'>90%</a><a href=\'/helligkeit/100\'>100%</a></div></div>");
            client.println("<p></p>");
            client.println("<p><a href=\'/farbe/pink\'><button class=\"button\">Aus</button></a></p>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
