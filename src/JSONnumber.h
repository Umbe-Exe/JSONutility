#pragma once
#include "json.h"

class JSONnumber : public Json {

public:
	Json *clone() const override;
	Json &putArray(const Json &array = *(Json *)0) override;
	Json &putObject(const Json &object = *(Json *)0) override;
	Json &putPair(const Json &pair = *(Json *)0) override;
	void setKey(const std::string key) override {};
	void setValue(const Json &value = *(Json *)0) override {};
	const std::string &getKey() const override;
	const std::string &getString() const override;
	Json &getValue() override;
	Json &putString(const std::string &string) override;
	Json &putNumber(const double &n, const uint8_t &precision = *(uint8_t *)0) override;
	Json &putNumber(const float &n, const uint8_t &precision = *(uint8_t *)0) override;
	Json &putNumber(const uint64_t &n) override;
	Json &putNumber(const std::string &string) override;
	Json &operator[](const uint64_t &idx) override;
	Json &removeElement(const uint64_t &idx = 0) override;
	Json &operator[](const std::string &key) override;
	Json &removeElement(const std::string &key) override;
	std::string stringify() const override;
	std::string prettyPrint(const uint64_t &level = 0) const override;
	uint64_t count() const override;
	static Json *decompose(const std::string &json, uint64_t &pos);

private:
	std::string value;
};
