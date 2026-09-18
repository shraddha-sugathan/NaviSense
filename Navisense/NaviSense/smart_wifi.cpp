#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ESPmDNS.h>
#include "smart_wifi.h"

void setupSmartWiFi() {
    Serial.println("Starting WiFiManager...");
    
    WiFiManager wifiManager;
    
    // Set a timeout so if it gets stuck, it restarts
    wifiManager.setConfigPortalTimeout(180); 
    
    if (!wifiManager.autoConnect("NAVISENSE_SETUP")) {
        Serial.println("Failed to connect and hit timeout. Rebooting...");
        delay(3000);
        ESP.restart();
    }

    Serial.println("WiFi Success!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());


    // ==========================================
    // START THE mDNS BROADCASTER
    // ==========================================
    if (!MDNS.begin("navisense")) { 
        Serial.println("Error setting up MDNS responder!");
    } else {
        Serial.println("mDNS responder started!");
        Serial.println("You can now connect to http://navisense.local");
    }
    // ==========================================
}