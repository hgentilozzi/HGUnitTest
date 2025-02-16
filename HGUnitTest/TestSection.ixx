export module TestSection;

import <string>;
import TestObject;

export class TestSection : public TestObject {
public:
	TestSection(std::string name, TestObject* parent) : TestObject(name, TestTypes::Section,parent) {}
};