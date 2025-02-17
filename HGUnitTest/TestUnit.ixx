export module TestUnit;
import <memory>;
import <string>;
import TestObject;

export class TestUnit : public TestObject {
public:
	TestUnit(std::string name, TestObject* parent) : TestObject(name, TestTypes::Unit,parent) {}
};