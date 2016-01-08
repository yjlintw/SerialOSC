#pragma once

#include <map>
#include "ofMain.h"
#include "ofYJSerialMQData.h"
class ofYJArduinoSerial : public ofSerial, public ofThread {

    public:
        ofYJArduinoSerial();
        ~ofYJArduinoSerial();
        void listDevices();
        bool connect();
        std::map<std::string, ofYJSerialMQData> getMsgs();
        void sendMsg(std::string msg);
        void clear();
        
        //  Setter/Getter
        void setConnectId(int id);
        int getConnectId();
        void setBaudRate(int rate);
        int getBaudRate();
        void setReceivedMsgSep(std::string sep);
        std::string getReceivedMsgSep();
        void setSendMsgSep(std::string sep);
        std::string getSendMsgSep();

        ofYJSerialMQData getData(std::string key);
        std::string getValue(std::string key);
        int getCounter(std::string key);

    private:
        std::vector <ofSerialDeviceInfo> mDeviceList;
        void threadedFunction();
        int mConnectId;
        int mBaud;
        std::string mReceivedString;
        std::string mReceivedMsgSep;
        std::string mSendMsgSep;
        std::map<std::string, ofYJSerialMQData> msgQueue;
        
};
