#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
#define host "192.168.x.xx" /*Local server Hostname or Computer name*/
#define port 4000

String response = "";

IPAddress ip(192, 168, 1, xx); /* Desired IP */
IPAddress gateway(192, 168, 1, 1); /*Router gateway IP address*/

EthernetClient client;

String handshake(){
  if(client.connect(host, port)){

    String _str = "GET /";
           _str += " HTTP/1.1\r\n";
           _str += "Host: ";
           _str += host;
           _str += ":";
           _str += port;
           _str += "\r\n";
           _str += "Connection: keep-alive\r\n\r\n";

    client.print(_str);
    delay(200);
    while(client.available()){
      res = client.readStringUntil('\r');
    }
    return res;
    
  }else{
    return "Server handshake failed";
  }
}

String senddata(String _data){

  cnt++;
  
  String _str = "GET /senddata?";
           _str += "data="; 
           _str += _data;
     Serial.println(_str);      
           
           _str += " HTTP/1.1\r\n";
           _str += "Host: ";
           _str += host;
           _str += ":";
           _str += port;
           _str += "\r\n";
           _str += "Connection: keep-alive\r\n\r\n";
           
  if(client.connect(host, port)){
    client.print(_str);
    delay(200);
    while(client.available()){
      res = client.readStringUntil('\r');
    }
    return res;
    
  }else{
    return "Failed to send data";
  }
}

void setup(){

  Serial.begin(9600);
  Serial.println("Initialize Ethernet with DHCP:");
  if(Ethernet.begin(mac) == 0){
    Serial.println("Failed to configure Ethernet using DHCP");
    if(Ethernet.hardwareStatus()==EthernetNoHardware){
      Serial.println("Ethernet shield was not found.");
      /*.. there is need to re-install new Ethernet shield */
    }
    if(Ethernet.linkStatus()==LinkOFF){
      Serial.println("Ethernet cable is not connected.");
    }
    /* Setup DHCP */
    Ethernet.begin(mac, ip, gateway);
  }else{
    Serial.print("DHCP assigned IP = ");
    Serial.println(Ethernet.localIP());
  }

  /* Client connect to server process */
  delay(1000);
  Serial.print("Connecting to ");
  Serial.print(host);
  Serial.print("...");
  response = handshake();
  Serial.print(response);
  Serial.println();

}

void loop(){

  //..
  response = "";
  
  int randomint = random(10,50);
  response = senddata(String(randomint));
  Serial.println(response);

  delay(1000);

}
