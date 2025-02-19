import TestObject;
import <memory>;

class TSec1 : public TestSection {
public:
	TSec1() : TestSection(__func__) {}

	void runTest(int level) override {
		AssertLess<float>(1.25, 1.25, 1);
	}
};

class Tu1 : public TestUnit {
public:
	Tu1() : TestUnit(__func__, { new TSec1 }) {}
};

class Tu2 : public TestUnit {
public:
	Tu2() : TestUnit(__func__, { new TSec2 }) {}

	class TSec2 : public TestSection {
	public:
		TSec2() : TestSection(__func__) {}

		void runTest(int level) override {
			m_NumFails = 2;
		}
	};
};

class TSuite : public TestSuite {
public:
	TSuite() : TestSuite(__func__, { new Tu1 ,new Tu2 }) {}
};

int main() {
	TestRunner tr({ new TSuite });
	tr.run();

	return 0;
}