export module TestRunner;
import TestObject;

export class TestRunner : public TestObject {
public:
	TestRunner() : TestObject("",TestTypes::Runner) {}
};