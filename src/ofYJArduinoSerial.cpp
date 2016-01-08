#include "ofYJArduinoSerial.h"
#include <sstream>
#include <iostream>
#include <istream>

ofYJArduinoSerial::ofYJArduinoSerial():mConnectId(0), mBaud(9600), mReceivedString(""), mReceivedMsgSep("\n"), mSendMsgSep("\n") {
    mDeviceList = getDeviceList();
}

ofYJArduinoSerial::~ofYJArduinoSerial() {
    waitForThread(true);
}

void ofYJArduinoSerial::listDevices() {
    for (ofSerialDeviceInfo device : mDeviceList) {
        std::cout << "--------" << std::endl;
        std::cout << "Device ID: " << device.getDeviceID() << std::endl;
        std::cout << "Device Name: " << device.getDeviceName() << std::endl;
        std::cout << "Device Path: " << device.getDevicePath() << std::endl;
    }
}


bool ofYJArduinoSerial::connect() {
    bool result = setup(mConnectId, mBaud);
    // startThread(); 
    return result;
}

void ofYJArduinoSerial::threadedFunction() {
    // start
    while (isThreadRunning()) {
        if (lock()) {
            getMsgs();
            unlock();
        }
    }
}

std::map<std::string, ofYJSerialMQData> ofYJArduinoSerial::getMsgs() {
    char serialByte = 0;
    std::string logString = "";

    // getting all the bytes in the queue
    // append it to mReceivedString
    while (available() > 0) {
        serialByte = readByte();
        if (serialByte > 1) {
            mReceivedString += serialByte;
        }
    }
    // get msg size
    // std::istringstream f(mReceivedString);
    // std::string s;
    // while(getline(f, s,'\n')) {
    //     std::cout << s << std::endl;
    // }    

    // get one command per cycle
    std::size_t seperate = mReceivedString.find(mReceivedMsgSep, 0);
    while (seperate != string::npos) {
        logString = mReceivedString.substr(0, seperate);
        mReceivedString = mReceivedString.substr(seperate + 1);
        //std::cout << "Received Queue: " << receivedString << std::endl;
        // cout << "logString: " << logString << endl;
        // split string
        std::size_t seperate2 = logString.find(" ", 0);
        std::string cmd;
        std::string content;
        if (seperate2 != string::npos) {
            cmd = logString.substr(0, seperate2);
            content = logString.substr(seperate2 + 1);

            // std::cout << "THREAD:" << cmd << ":" << content << std::endl;
        
            // update map
            std::map<std::string, ofYJSerialMQData>::iterator lb = msgQueue.lower_bound(cmd);
            if (lb != msgQueue.end() && !(msgQueue.key_comp()(cmd, lb->first))) {
                // key already exist
                lb->second.setMsg(content);
            } else {
                ofYJSerialMQData data = ofYJSerialMQData();
                data.setMsg(content);
                msgQueue.insert(lb, std::map<std::string, ofYJSerialMQData>::value_type(cmd, data));
            }
        }
        seperate = mReceivedString.find(mReceivedMsgSep, 0);
    }
    
    // static int currentCounter = -1;
    //
    // ofYJSerialMQData data = getValue("cmd1");
    // if (data.getCounter() != currentCounter) {
    //     std::cout << "cmd1: " << data.getMsg() << std::endl;
    //     currentCounter = data.getCounter();
    // }

    return msgQueue;
}


ofYJSerialMQData ofYJArduinoSerial::getData(std::string key) {
    std::map<std::string, ofYJSerialMQData>::const_iterator pos = msgQueue.find(key);
    if (pos == msgQueue.end()) {
        return ofYJSerialMQData();
    } else {
        return pos->second;
    }
}

std::string ofYJArduinoSerial::getValue(std::string key) {
    ofYJSerialMQData data;
    if (lock()) {
        data = getData(key);
        unlock();
    }
    return data.getMsg();
}

int ofYJArduinoSerial::getCounter(std::string key) {
    ofYJSerialMQData data;
    if (lock()) {
        data= getData(key);
        unlock();
    }
    return data.getCounter();
}

void ofYJArduinoSerial::sendMsg(std::string msg) {
    msg += mSendMsgSep;
    unsigned char* msguc = new unsigned char[msg.size()];
    memcpy(msguc, msg.c_str(), msg.size());
    writeBytes(msguc, msg.size());
    delete [] msguc;
}

void ofYJArduinoSerial::clear() {
    mReceivedString = "";
}



//  Getter / Setter

void ofYJArduinoSerial::setConnectId(int id) {
    mConnectId = id;
}

int ofYJArduinoSerial::getConnectId() {
    return mConnectId;
}

void ofYJArduinoSerial::setBaudRate(int rate) {
    mBaud = rate;
}

int ofYJArduinoSerial::getBaudRate() {
    return mBaud;
}

void ofYJArduinoSerial::setReceivedMsgSep(std::string sep) {
    mReceivedMsgSep = sep;
}

std::string ofYJArduinoSerial::getReceivedMsgSep() {
    return mReceivedMsgSep;
}

void ofYJArduinoSerial::setSendMsgSep(std::string sep) {
    mSendMsgSep = sep;
}

std::string ofYJArduinoSerial::getSendMsgSep() {
    return mSendMsgSep;
}

