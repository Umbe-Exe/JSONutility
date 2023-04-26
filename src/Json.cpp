#include "json.h"
#include "JSONarray.h"
#include "JSONobject.h"
#include "JSONpair.h"
#include "JSONstring.h"
#include "JSONnumber.h"

Json::Json() {
	content = nullptr;
}

Json::Json(const Json &json) {
	content = json.clone();
}

Json &Json::operator=(const Json &json) {
	if(content) delete content;
	content = json.clone();
	return *this;
}

Json *Json::clone() const {
	return content ? content->clone() : new Json();
}

Json &Json::putArray(const Json &array) {
	if(!content) content = &array ? array.clone() : new JSONarray();
	else return content->putArray(array);

	return *content;
}

Json &Json::putObject(const Json &object) {
	if(!content) content = &object ? object.clone() : new JSONobject();
	else return content->putObject(object);

	return *content;
}

Json &Json::putPair(const Json &pair) {
	if(!content) content = &pair ? pair.clone() : new JSONpair();
	else return content->putPair(pair);

	return *content;
}

void Json::setKey(const std::string key) {
	if(!content) putPair();
	content->setKey(key);
}

void Json::setValue(const Json &value) {
	if(!content) putPair();
	content->setValue(value);
}

const std::string &Json::getKey() const {
	if(content) return content->getString();
	return *(std::string *)0;
}

const std::string &Json::getString() const {
	if(content) return content->getString();
	return *(std::string *)0;
}

Json &Json::getValue() {
	if(content) return content->getValue();
	return *(Json *)0;
}

Json &Json::putString(const std::string &string) {
	if(!content) content = new JSONstring();

	content->putString(string);

	return *content;
}

Json &Json::putNumber(const double &n, const uint8_t &precision) {
	if(!content) content = new JSONnumber();

	content->putNumber(n, precision);

	return *content;
}

Json &Json::putNumber(const float &n, const uint8_t &precision) {
	if(!content) content = new JSONnumber();

	content->putNumber(n, precision);

	return *content;
}

Json &Json::putNumber(const uint64_t &n) {
	if(!content) content = new JSONnumber();

	content->putNumber(n);

	return *content;
}

Json &Json::putNumber(const std::string &string) {
	if(!content) content = new JSONnumber();

	content->putNumber(string);

	return *content;
}

Json &Json::operator[](const uint64_t &idx) {
	if(content) return (*content)[idx];
	return *(Json *)0;
}

Json &Json::removeElement(const uint64_t &idx) {
	if(content) content->removeElement(idx);
	return *this;
}

Json &Json::operator[](const std::string &key) {
	if(content) return (*content)[key];
	return *(Json *)0;
}

Json &Json::removeElement(const std::string &key) {
	if(content) content->removeElement(key);
	return *this;
}

std::string Json::stringify() const {
	return (content ? content->stringify() : "");
}

std::string Json::prettyPrint(const uint64_t &level) const {
	return content ? content->prettyPrint() : "";
}

uint64_t Json::count() const {
	return content ? content->count() : -1;
}

void Json::clear() {
	if(content) {
		delete content;
		content = nullptr;
	}
}

Json::~Json() {
	if(content)	delete content;
}

bool isKeyString(const std::string &json, uint64_t pos) {

	while(++pos < json.size()) {
		if(json[pos] == '"' and json[pos - 1] != '\\') {
			while(++pos < json.size())
				if(!std::isspace(json[pos]))
					if(json[pos] == ':') return true;
					else return false;
		}
	} return false;
}

Json *Json::decompose(const std::string &json, uint64_t &pos) {

	while(pos < json.size()) {

		if(json[pos] == '"') {
			if(isKeyString(json, pos)) return JSONpair::decompose(json, pos);
			else return JSONstring::decompose(json, pos);
			break;
		} else if(json[pos] == '{') {
			return JSONobject::decompose(json, pos);
			break;
		} else if(json[pos] == '[') {
			return JSONarray::decompose(json, pos);
			break;
		} else if(std::isalnum(json[pos])) {
			return JSONnumber::decompose(json, pos);
			break;
		} else if(json[pos] == ',' or json[pos] == '}' or json[pos] == ']') return nullptr;
		++pos;
	}
	return nullptr;
}

Json::Json(const std::string &json) {
	size_t pos = 0;
	content = Json::decompose(json, pos);
}