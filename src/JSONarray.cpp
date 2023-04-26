#include "JSONarray.h"
#include "JSONobject.h"
#include "JSONpair.h"
#include "JSONstring.h"
#include "JSONnumber.h"

JSONarray::~JSONarray() {
	for(Json *element : list) delete element;
}

Json *JSONarray::clone() const {
	JSONarray *clone = new JSONarray();

	for(Json *element : list) clone->list.push_back(element->clone());

	return clone;
}

Json &JSONarray::putArray(const Json &array) {
	Json *clone;

	if(&array) clone = array.clone();
	else clone = new JSONarray();

	list.push_back(clone);

	return *clone;
}

Json &JSONarray::putObject(const Json &object) {
	Json *clone;

	if(&object) clone = object.clone();
	else clone = new JSONobject();

	list.push_back(clone);

	return *clone;
}

Json &JSONarray::putPair(const Json &pair) {
	Json *clone;

	if(&pair) clone = pair.clone();
	else clone = new JSONpair();

	list.push_back(clone);

	return *clone;
}

const std::string &JSONarray::getKey() const {
	return *(std::string *)0;
}

const std::string &JSONarray::getString() const {
	return *(std::string *)0;
}

Json &JSONarray::getValue() {
	return *this;
}

Json &JSONarray::putString(const std::string &string) {
	JSONstring *str = new JSONstring();

	str->putString(string);

	list.push_back(str);

	return *str;
}

Json &JSONarray::putNumber(const double &n, const uint8_t &precision) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(n, precision);

	list.push_back(num);

	return *num;
}

Json &JSONarray::putNumber(const float &n, const uint8_t &precision) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(n, precision);

	list.push_back(num);

	return *num;
}

Json &JSONarray::putNumber(const uint64_t &n) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(n);

	list.push_back(num);

	return *num;
}

Json &JSONarray::putNumber(const std::string &string) {
	JSONnumber *num = new JSONnumber();

	num->putNumber(string);

	list.push_back(num);

	return *num;
}

Json &JSONarray::operator[](const uint64_t &idx) {
	if(idx >= 0 and idx < list.size()) return *list[idx];
	return *(Json *)0;
}

Json &JSONarray::removeElement(const uint64_t &idx) {
	if(idx >= 0 and idx < list.size()) {
		delete list[idx];
		list.erase(list.begin() + idx);
	}
	return *this;
}

Json &JSONarray::operator[](const std::string &key) {
	for(Json *element : list) if(element->getKey() == key) return *element;
	return *(Json *)0;
}

Json &JSONarray::removeElement(const std::string &key) {
	for(uint64_t i = 0; i < list.size(); ++i) if(list[i]->getKey() == key) {
		delete list[i];
		list.erase(list.begin() + i);
	}
	return *this;
}

std::string JSONarray::stringify() const {
	std::string result = "[";

	if(list.size()) {
		for(Json *element : list) result += element->stringify() + ',';
		result.back() = ']';
	} else result += ']';

	return result;
}

std::string JSONarray::prettyPrint(const uint64_t &level) const {
	std::string space(level, ' ');
	std::string result = space + '[';

	if(list.size()) {
		for(Json *element : list) result += '\n' + element->prettyPrint(level + 4) + ',';
		result.back() = '\n';
		result += space + ']';
	} else result += ']';

	return result;
}

uint64_t JSONarray::count() const {
	return list.size();
}

Json *JSONarray::decompose(const std::string &json, uint64_t &pos) {
	Json *what = nullptr;
	bool wasComma = false;
	JSONarray *array = new JSONarray();

	while(++pos < json.size()) {
		if(!std::isspace(json[pos])) {

			if(json[pos] == ']') {
				if(wasComma) array->list.push_back(new Json());
				return array;
			} else if(json[pos] == ',') {
				wasComma = true;
				if(!what) array->list.push_back(new Json());
			}

			what = nullptr;
			what = Json::decompose(json, pos);
			if(what) {
				array->list.push_back(what);
				wasComma = false;
			}
		}
	}
	delete array;
	return nullptr;
}
