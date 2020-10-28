#pragma once

#include "WebSocketsServer.h"
#include "WebPageWortuhr.h"
#include "Uhr.h"

#define RESPONSE_SIZE    900

const char* const html_sliders[] PROGMEM = {index_html_head, index_html_body_first, slider_RGBW, index_html_body_mid, Switches_UHR242, Switches_UHR169, index_html_body_rest};

class WebPage_Adapter : public WebSocketsServer {

public:
    // forward the port to the parent class constructor
    WebPage_Adapter(int port) : WebSocketsServer(port) {
    }

    /**
     * @param client WSclient_t *  ptr to the client struct
     */
    void handleNonWebsocketConnection(WSclient_t *client) override {
        DEBUG_WEBSOCKETS("[WS-Server][%d][handleHeader] no Websocket connection close.\n", client->num);
        client->tcp->write("HTTP/1.1 200 OK\r\n"
                           "Server: arduino-WebSocket-Server\r\n"
                           "Content-Type: text/html\r\n"
                           //--                    "Content-Length: 32\r\n"
                           "Connection: close\r\n"
                           //--                    "Sec-WebSocket-Version: 13\r\n"
                           "\r\n");
        Send_HTML_Code_for_Sliders(client, sizeof(index_html_head), 0);
        Send_HTML_Code_for_Sliders(client, sizeof(index_html_body_first), 1);
        if (G.Colortype == Grbw){Send_HTML_Code_for_Sliders(client, sizeof(slider_RGBW), 2);};
        Send_HTML_Code_for_Sliders(client, sizeof(index_html_body_mid), 3);
        if (G.UhrtypeDef == Uhr_242){Send_HTML_Code_for_Sliders(client, sizeof(Switches_UHR242), 4);};
        if (G.UhrtypeDef == Uhr_169){Send_HTML_Code_for_Sliders(client, sizeof(Switches_UHR169), 5);};
        Send_HTML_Code_for_Sliders(client, sizeof(index_html_body_rest), 6);
        clientDisconnect(client);
    }

    void Send_HTML_Code_for_Sliders(const WSclient_t *client, uint16_t slider_size, uint8_t slider_index) const {
        char str[RESPONSE_SIZE + 4];
        unsigned ww = 0;
        unsigned yy = 0;
        int j;
        while (ww < slider_size) {
            str[yy] = pgm_read_byte(&html_sliders[slider_index][ww]);
            str[yy + 1] = '\0';
            yy++;
            if (yy == RESPONSE_SIZE) {
                j = strlen(str);
                client->tcp->write(&str[0], j);
                str[0] = '\0';
                yy = 0;
            }
            ww++;
        }
        if (yy > 0) {
            j = strlen(str);
            client->tcp->write(&str[0], j);
        }
    }

};

//-- WebSocketserver
WebPage_Adapter webSocket = WebPage_Adapter(80);

//------------------------------------------------------------------------------

uint16_t split(uint8_t *payload, uint8_t start, uint8_t end) {
    char buffer[3];
	uint8_t m = 0;
    for (uint16_t k = start; k < (start + end); k++) {
        buffer[m] = payload[k];
        m++;
    }
    return atoi(buffer);
}

//------------------------------------------------------------------------------

uint32_t split(uint8_t *payload, uint8_t start, uint8_t end, uint8_t i) {
	char buffer[i];
	uint8_t m = 0;
	for (uint16_t k = start; k < (start + end); k++) {
		buffer[m] = payload[k];
		m++;
	}
	return atoi(buffer);
}

//------------------------------------------------------------------------------

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t lenght) {
    int ii;
    int jj;
    char tmp[30];
    payload = (payload == NULL) ? (uint8_t *) "" : payload;
    Serial.printf("Client-Nr.: [%u]  WStype: %u payload: %s\n", num, type, payload);

    switch (type) {
        case WStype_DISCONNECTED: {
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        }
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            break;
        }
        case WStype_TEXT:
		{
			Serial.printf("[%u] get Text: %s\n", lenght, payload);

			uint16_t command = split (payload, 0, 3);
			G.param1 = split (payload, 3, 3);
			G.param2 = split (payload, 6, 3);

			switch (command)
			{
				case COMMAND_MODE_WORD_CLOCK:
				{        // Uhrzeit Vordergrund Farbe einstellen
					G.prog = COMMAND_MODE_WORD_CLOCK;
					G.rgb[Foreground][0] = split (payload, 9, 3);
					G.rgb[Foreground][1] = split (payload, 12, 3);
					G.rgb[Foreground][2] = split (payload, 15, 3);
					G.rgb[Foreground][3] = split (payload, 18, 3);

					G.rgb[Background][0] = split (payload, 21, 3);
					G.rgb[Background][1] = split (payload, 24, 3);
					G.rgb[Background][2] = split (payload, 27, 3);
					G.rgb[Background][3] = split (payload, 30, 3);

					G.rgb[Frame][0] = split (payload, 33, 3);
					G.rgb[Frame][1] = split (payload, 36, 3);
					G.rgb[Frame][2] = split (payload, 39, 3);
					G.rgb[Frame][3] = split (payload, 42, 3);

					G.rgb[Effect][0] = split (payload, 45, 3);
					G.rgb[Effect][1] = split (payload, 48, 3);
					G.rgb[Effect][2] = split (payload, 51, 3);
					G.rgb[Effect][3] = split (payload, 54, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_MODE_SECONDS:
				{      // Sekunden
					G.prog = COMMAND_MODE_SECONDS;
					if (G.param1 == 0) { G.prog_init = 1; }

					G.rgb[Effect][0] = split (payload, 45, 3);
					G.rgb[Effect][1] = split (payload, 48, 3);
					G.rgb[Effect][2] = split (payload, 51, 3);
					G.rgb[Effect][3] = split (payload, 54, 3);
					G.hell = split (payload, 57, 3);
					G.geschw = split (payload, 60, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_MODE_MARQUEE:
				{      // Laufschrift
					G.prog = COMMAND_MODE_MARQUEE;
					if (G.param1 == 0) { G.prog_init = 1; }

					G.rgb[Effect][0] = split (payload, 45, 3);
					G.rgb[Effect][1] = split (payload, 48, 3);
					G.rgb[Effect][2] = split (payload, 51, 3);
					G.rgb[Effect][3] = split (payload, 54, 3);
					G.hell = split (payload, 57, 3);
					G.geschw = split (payload, 60, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_MODE_RAINBOW:
				{      // Regenbogen
					G.prog = COMMAND_MODE_RAINBOW;
					G.prog_init = 1;

					G.hell = split (payload, 57, 3);
					G.geschw = split (payload, 60, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_MODE_CHANGE:
				{      // Farbwechsel
					G.prog = COMMAND_MODE_CHANGE;
					G.prog_init = 1;

					G.hell = split (payload, 57, 3);
					G.geschw = split (payload, 60, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_MODE_COLOR:
				{      // Farbe
					G.prog = COMMAND_MODE_COLOR;
					G.prog_init = 1;

					G.rgb[Effect][0] = split (payload, 45, 3);
					G.rgb[Effect][1] = split (payload, 48, 3);
					G.rgb[Effect][2] = split (payload, 51, 3);
					G.rgb[Effect][3] = split (payload, 54, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_BRIGHTNESS:
				{      // Helligkeit
					G.hell = split (payload, 57, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SPEED:
				{       // Geschwindigkeit
					G.geschw = split (payload, 60, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_INITIAL_VALUES:
				{       // Startwerte speichern
					G.conf = COMMAND_SET_INITIAL_VALUES;
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_TIME:
				{       // Uhrzeit setzen
					G.conf = COMMAND_SET_TIME;
					ii = 0;
					tmp[0] = '\0';
					uint32_t  tt = split(payload, 12, 28, 28-12);
					Serial.println(tt);
					for (uint8_t k = 12; k < 28; k++)
					{
						tmp[ii] = payload[k];
						ii++;
					}
					tt = atoi(tmp);
					Serial.println(tt);
					Serial.printf("Conf: Time: %d\n", tt);
					setTime(tt);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_HOSTNAME:
				{         // Hostname speichern
					G.conf = COMMAND_SET_HOSTNAME;
					ii = 0;
					for (uint8_t k = 9; k < 25; k++)
					{
						if (payload[k] != ' ')
						{
							G.hostname[ii] = payload[k];
							ii++;
						}
					}
					G.hostname[ii] = '\0';
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_SETTING_SECOND:
				{       // Anzeige Sekunden speichern
					G.conf = COMMAND_SET_SETTING_SECOND;
					G.zeige_sek = split (payload, 9, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_MINUTE:
				{       // Anzeige Minuten speichern
					G.conf = COMMAND_SET_MINUTE;
					G.zeige_min = split (payload, 9, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_LDR:
				{       // LDR speichern
					G.conf = COMMAND_SET_LDR;
					G.ldr = split (payload, 9, 3);
					G.ldrCal = split (payload, 12, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_COLORTYPE:
				{       // UhrType speichern
					G.conf = COMMAND_SET_COLORTYPE;
					G.Colortype = split (payload, 9, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_UHRTYPE:
				{       // UhrType speichern
					G.conf = COMMAND_SET_UHRTYPE;
					G.UhrtypeDef = split (payload, 9, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_WEATHER_DATA:
				{       // Openweathermap speichern
					G.conf = COMMAND_SET_WEATHER_DATA;
					ii = 0;
					for (uint8_t k = 9; k < 16; k++)
					{
						if (payload[k] != ' ')
						{
							G.cityid[ii] = payload[k];
							ii++;
						}
					}
					G.cityid[ii] = '\0';
					//
					jj = 0;
					for (uint8_t l = 17; l < 49; l++)
					{
						if (payload[l] != ' ')
						{
							G.apikey[jj] = payload[l];
							jj++;
						}
					}
					G.apikey[jj] = '\0';
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_BRIGHTNESS:
				{       // Helligkeit speichern
					G.conf = COMMAND_SET_BRIGHTNESS;
					G.h6 = split (payload, 9, 3);
					G.h8 = split (payload, 12, 3);
					G.h12 = split (payload, 15, 3);
					G.h16 = split (payload, 18, 3);
					G.h18 = split (payload, 21, 3);
					G.h20 = split (payload, 24, 3);
					G.h22 = split (payload, 27, 3);
					G.h24 = split (payload, 30, 3);
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_MARQUEE_TEXT:
				{       // Lauftext speichern
					G.conf = COMMAND_SET_MARQUEE_TEXT;
					ii = 0;
					for (uint8_t k = 9; k < 39; k++)
					{
						if (payload[k] != ' ')
						{
							G.ltext[ii] = payload[k];
							ii++;
						}
					}
					G.ltext[ii] = '\0';
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_TIMESERVER:
				{       // Zeitserver speichern
					G.conf = COMMAND_SET_TIMESERVER;
					ii = 0;
					for (int k = 9; k < 24; k++)
					{
						G.zeitserver[ii] = payload[k];
						ii++;
					}
					G.zeitserver[ii] = '\0';
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_WIFI_DISABLED:
				{       // Zeitserver speichern
					G.conf = COMMAND_SET_WIFI_DISABLED;
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_SET_WIFI_AND_RESTART:
				{       // WLAN-Daten speichern und neu starten
					G.conf = COMMAND_SET_WIFI_AND_RESTART;
					ii = 0;
					for (uint8_t k = 9; k < 34; k++)
					{
						G.ssid[ii] = payload[k];
						ii++;
					}
					uint8_t index = 0;
					for (int8_t counter = sizeof(G.ssid) / sizeof(G.ssid[0]) - 1; counter > -1; counter--)
					{
						if (!isSpace(G.ssid[counter]))
						{
							index = counter;
							break;
						}
					}
					G.ssid[index + 1] = '\0';

					ii = 0;
					for (int k = 34; k < 59; k++)
					{
						if (payload[k] != ' ')
						{
							G.passwd[ii] = payload[k];
							ii++;
						}
					}
					G.passwd[ii] = '\0';
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_RESET:
				{      // Reset
					G.conf = COMMAND_RESET;
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_REQUEST_CONFIG_VALUES:
				{      // Config anfordern
					G.conf = COMMAND_REQUEST_CONFIG_VALUES;
					G.client_nr = num;
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_REQUEST_COLOR_VALUES:
				{      // Farbwerte anfordern
					G.conf = COMMAND_REQUEST_COLOR_VALUES;
					G.client_nr = num;
					break;
				}

					//------------------------------------------------------------------------------

				case COMMAND_REQUEST_WIFI_LIST:
				{      // Wlan Liste anfordern
					G.conf = COMMAND_REQUEST_WIFI_LIST;
					G.client_nr = num;
					break;
				}

					//------------------------------------------------------------------------------

				default:
					break;
			}
		}
        case WStype_BIN: {
            Serial.printf("[%u] get binary lenght: %u\n", num, lenght);
            hexdump(payload, lenght);
            //--echo data back to browser
            //webSocket.sendBIN(num, payload, lenght);
            break;
        }
        default:
            break;
    }
}

