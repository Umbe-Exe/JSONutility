#include "JSONarray.h"
#include "JSONobject.h"
#include "JSONpair.h"
#include "JSONstring.h"
#include "JSONnumber.h"

JSONobject::~JSONobject() {
	for(Json *pair : list) delete pair;
}

Json *JSONobject::clone() const {
	JSONobject *clone = new JSONobject();

	for(Json *pair : list) clone->list.push_back(pair->clone());

	return clone;
}

Json &JSONobject::putArray(const Json &array) {
	Json *clone;

	if(&array) clone = array.clone();
	else clone = new JSONarray();

	list.push_back(clone);

	return *clone;
}

Json &JSONobject::putObject(const Json &object) {
	Json *clone;

	if(&object) clone = object.clone();
	else clone = new JSONobject();

	list.push_back(clone);

	return *clone;
}

Json &JSONobject::putPair(const Json &pair) {
	Json *clone;

	if(&pair) clone = pair.clone();
	else clone = new JSONpair();

	list.push_back(clone);

	return *clone;
}

const std::string &JSONobject::getKey() const {
	return *(std::string *)0;
}

const std::string &JSONobject::getString() const {
	return *(std::string *)0;
}

Json &JSONobject::getValue() {
	return *this;
}

Json &JSONobject::putString(const std::string &string) {
	JSONstring *str = new JSONstring();

	str->putString(string);

	list.push_back(str);

	return *str;
}

Json &JSONobject::putNumber(const double &n, const uint8_t &precision) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(n, precision);

	list.push_back(num);

	return *num;
}

Json &JSONobject::putNumber(const float &n, const uint8_t &precision) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(n, precision);

	list.push_back(num);

	return *num;
}

Json &JSONobject::putNumber(const uint64_t &n) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(n);

	list.push_back(num);

	return *num;
}

Json &JSONobject::putNumber(const std::string &string) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(string);

	list.push_back(num);

	return *num;
}

Json &JSONobject::operator[](const uint64_t &idx) {
	if(idx >= 0 and idx < list.size()) return *list[idx];
	return *(Json *)0;
}

Json &JSONobject::removeElement(const uint64_t &idx) {
	if(idx >= 0 and idx < list.size()) {
		delete list[idx];
		list.erase(list.begin() + idx);
	}
	return *this;
}

Json &JSONobject::operator[](const std::string &key) {
	for(Json *element : list) if(element->getKey() == key) return *element;
	return *(Json *)0;
}

Json &JSONobject::removeElement(const std::string &key) {
	for(uint64_t i = 0; i < list.size(); ++i) if(list[i]->getKey() == key) {
		delete list[i];
		list.erase(list.begin() + i);
	}
	return *this;
}

std::string JSONobject::stringify() const {
	std::string result = "{";

	if(list.size()) {
		for(Json *element : list) result += element->stringify() + ',';
		result.back() = '}';
	} else result += '}';

	return result;
}

std::string JSONobject::prettyPrint(const uint64_t &level) const {
	std::string space(level, ' ');
	std::string result = space + '{';

	if(list.size()) {
		for(Json *element : list) result += '\n' + element->prettyPrint(level + 4) + ',';
		result.back() = '\n';
		result += space + '}';
	} else result += '}';
	
	return result;
}

uint64_t JSONobject::count() const {
	return list.size();
}

Json *JSONobject::decompose(const std::string &json, uint64_t &pos) {
	Json *what = nullptr;
	bool wasComma = false;
	JSONobject *obj = new JSONobject();

	while(++pos < json.size()) {
		if(!std::isspace(json[pos])) {

			if(json[pos] == '}') {
				if(wasComma) obj->list.push_back(new Json());
				return obj;
			} else if(json[pos] == ',') {
				wasComma = true;
				if(!what) obj->list.push_back(new Json());
			}

			what = nullptr;
			what = Json::decompose(json, pos);
			if(what) {
				obj->list.push_back(what);
				wasComma = false;
			}
		}
	}
	delete obj;
	return nullptr;
}
