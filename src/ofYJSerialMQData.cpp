#include "ofYJSerialMQData.h"

ofYJSerialMQData::ofYJSerialMQData():msg(""), counter(0) {
}


void ofYJSerialMQData::setMsg(const std::string msg) {
    this->msg = msg;
    counter++;
}


const std::string& ofYJSerialMQData::getMsg() const {
    return this->msg;
}

const int& ofYJSerialMQData::getCounter() const {
    return counter;
}

void ofYJSerialMQData::clear() {
    counter = 0;
    msg = "";
}
