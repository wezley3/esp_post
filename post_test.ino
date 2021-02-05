#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
    
// wifi info
const char* ssid = ""; 
const char* password = ""; 
    
// Host ip and url
const char* host = "http://192.168.1.41"; //edit the host adress, ip address etc. 
String url = "/esp/test_post.php"; 

// Setup connection to wireless router
void setup() 
{ 
      
  Serial.begin(115200); 
  delay(10); // We start by connecting to a WiFi network 
  Serial.println(); 
  Serial.println(); Serial.print("Connecting to ");
  Serial.println(ssid); 
    
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default, would try to act as both a client and an access-point and could cause network-issues with your other WiFi-devices on your WiFi-network. */ 
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); 
    
  // Loop untill wifi connection is established
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); 
    Serial.print("."); 
  } 
    
  // Pring out the ip address that was obtained
  Serial.println(""); 
  Serial.println("WiFi connected"); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP()); 

} 
    
// Count the loop numbers
int loop_number = 0;

// Loop through connecting to host address and post loop number
void loop() 
{ 
      
  delay(5000); 
        
  // Set post data and host ip/post url
  String postData = "test_post=loop_number" + String(loop_number++); 
  String address = host + url; 
        
  // Set up post header and address
  HTTPClient http; 
  http.begin(address); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
  // Post the data and print the code
  auto httpCode = http.POST(postData); 
  Serial.print("Post response code: ");
  Serial.println(httpCode); 

  // Get the return string from post result
  String payload = http.getString(); 
  Serial.print("Return data: ");
  Serial.println(payload); //Print request response payload 

  // Close connection to http
  http.end(); 
  Serial.println("closing connection"); 

} 
