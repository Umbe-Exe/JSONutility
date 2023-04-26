#include "JSONarray.h"
#include "JSONobject.h"
#include "JSONpair.h"
#include "JSONstring.h"
#include "JSONnumber.h"

JSONpair::~JSONpair() {
	if(m_value) delete m_value;
}

Json *JSONpair::clone() const {
	JSONpair *clone = new JSONpair();

	clone->m_key = m_key;
	if(m_value) clone->m_value = m_value->clone();

	return clone;
}

Json &JSONpair::putArray(const Json &array) {
	Json *clone;

	if(&array) clone = array.clone();
	else clone = new JSONarray();

	if(m_value) delete m_value;
	m_value = clone;

	return *clone;
}

Json &JSONpair::putObject(const Json &object) {
	Json *clone;

	if(&object) clone = object.clone();
	else clone = new JSONobject();

	if(m_value) delete m_value;
	m_value = clone;

	return *clone;
}

Json &JSONpair::putPair(const Json &pair) {
	Json *clone;

	if(&pair) clone = pair.clone();
	else clone = new JSONpair();

	m_value = clone;

	return *clone;
}

const std::string &JSONpair::getKey() const {
	return m_key;
}

const std::string &JSONpair::getString() const {
	if(m_value) return m_value->getString();
	return *(std::string *)0;
}

Json &JSONpair::getValue() {
	return *m_value;
}

void JSONpair::setKey(const std::string key) {
	m_key = key;
}

void JSONpair::setValue(const Json &value) {
	if(!&value) m_value = nullptr;
	else m_value = value.clone();
}

Json &JSONpair::putString(const std::string &string) {
	if(m_value) delete m_value;

	JSONstring *str = new JSONstring();

	str->putString(string);

	m_value = str;

	return *str;
}

Json &JSONpair::putNumber(const double &n, const uint8_t &precision) {
	if(m_value) delete m_value;

	JSONnumber *num = new JSONnumber();

	num->putNumber(n, precision);

	m_value = num;

	return *num;
}

Json &JSONpair::putNumber(const float &n, const uint8_t &precision) {
	if(m_value) delete m_value;

	JSONnumber *num = new JSONnumber();

	num->putNumber(n, precision);

	m_value = num;

	return *num;
}

Json &JSONpair::putNumber(const uint64_t &n) {
	if(m_value) delete m_value;

	JSONnumber *num = new JSONnumber();

	num->putNumber(n);

	m_value = num;

	return *num;
}

Json &JSONpair::putNumber(const std::string &string) {
	if(m_value) delete m_value;

	JSONnumber *num = new JSONnumber();

	num->putNumber(string);

	m_value = num;

	return *num;
}

Json &JSONpair::operator[](const uint64_t &idx) {
	if(idx == 0) return *m_value;
	return *(Json *)0;
}

Json &JSONpair::removeElement(const uint64_t &idx) {
	if(idx == 0 and m_value) {
		delete m_value;
		m_value = nullptr;
	} return *this;
}

Json &JSONpair::operator[](const std::string &key) {
	if(key == m_key) return *m_value;
	return *(Json *)0;
}

Json &JSONpair::removeElement(const std::string &key) {
	if(key == m_key and m_value) {
		delete m_value;
		m_value = nullptr;
	} return *this;
}

std::string JSONpair::stringify() const {
	return "\"" + m_key + "\":" + (m_value ? m_value->stringify() : "");
}

std::string JSONpair::prettyPrint(const uint64_t &level) const {
	std::string space(level, ' ');
	return space + "\"" + m_key + "\" :\n" + (m_value ? m_value->prettyPrint(level + m_key.size() + 5) : "");
}

uint64_t JSONpair::count() const {
	return 1;
}

Json *JSONpair::decompose(const std::string &json, uint64_t &pos) {
	size_t start = pos;
	while(++pos < json.size())
		if(json[pos] == '"' and json[pos - 1] != '\\') {
			JSONpair *pair = new JSONpair();
			pair->m_key = json.substr(start + 1, pos - 1 - start);

			while(++pos < json.size())
				if(!std::isspace(json[pos])) break;

			if(json[pos] == ':') pair->m_value = Json::decompose(json, ++pos);

			return pair;
		}
	return nullptr;
}
