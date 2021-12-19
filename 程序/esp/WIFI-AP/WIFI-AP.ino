#include <ESP8266WiFi.h>
//APmode串口透传

const char *ssid = "Raymond";
const char *password = "13696786574";
const int tcpPort = 8361;//你建立的Server服务端的端口号
WiFiServer server(tcpPort); //设立服务端监听端口号

void setup() {
  Serial.begin ( 9600 );
  Serial.println("");

  //server配置
  
  //boolean alreadyConnected = false;
  
  
  // 设置内网
  IPAddress softLocal(192,168,128,1);   // 1.设置内网WIFI IP地址
  IPAddress softGateway(192,168,128,1); //软网关
  IPAddress softSubnet(255,255,255,0); //软子网
  WiFi.softAPConfig(softLocal, softGateway, softSubnet);
   
  WiFi.softAP(ssid, password);      // 2创建wifi  名称 +密码 adminadmin 校验式网络-----（需要输入账号密码）,通道为1，wifi不隐藏，最大连接数=4
   
  IPAddress myIP = WiFi.softAPIP();  // 3输出创建的WIFI IP地址                   
  Serial.print("AP IP address: ");                                           
  Serial.println(myIP);
   
  Serial.print("softAPName: ");  // 4输出WIFI 名称
  Serial.println("Raymond");

  server.begin();
}
  
  
void loop() 
{
   WiFiClient client = server.available();
   if (client)
  {

    Serial.println("\n[Client Connect!]");
    while(client.connected()) //建立TCP通信后，开始串口透传
    { 
      //client.flush()

      //将串口数据打印给TCP客户端
      if (Serial.available()) 
      {
        size_t len = Serial.available(); //获取串口接收字节数
        uint8_t sbuf[len];
        Serial.readBytes(sbuf, len); //读取相应字节数的数据

        client.write(sbuf, len); //将串口数据发送给发送给客户端
        delay(1); //延时1ms
      }

      //将TCP数据打印给串口
      if(client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.println(line); 
      }  
    }
    delay(1);
    Serial.println("[Client disconnected]");
  }
}
