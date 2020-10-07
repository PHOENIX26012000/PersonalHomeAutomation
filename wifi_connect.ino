#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "oppo";
const char* password = "12345678";
String  command ="";
int relay1 = 16;
int relay2 = 15;
int relay3 = 3;
int relay4 = 1;
void setup() {
  
Serial.begin(9600);
 pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);  
  pinMode(relay3, OUTPUT);  
  pinMode(relay4, OUTPUT);  

  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
 digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
Serial.println("Connecting to WIFI");
//server.begin();
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(1000);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();
  
}


void loop() {
    client = server.available();
    if (!client) return; 
    command = checkClient ();
    //client.println("HTTP/1.1 200 OK");
  //client.println("Content-Type: text/html");
  //client.println("");
  //client.println("<!DOCTYPE HTML>");
  //client.println("<html>");
  //client.println("<body>");
  //client.println(echo);
  //client.println("</body>");
  //client.println("</html>");
  //client.stop();
  //delay(1);
   

         if ( command== "light on"   || command == "r1on"  || command == "ligar um")        digitalWrite(relay1,LOW);
    else if ( command == "light off" ||command == "r1off" || command == "desligar um")     digitalWrite(relay1,HIGH);
    else if ( command == "device on"    ||command == "r2on"  || command == "ligar dois")      digitalWrite(relay2,LOW);     
    else if ( command == "device off" || command == "r2off" ||command == "desligar dois")   digitalWrite(relay2,HIGH);
    else if (command == "r3on"  || command == "ligar 3"    || command == "ligar tres")      digitalWrite(relay3,LOW);
    else if (command == "r3off" || command == "desligar 3" || command == "desligar tres")   digitalWrite(relay3,HIGH);
    else if (command == "r4on"  || command == "ligar 4"    || command == "ligar quatro")    digitalWrite(relay4,LOW);
    else if (command == "r4off" || command == "desligar 4" || command == "desligar quatro") digitalWrite(relay4,HIGH);
   else if (command == "allon" || command == "ligar tudo" || command == "ligar todos") 
    {
      digitalWrite(relay1,LOW);
      digitalWrite(relay2,LOW);
      digitalWrite(relay3,LOW);
      digitalWrite(relay4,LOW);
    }
    else if (command == "alloff" || command == "desligar tudo" || command == "desligar todos") 
    {
      digitalWrite(relay1,HIGH);
      digitalWrite(relay2,HIGH);
      digitalWrite(relay3,HIGH);
      digitalWrite(relay4,HIGH);
    }
   // sendBackEcho("As your wish"); // send command echo back to android device
    command = "";
}
String checkClient(void){
  while(!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  Serial.print(request);
  return request;
}
//String checkClient (void)
//{
//  while(!client.available()) delay(1); 
//  String request = client.readStringUntil('\r');
//  request.remove(0, 5);
//  request.remove(request.length()-9,9);
//  Serial.print(request);
//  return request;
//}
void sendBackEcho(String echo)
{
  client.println("HTTP/1.1 200 As your wish");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(echo);
  client.println("</html>");
  client.stop();
  delay(1);
}
