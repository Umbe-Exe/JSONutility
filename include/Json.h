#pragma once
#include <string>

#ifndef JSON_STATIC
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT
#endif

class Json {

public:
	Json();
	Json(const Json &json);
	Json(const std::string &json);
	Json &operator=(const Json &json);
	virtual Json &putArray(const Json &array = *(Json *)0);
	virtual Json &putObject(const Json &object = *(Json *)0);
	virtual Json &putPair(const Json &pair = *(Json *)0);
	virtual void setKey(const std::string key);
	virtual void setValue(const Json &value = *(Json *)0);
	virtual const std::string &getKey() const;
	virtual const std::string &getString() const;
	virtual Json &getValue();
	virtual Json &putString(const std::string &string);
	virtual Json &putNumber(const double &n, const uint8_t &precision = *(uint8_t *)0);
	virtual Json &putNumber(const float &n, const uint8_t &precision = *(uint8_t *)0);
	virtual Json &putNumber(const uint64_t &n);
	virtual Json &putNumber(const std::string &string);
	virtual Json &operator[](const uint64_t &idx);
	virtual Json &removeElement(const uint64_t &idx = 0);
	virtual Json &operator[](const std::string &key);
	virtual Json &removeElement(const std::string &key);
	virtual std::string stringify() const;
	virtual std::string prettyPrint(const uint64_t &level = 0) const;
	virtual uint64_t count() const;
	void clear();
	~Json();

private:
	Json *content;
	virtual Json *clone() const;
	static Json *decompose(const std::string &json, uint64_t &pos);
	friend class JSONstring;
	friend class JSONnumber;
	friend class JSONpair;
	friend class JSONarray;
	friend class JSONobject;
};
