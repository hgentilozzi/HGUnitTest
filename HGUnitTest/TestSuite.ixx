export module TestSuite;
import <memory>;
import <string>;
import TestObject;

export class TestSuite : public TestObject {
public:
	TestSuite(std::string name, TestObject* parent) : TestObject(name, TestTypes::Suite,parent) {}
};