#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <SmarTC_WiFi.h>

SmarTC_WiFi::SmarTC_WiFi()
{
    i_ssid = NULL;
    i_pwd = NULL;
    i_name = NULL;
}

SmarTC_WiFi::~SmarTC_WiFi()
{
    if (i_ssid)
        free(i_ssid);
    if (i_pwd)
        free(i_pwd);
    if (i_name)
        free(i_name);
}

bool SmarTC_WiFi::init(char *ssid, char *pwd, char *name)
{
    i_ssid = ssid;
    i_pwd = pwd;
    i_name = name;

    wifi_set_phy_mode(PHY_MODE_11B);
    system_phy_set_max_tpw(82);
    WiFi.mode(WIFI_STA);
    WiFi.hostname(name);

    return true;
}

bool SmarTC_WiFi::connect()
{
    WiFi.begin(i_ssid, i_pwd);

    unsigned long start = millis();
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        if (millis() - start > WIFI_CNX_TIMEOUT_MS)
            return false;
        else
            delay(1000);
    }

    return true;
}

bool SmarTC_WiFi::loop()
{
    unsigned long start = millis();
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        if (millis() - start > WIFI_CNX_TIMEOUT_MS)
            return false;
        else
            delay(1000);
    }

    return true;
}

void SmarTC_WiFi::scanNetworks()
{
    Serial.println(F("***** Scan Networks *****"));
    byte numSsid = WiFi.scanNetworks();

    Serial.print(F("Available networks:"));
    Serial.println(numSsid);

    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
        Serial.print(thisNet);
        Serial.print(F(") "));
        Serial.print(WiFi.SSID(thisNet));
        Serial.print(F("\tSignal: "));
        Serial.print(WiFi.RSSI(thisNet));
        Serial.print(F(" dBm"));
        Serial.print(F("\tEncryption: "));
        Serial.println(WiFi.encryptionType(thisNet));
    }
}

void SmarTC_WiFi::printMacAddress()
{
    char str_mac[18] = {0};
    byte mac[6];

    WiFi.macAddress(mac);
    Serial.print(F("MAC: "));
    sprintf(str_mac, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
    Serial.println(str_mac);
}

void SmarTC_WiFi::wifiStatusInfo()
{
    Serial.print(F("SSID: "));
    Serial.println(WiFi.SSID());

    byte *bssid;
    bssid = WiFi.BSSID();
    Serial.print(F("BSSID: "));
    Serial.print(bssid[5], HEX);
    Serial.print(F(":"));
    Serial.print(bssid[4], HEX);
    Serial.print(F(":"));
    Serial.print(bssid[3], HEX);
    Serial.print(F(":"));
    Serial.print(bssid[2], HEX);
    Serial.print(F(":"));
    Serial.print(bssid[1], HEX);
    Serial.print(F(":"));
    Serial.println(bssid[0], HEX);
    Serial.print(F("RSSI: "));
    Serial.println(WiFi.RSSI());

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
}
