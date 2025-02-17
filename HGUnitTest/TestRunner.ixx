export module TestRunner;
import <memory>;
import TestObject;


export class TestRunner : public TestObject {
public:
	TestRunner() : TestObject("", TestTypes::Runner) {}
};