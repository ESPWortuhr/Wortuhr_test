/*--------------------------------------------------
Dieses File gehoert zum Code von:
https://github.com/Eisbaeeer/Ulrich-Radig_Wort_Uhr_Version_2
--------------------------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#ifdef UHR_242

void getweather(){
    
        // connect to server  
        bool ok = client.connect(server, 80);
        bool beginFound = false;
        
         #ifdef DEBUG
         USE_SERIAL.println(""); 
         USE_SERIAL.println("--------------------------------------");      
         USE_SERIAL.println ( "Connecting to Openweathermap.org" );  
         USE_SERIAL.println("--------------------------------------");
                
         #endif

        // create calling URL
        strncat(resource, resource1, 22);
        strncat(resource, G.cityid, 7);
        strncat(resource, resource2, 20);
        strncat(resource, G.apikey, 32);
        strncat(resource, resource3, 6);
  
         #ifdef DEBUG      
         USE_SERIAL.print ( "Calling URL: " );
         USE_SERIAL.println (resource);      
         #endif
        
        if (ok == 1){
    
        //Send request to resource
        client.print("GET ");
        client.print(resource);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();
    
        delay(100);
    
        //Reading stream and remove headers
        client.setTimeout(6000);
   
        bool ok_header = ok_header = client.find("\r\n\r\n");
    
        while(!ok_header){
        // wait
        }
         
        client.readBytes(response, 6000);
        
         #ifdef DEBUG
         USE_SERIAL.println("Antwort: "); 
         USE_SERIAL.println(response);  
         //TelnetMsg("Antwort: "); 
         //TelnetMsg(response);  
         
         #endif
        
        // process JSON
        DynamicJsonBuffer jsonBuffer;
        
        // But.....make sure the stream header is valid
        // Sometime OWM includes invalid data after the header
        // Parsing fails if this data is not removed
        
        if(int(response[0]) != 123){
            #ifdef DEBUG
            USE_SERIAL.println("Wrong start char detected"); 
            #endif
        int i = 0;
        while(!beginFound){
            if(int(response[i]) == 123){ // check for the "{" 
            beginFound = true;
            #ifdef DEBUG
            USE_SERIAL.println("{ found at "); 
            USE_SERIAL.println(i); 
            #endif
            }
            i++;
        }

            int eol = sizeof(response);
            #ifdef DEBUG
            USE_SERIAL.println("Length = "); 
            USE_SERIAL.println(eol); 
            #endif
             
    
            //restructure by shifting the correct data
            #ifdef DEBUG
            USE_SERIAL.println("restructure"); 
            #endif
            for(int c=0; c<(eol-i); c++){
                response[c] = response[((c+i)-1)];
                #ifdef DEBUG
                USE_SERIAL.println(response[c]); 
                #endif
            }
     
            #ifdef DEBUG
            USE_SERIAL.println("Done...!"); 
            //TelnetMsg("Done...!"); 
            #endif

            }
        
        
        JsonObject& root = jsonBuffer.parseObject(response);
        
        if (!root.success()) {
            #ifdef DEBUG
            USE_SERIAL.println("JSON parsing failed!"); 
            #endif
        } 
        else {
        #ifdef DEBUG
        USE_SERIAL.println("JSON parsing worked!"); 
        //TelnetMsg("JSON parsing worked!"); 
        #endif
        }

        //Variable mit json Wert forecast füllen
        const char* location = root["city"]["name"]; 
        const char* wetter_6 = root["list"][1]["weather"][0]["description"];
        const int wetterid_6 = root["list"][1]["weather"][0]["id"];
        double temp_6 = root["list"][1]["main"]["temp"];
        const char* wetter_12 = root["list"][3]["weather"][0]["description"];
        const int wetterid_12 = root["list"][3]["weather"][0]["id"];
        double temp_12 = root["list"][3]["main"]["temp"];
        const char* wetter_18 = root["list"][5]["weather"][0]["description"];
        const int wetterid_18 = root["list"][5]["weather"][0]["id"];
        double temp_18 = root["list"][5]["main"]["temp"];
        const char* wetter_24 = root["list"][7]["weather"][0]["description"];
        const int wetterid_24 = root["list"][7]["weather"][0]["id"];
        double temp_24 = root["list"][7]["main"]["temp"];

        /*--------------------------------------------------
        List of Conditions http://openweathermap.org/weather-conditions
        Weather condition code (wetterid):

        2xx Thunderstorm = Gewitter
        3xx Drizzle = Nieselregen
        5xx Rain = Regen
        6xx Snow = Schnee
        7xx Clouds = Warung
        800 Clear = Klar
        80x Clouds = Wolken
        --------------------------------------------------*/
                
        // Print data to Serial
        #ifdef DEBUG
        USE_SERIAL.print("*** "); 
        USE_SERIAL.print(location); 
        USE_SERIAL.println(" ***"); 
        USE_SERIAL.println("----------");
        USE_SERIAL.println("+6h");                                    
        USE_SERIAL.print("Type: "); 
        USE_SERIAL.println(wetter_6); 
        USE_SERIAL.print("Wetter ID: "); 
        USE_SERIAL.println(wetterid_6); 
        USE_SERIAL.print("Temp: "); 
        USE_SERIAL.print(temp_6);    
        USE_SERIAL.println("°C"); 
        USE_SERIAL.println("----------");
        USE_SERIAL.println("+12h");                                    
        USE_SERIAL.print("Type: "); 
        USE_SERIAL.println(wetter_12); 
        USE_SERIAL.print("Wetter ID: "); 
        USE_SERIAL.println(wetterid_12); 
        USE_SERIAL.print("Temp: "); 
        USE_SERIAL.print(temp_12);    
        USE_SERIAL.println("°C"); 
        USE_SERIAL.println("----------");              
        USE_SERIAL.println("+18h");                                    
        USE_SERIAL.print("Type: "); 
        USE_SERIAL.println(wetter_18); 
        USE_SERIAL.print("Wetter ID: "); 
        USE_SERIAL.println(wetterid_18); 
        USE_SERIAL.print("Temp: "); 
        USE_SERIAL.print(temp_18);    
        USE_SERIAL.println("°C"); 
        USE_SERIAL.println("----------");              
        USE_SERIAL.println("+24h");                                    
        USE_SERIAL.print("Type: "); 
        USE_SERIAL.println(wetter_24); 
        USE_SERIAL.print("Wetter ID: "); 
        USE_SERIAL.println(wetterid_24); 
        USE_SERIAL.print("Temp: "); 
        USE_SERIAL.print(temp_24);    
        USE_SERIAL.println("°C");
        USE_SERIAL.println("Stunde");
        USE_SERIAL.println(_stunde);
        USE_SERIAL.println("----------");  
        #endif

        // Wetterdaten auf LED Matrix ausgeben
        
        // Wetterdaten in Variable speichern
        if (temp_6 >= 35) { wtemp_6 = 35; }
        if ((temp_6 >= 30) && (temp_6 <= 34)) { wtemp_6 = 30; }
        if ((temp_6 >= 25) && (temp_6 <= 29)) {  wtemp_6 = 25; }
        if ((temp_6 >= 20) && (temp_6 <= 24)) {  wtemp_6 = 20; }
        if ((temp_6 >= 15) && (temp_6 <= 19)) {  wtemp_6 = 15; }
        if ((temp_6 >= 10) && (temp_6 <= 14)) {  wtemp_6 = 10; }   
        if ((temp_6 >= 5) && (temp_6 <= 9)) {  wtemp_6 = 5; }
        if ((temp_6 >= 0) && (temp_6 <= 5)) {  wtemp_6 = 1; }
        if ((temp_6 < 0) && (temp_6 >= -5)) {  wtemp_6 = -1; }
        if ((temp_6 <=-5) && (temp_6 >= -9)) {  wtemp_6 = -5; }
        if ((temp_6 <=-10) && (temp_6 >= -14)) {  wtemp_6 = -10; }
        if ((temp_6 <=-15) && (temp_6 >= -19)) {  wtemp_6 = -15; }
        if ((temp_6 <=-20) && (temp_6 >= -24)) {  wtemp_6 = -20; }
        if (temp_6 <= -25) {  wtemp_6 = -25; }
        if ((int(wetterid_6) >= 200) && (int(wetterid_6) < 300)) { wwetter_6 = 200;}
        if ((int(wetterid_6) >= 300) && (int(wetterid_6) < 400)) { wwetter_6 = 300;}
        if ((int(wetterid_6) >= 500) && (int(wetterid_6) < 600)) { wwetter_6 = 500;}
        if ((int(wetterid_6) >= 600) && (int(wetterid_6) < 700)) { wwetter_6 = 600;}
        if ((int(wetterid_6) >= 700) && (int(wetterid_6) < 800)) { wwetter_6 = 700;}
        if (int(wetterid_6) == 800) { wwetter_6 = 800;}
        if ((int(wetterid_6) > 800) && (int(wetterid_6) < 900)) { wwetter_6 = 801;}    

        if (temp_12 >= 35) {  wtemp_12 = 35; }
        if ((temp_12 >= 30) && (temp_12 <= 34)) {  wtemp_12 = 30; }
        if ((temp_12 >= 25) && (temp_12 <= 29)) {  wtemp_12 = 25; }
        if ((temp_12 >= 20) && (temp_12 <= 24)) {  wtemp_12 = 20; }
        if ((temp_12 >= 15) && (temp_12 <= 19)) {  wtemp_12 = 15; }
        if ((temp_12 >= 10) && (temp_12 <= 14)) {  wtemp_12 = 10; }   
        if ((temp_12 >= 5) && (temp_12 <= 9)) {  wtemp_12 = 5; }
        if ((temp_12 >= 0) && (temp_12 <= 5)) {  wtemp_12 = 1; }
        if ((temp_12 < 0) && (temp_12 >= -5)) {  wtemp_12 = -1; }
        if ((temp_12 <=-5) && (temp_12 >= -9)) {  wtemp_12 = -5; }
        if ((temp_12 <=-10) && (temp_12 >= -14)) {  wtemp_12 = -10; }
        if ((temp_12 <=-15) && (temp_12 >= -19)) {  wtemp_12 = -15; }
        if ((temp_12 <=-20) && (temp_12 >= -24)) {  wtemp_12 = -20; }
        if (temp_12 <= -25) {  wtemp_12 = -25; }
        if ((int(wetterid_12) >= 200) && (int(wetterid_12) < 300)) { wwetter_12 = 200;}
        if ((int(wetterid_12) >= 300) && (int(wetterid_12) < 400)) { wwetter_12 = 300;}
        if ((int(wetterid_12) >= 500) && (int(wetterid_12) < 600)) { wwetter_12 = 500;}
        if ((int(wetterid_12) >= 600) && (int(wetterid_12) < 700)) { wwetter_12 = 600;}
        if ((int(wetterid_12) >= 700) && (int(wetterid_12) < 800)) { wwetter_12 = 700;}
        if (int(wetterid_12) == 800) { wwetter_12 = 800;}
        if ((int(wetterid_12) > 800) && (int(wetterid_12) < 900)) { wwetter_12 = 801;}

       if (temp_18 >= 35) {  wtemp_18 = 35; }
        if ((temp_18 >= 30) && (temp_18 <= 34)) {  wtemp_18 = 30; }
        if ((temp_18 >= 25) && (temp_18 <= 29)) {  wtemp_18 = 25; }
        if ((temp_18 >= 20) && (temp_18 <= 24)) {  wtemp_18 = 20; }
        if ((temp_18 >= 15) && (temp_18 <= 19)) {  wtemp_18 = 15; }
        if ((temp_18 >= 10) && (temp_18 <= 14)) {  wtemp_18 = 10; }   
        if ((temp_18 >= 5) && (temp_18 <= 9)) {  wtemp_18 = 5; }
        if ((temp_18 >= 0) && (temp_18 <= 5)) {  wtemp_18 = 1; }
        if ((temp_18 < 0) && (temp_18 >= -5)) {  wtemp_18 = -1; }
        if ((temp_18 <=-5) && (temp_18 >= -9)) {  wtemp_18 = -5; }
        if ((temp_18 <=-10) && (temp_18 >= -14)) {  wtemp_18 = -10; }
        if ((temp_18 <=-15) && (temp_18 >= -19)) {  wtemp_18 = -15; }
        if ((temp_18 <=-20) && (temp_18 >= -24)) {  wtemp_18 = -20; }
        if (temp_18 <= -25) {  wtemp_18 = -25; }
        if ((int(wetterid_18) >= 200) && (int(wetterid_18) < 300)) { wwetter_18 = 200;}
        if ((int(wetterid_18) >= 300) && (int(wetterid_18) < 400)) { wwetter_18 = 300;}
        if ((int(wetterid_18) >= 500) && (int(wetterid_18) < 600)) { wwetter_18 = 500;}
        if ((int(wetterid_18) >= 600) && (int(wetterid_18) < 700)) { wwetter_18 = 600;}
        if ((int(wetterid_18) >= 700) && (int(wetterid_18) < 800)) { wwetter_18 = 700;}
        if (int(wetterid_18) == 800) { wwetter_18 = 800;}
        if ((int(wetterid_18) > 800) && (int(wetterid_18) < 900)) { wwetter_18 = 801;}

        if (temp_24 >= 35) {  wtemp_24 = 35; }
        if ((temp_24 >= 30) && (temp_24 <= 34)) {  wtemp_24 = 30; }
        if ((temp_24 >= 25) && (temp_24 <= 29)) {  wtemp_24 =25; }
        if ((temp_24 >= 20) && (temp_24 <= 24)) {  wtemp_24 = 20; }
        if ((temp_24 >= 15) && (temp_24 <= 19)) {  wtemp_24 = 15; }
        if ((temp_24 >= 10) && (temp_24 <= 14)) {  wtemp_24 = 10; }   
        if ((temp_24 >= 5) && (temp_24 <= 9)) {  wtemp_24 = 5; }
        if ((temp_24 >= 0) && (temp_24 <= 5)) {  wtemp_24 = 1; }
        if ((temp_24 < 0) && (temp_24 >= -5)) {  wtemp_24 = -1; }
        if ((temp_24 <=-5) && (temp_24 >= -9)) {  wtemp_24 = -5; }
        if ((temp_24 <=-10) && (temp_24 >= -14)) {  wtemp_24 = -10; }
        if ((temp_24 <=-15) && (temp_24 >= -19)) {  wtemp_24 = -15; }
        if ((temp_24 <=-20) && (temp_24 >= -24)) {  wtemp_24 = -20; }
        if (temp_24 <= -25) {  wtemp_24 = -25; }
        if ((int(wetterid_24) >= 200) && (int(wetterid_24) < 300)) { wwetter_24 = 200;}
        if ((int(wetterid_24) >= 300) && (int(wetterid_24) < 400)) { wwetter_24 = 300;}
        if ((int(wetterid_24) >= 500) && (int(wetterid_24) < 600)) { wwetter_24 = 500;}
        if ((int(wetterid_24) >= 600) && (int(wetterid_24) < 700)) { wwetter_24 = 600;}
        if ((int(wetterid_24) >= 700) && (int(wetterid_24) < 800)) { wwetter_24 = 700;}
        if (int(wetterid_24) == 800) { wwetter_24 = 800;}
        if ((int(wetterid_24) > 800) && (int(wetterid_24) <= 900)) { wwetter_24 = 801;}

        // Tageszeit bestimmen
        if ((_stunde >=3) && (_stunde <= 9)) { wstunde = 1;}
        if ((_stunde >9) && (_stunde <= 15)) { wstunde = 2;}
        if ((_stunde >15) && (_stunde <= 21)) { wstunde = 3;}
        if ((_stunde >21) && (_stunde <= 23)) { wstunde = 4;}
        if ((_stunde >=0) && (_stunde < 3)) { wstunde = 4;}

      

        #ifdef DEBUG
        USE_SERIAL.print("Temp_6 - ");
        USE_SERIAL.println(wtemp_6);
        USE_SERIAL.print("wwetter_6 - ");        
        USE_SERIAL.println(wwetter_6);
        USE_SERIAL.println("--------- ");
        USE_SERIAL.print("Temp_12 - ");
        USE_SERIAL.println(wtemp_12);
        USE_SERIAL.print("wwetter_12 - ");
        USE_SERIAL.println(wwetter_12);
        USE_SERIAL.println("--------- ");
        USE_SERIAL.print("Temp_18 - ");
        USE_SERIAL.println(wtemp_18);
        USE_SERIAL.print("wwetter_18 - ");
        USE_SERIAL.println(wwetter_18);
        USE_SERIAL.println("--------- ");
        USE_SERIAL.print("Temp_24 - ");
        USE_SERIAL.println(wtemp_24);
        USE_SERIAL.print("wwetter_24 - ");
        USE_SERIAL.println(wwetter_24);
        USE_SERIAL.println("--------- ");
        USE_SERIAL.print("wstunde - ");
        USE_SERIAL.println(wstunde);
        USE_SERIAL.println("--------- ");
        
        #endif    
     
     
     }
     client.stop(); // disconnect from server     
}
#endif
