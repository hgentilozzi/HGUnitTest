import TestRunner;
import TestUnit;
import TestSuite;
import TestSection;
import <memory>;

class TSec1 : public TestSection {
public:
	TSec1(TestObject* parent) : TestSection(__func__, parent) {}

	void runTest(int level) override {
		AssertLess<float>(1.25, 1.25, 1);
	}
};

class Tu1 : public TestUnit {
public:
	Tu1(TestObject* parent) : TestUnit(__func__,parent) {
		new TSec1(this);
	}
};

class Tu2 : public TestUnit {
public:
	Tu2(TestObject* parent) : TestUnit(__func__,parent) {
		new TSec2(this);
	}

	class TSec2 : public TestSection {
	public:
		TSec2(TestObject* parent) : TestSection(__func__, parent) {}

		void runTest(int level) override {
			m_NumFails = 2;
		}
	};
};

class TSuite : public TestSuite {
public:
	TSuite(TestObject* parent) : TestSuite(__func__,parent) {
		new Tu1(this);
		new Tu2(this);
	}
};

int main() {
	TestRunner tr;
	new TSuite(&tr);
	tr.run();

	return 0;
}