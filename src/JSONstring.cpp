#include "JSONarray.h"
#include "JSONobject.h"
#include "JSONpair.h"
#include "JSONstring.h"
#include "JSONnumber.h"
#include <iomanip>
#include <sstream>

Json *JSONstring::clone() const {
	JSONstring *clone = new JSONstring();
	clone->value = value;
	return clone;
}

Json &JSONstring::putArray(const Json &array) {
    if(&array) putObject(array);
    return *this;
}

Json &JSONstring::putObject(const Json &object) {
    if(&object) {
        std::string s = object.stringify();
        std::size_t pos = 0;
        std::size_t prevPos;

        value.reserve(s.size());

        while(true) {
            prevPos = pos;
            pos = s.find("\"", pos);
            if(pos == std::string::npos)
                break;
            value.append(s, prevPos, pos - prevPos);
            value += "\\\"";
            pos += 1;
        }
        value.append(s, prevPos, s.size() - prevPos);
    }
    return *this;
}

Json &JSONstring::putPair(const Json &pair) {
    if(&pair) putObject(pair);
    return *this;
}

const std::string &JSONstring::getKey() const {
    return *(std::string *)0;
}

const std::string &JSONstring::getString() const {
    return value;
}

Json &JSONstring::getValue() {
    return *this;
}

Json &JSONstring::putString(const std::string &string) {
    value = string;
    return *this;
}

Json &JSONstring::putNumber(const double &n, const uint8_t &precision) {
    if(&precision) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << n;
        value = stream.str();
    } else value = std::to_string(n);
    return *this;
}

Json &JSONstring::putNumber(const float &n, const uint8_t &precision) {
    if(&precision) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << n;
        value = stream.str();
    } else value = std::to_string(n);
    return *this;
}

Json &JSONstring::putNumber(const uint64_t &n) {
    value = std::to_string(n);
    return *this;
}

Json &JSONstring::putNumber(const std::string &string) {
    value = string;
    return *this;
}

Json &JSONstring::operator[](const uint64_t &idx) {
    if(idx == 0) return *this;
    return *(Json *)0;
}

Json &JSONstring::removeElement(const uint64_t &idx) {
    if(idx == 0) value = "";
    return *this;
}

Json &JSONstring::operator[](const std::string &key) {
    return *(Json *)0;
}

Json &JSONstring::removeElement(const std::string &key) {
    return *(Json *)0;
}

std::string JSONstring::stringify() const {
	return "\"" + value + "\"";
}

std::string JSONstring::prettyPrint(const uint64_t &level) const {
    std::string space(level, ' ');
    return space + "\"" + value + "\"";
}

uint64_t JSONstring::count() const {
	return 1;
}

Json *JSONstring::decompose(const std::string &json, uint64_t &pos) {
    size_t start = pos;
    while(++pos < json.size())
        if(json[pos] == '"' and json[pos - 1] != '\\') {
            JSONstring *str = new JSONstring();
            str->putString(json.substr(start + 1, pos - 1 - start));
            return str;
        }
    return nullptr;
}
