class Detector
{
    public:
        Detector(int pin, int pinPower);
        void setup();
        void switchPower(bool power);
        bool detect();

    private:
        bool _lastDetection;
        int _pin;
        int _pinPower;
        bool _detected;
};