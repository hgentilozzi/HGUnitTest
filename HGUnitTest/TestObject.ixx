export module TestObject;
import <string>;
import <vector>;
import <print>;
import <chrono>;


using namespace std::chrono;

export class TestObject {
public:

	enum TestTypes { Section, Unit, Suite, Runner};
	TestObject(std::string name, TestTypes type, TestObject* parent=nullptr)
		: m_Name(name) , m_Type(type), m_NumFails(0), m_Parent(parent)
	{
		if (m_Parent != nullptr)
			m_Parent->addTest(this);
	}

	virtual ~TestObject() = default;

	void run(int level = 0) {
		int totalTests = 0;
		int totalFails = 0;
		auto beg = high_resolution_clock::now();
		
		std::printf("%*s%s:%s Begin\n", level, "", Type2Name().c_str(), m_Name.c_str());

		if (m_Type == Section) {
			totalTests = 1;
			beforeTest();
			runTest(level+1);
			afterTest();
			totalFails = m_NumFails;
		}	
		
		for (auto& tu : m_SubTests) {
			tu->beforeTest();
			tu->run(level + 1);
			tu->afterTest();
			totalFails += tu->numFails();
			totalTests += (int) tu->numTests();
		}

		auto end = high_resolution_clock::now();
		std::chrono::duration<float> dur = end - beg;

		std::printf("%*s%s:%s End. #Test=%d #Fails=%d Elp=%fs\n", 
			level, "", Type2Name().c_str(), m_Name.c_str(), totalTests, totalFails, dur.count());
	}

	void addTest(TestObject* to) {
		m_SubTests.push_back(to);
	}

	auto numTests() {
		return (m_Type == Section)? 1 : m_SubTests.size();
	}
	auto numFails() {
		return m_NumFails;
	}

	std::string& getName() { return m_Name; }

	TestObject* getParent() {
		return m_Parent;
	}

	void setParent(TestObject* parent) {
		m_Parent = parent;
	}

	// virtuals
	virtual void beforeTest() {};
	virtual void runTest(int level) {};
	virtual void afterTest() {};

protected:
	std::string m_Name;
	TestTypes   m_Type;
	int m_NumFails;
	TestObject* m_Parent;
	std::vector<TestObject*> m_SubTests;

	const std::string Type2Name() const {
		switch (m_Type) {
		case Section:
			return "Section";
		case Unit:
			return "Unit";
		case Suite:
			return "Suite";
		case Runner:
			return "Runner";
		}

		return "Invalid";
	}
};

