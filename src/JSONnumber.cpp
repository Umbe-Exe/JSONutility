#include "JSONarray.h"
#include "JSONobject.h"
#include "JSONpair.h"
#include "JSONstring.h"
#include "JSONnumber.h"
#include <iomanip>
#include <sstream>

Json *JSONnumber::clone() const {
	JSONnumber *clone = new JSONnumber();
	clone->value = value;
	return clone;
}

Json &JSONnumber::putArray(const Json &array) {
	if(&array) value = array.stringify();
	return *this;
}

Json &JSONnumber::putObject(const Json &object) {
	if(&object) value = object.stringify();
	return *this;
}

Json &JSONnumber::putPair(const Json &pair) {
	//if(&pair) value = pair.stringify();
	return *(Json *)0;
}

const std::string &JSONnumber::getKey() const {
	return *(std::string *)0;
}

const std::string &JSONnumber::getString() const {
	return value;
}

Json &JSONnumber::getValue() {
	return *this;
}

Json &JSONnumber::putString(const std::string &string) {
	value = string;
	return *this;
}

Json &JSONnumber::putNumber(const double &n, const uint8_t &precision) {
	if(&precision) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(precision) << n;
		value = stream.str();
	} else value = std::to_string(n);
	return *this;
}

Json &JSONnumber::putNumber(const float &n, const uint8_t &precision) {
	if(&precision) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(precision) << n;
		value = stream.str();
	} else value = std::to_string(n);
	return *this;
}

Json &JSONnumber::putNumber(const uint64_t &n) {
	value = std::to_string(n);
	return *this;
}

Json &JSONnumber::putNumber(const std::string &string) {
	value = string;
	return *this;
}

Json &JSONnumber::operator[](const uint64_t &idx) {
	if(idx == 0) return *this;
	return *(Json *)0;
}

Json &JSONnumber::removeElement(const uint64_t &idx) {
	if(idx == 0) value = "";
	return *this;
}

Json &JSONnumber::operator[](const std::string &key) {
	return *this;
}

Json &JSONnumber::removeElement(const std::string &key) {
	return *this;
}

std::string JSONnumber::stringify() const {
	return value;
}

std::string JSONnumber::prettyPrint(const uint64_t &level) const {
	std::string space(level, ' ');
	return space + value;
}

uint64_t JSONnumber::count() const {
	return 1;
}

Json *JSONnumber::decompose(const std::string &json, uint64_t &pos) {
	size_t start = pos;
	do
		if(std::isspace(json[pos]) or json[pos] == ',' or json[pos] == '}' or json[pos] == ']') {
			JSONnumber *str = new JSONnumber();
			str->putString(json.substr(start, pos - start));
			return str;
		}
	while(++pos < json.size());
	return nullptr;
}
