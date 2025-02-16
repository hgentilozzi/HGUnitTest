import TestRunner;
import TestUnit;
import TestSuite;
import TestSection;

class TSec1 : public TestSection {
public:
	TSec1(TestObject* parent) : TestSection(__func__, parent) {}

	void runTest(int level) override {
	}
};



class Tu1 : public TestUnit {
public:
	Tu1(TestObject* parent) : TestUnit(__func__,parent) {}

	void beforeTest() override {
		new TSec1(this);
	}
};

class Tu2 : public TestUnit {
public:
	Tu2(TestObject* parent) : TestUnit(__func__,parent) {}

	class TSec2 : public TestSection {
	public:
		TSec2(TestObject* parent) : TestSection(__func__, parent) {}

		void runTest(int level) override {
			m_NumFails = 2;
		}
	};
	void beforeTest() override {
		new TSec2(this);
	}

};

class TSuite : public TestSuite {
public:
	TSuite(TestObject* parent) : TestSuite(__func__,parent) {}

	void beforeTest() override {
		new Tu1(this);
		new Tu2(this);
	}
};

int main() {

	TestRunner   tr;
	new TSuite(&tr);
	tr.run();

	return 0;
}