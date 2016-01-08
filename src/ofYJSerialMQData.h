#pragma once
#include <string>

class ofYJSerialMQData {
    public:
        ofYJSerialMQData();
        void setMsg(const std::string msg);
        const std::string& getMsg() const;
        const int& getCounter() const;
        void clear();
        
    private:
        std::string msg;
        int counter;

};
