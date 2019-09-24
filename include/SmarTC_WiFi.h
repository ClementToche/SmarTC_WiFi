#ifndef SMARTC_WIFI_H
#define SMARTC_WIFI_H

#define WIFI_CNX_TIMEOUT_MS 20000

class SmarTC_WiFi
{
public:
    SmarTC_WiFi();
    ~SmarTC_WiFi();

    bool init(char* ssid, char* pwd, char* name);

    bool connect();
    bool loop();

    void scanNetworks();
    void printMacAddress();
    void wifiStatusInfo();

private:
    char* i_ssid;
    char* i_pwd;
    char* i_name;
};

#endif // SMARTC_WIFI_H
