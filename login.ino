#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Sharif-WiFi";
const char* password = "";

void setup() {
  Serial.begin(115200);
  delay(4000); //Delay needed before calling the WiFi.begin
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;
    http.begin("https://net2.sharif.edu/login"); //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header
    String postData = "username=Pouria_Arefijamal&password=:))"; //Specify the data
    int httpResponseCode = http.POST(postData); //Send the actual POST request
    if (httpResponseCode > 0) {
      String response = http.getString(); //Get the response to the request
      response.replace("<[^>]*>", ""); //Remove HTML tags
      response.replace("\n", ""); //Remove newlines
      response.trim(); //Remove leading/trailing whitespaces
      Serial.println(httpResponseCode); //Print return code
      Serial.println(response); //Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end(); //Free resources
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(10000); //Send a request every 10 seconds
}
