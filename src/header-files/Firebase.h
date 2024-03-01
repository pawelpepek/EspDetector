#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <queue>

#define PORT 443

enum FirebaseState
{
	Ready,
	Sending
};

class Firebase
{
	public:
		Firebase();
		FirebaseState manageState();
		void post(unsigned long value);

	private:
		std::queue<int> _valuesToSend;
		FirebaseState _state;
		String _host;
		WiFiClientSecure _httpsClient;
		unsigned long _startTime;

		void sendIfNotEmpty();
		void send();
		bool isTimeElapsed();
		bool is200OK(String str);
};