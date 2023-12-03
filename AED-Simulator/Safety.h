#ifndef SAFETY_H
#define SAFETY_H


class Safety: public Victim{
    public:
        bool runSelfTest();
        bool isCableattached();
        bool isChild(int weight, int age);
        bool isTouching();
        bool isWet();
        bool safeEnvironment();

        //getters and setters
        bool getCablePluggedIn();
        bool getFailed();
        bool getBatteryCharged();
        void setCablePluggedIn(bool cableStatus);
        void setFailed(bool failedStatus);
        void setBatteryCharged(bool batteryStatus);

    private:
        bool cablePluggedIn;
        bool failed;
        bool batteryCharged;
        bool wet;
        bool touching;
        bool safe;
        bool cableAttached;
};

#endif