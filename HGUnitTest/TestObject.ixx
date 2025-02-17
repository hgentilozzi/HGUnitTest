export module TestObject;
import <string>;
import <vector>;
import <print>;
import <chrono>;
import <memory>;

using namespace std::chrono;
export class TestObject {
public:

	enum TestTypes { Section, Unit, Suite, Runner};
	TestObject() = default;

	TestObject(std::string name, TestTypes type, TestObject* parent=nullptr)
		: m_Name(name) , m_Type(type), m_NumFails(0), m_Parent(parent)
	{
		m_NumTests = 0;
		m_NumFails = 0;

		if (m_Parent != nullptr)
			m_Parent->addTest(this);
	}

	virtual ~TestObject() = default;

	void run(int level = 0) {

		m_Level = level;
		auto beg = high_resolution_clock::now();
		
		std::printf("%*s%s:%s Begin\n", level, "", Type2Name().c_str(), m_Name.c_str());

		if (m_Type == Section) {
			m_NumTests = 1;
			beforeTest();
			runTest(level+1);
			afterTest();
		}	
		
		for (auto& tu : m_SubTests) {
			tu->beforeTest();
			tu->run(level + 1);
			tu->afterTest();
			m_NumFails += tu->numFails();
			m_NumTests += (int) tu->numTests();
		}

		auto end = high_resolution_clock::now();
		std::chrono::duration<float> dur = end - beg;

		std::printf("%*s%s:%s End. #Test=%d #Fails=%d Elp=%fs\n", 
			level, "", Type2Name().c_str(), m_Name.c_str(), m_NumTests, m_NumFails, dur.count());
	}

	void addTest(TestObject* to) {
		m_SubTests.push_back(to);
	}

	auto numTests() {
		return m_NumTests;
	}
	auto numFails() {
		return m_NumFails;
	}

	std::string& getName() { return m_Name; }

	//TestObject* getParent() {
	//	return m_Parent;
	//}

	//void setParent(TestObject* parent) {
	//	m_Parent = parent;
	//}

	// virtuals
	virtual void beforeTest() {};
	virtual void runTest(int level) {};
	virtual void afterTest() {};

	template<class T>
	void Assert(bool v, T was, T expected, const char* opmsg, int sub_unit = 0) {
		if (!v) {
			
			std::printf("%*s%s(%d) failed. ",m_Level + 1, "", m_Name.c_str(), sub_unit);
			std::print("{} {} {}\n", was, opmsg, expected);

			m_NumFails++;
		}
	};

	template<class T>
	void AssertEquals(T was, T expected, int sub_unit = 0) {
		Assert<T>(was == expected, was, expected, "=", sub_unit);
	};
	template<class T>
	void AssertNotEquals(T was, T expected, int sub_unit = 0) {
		Assert<T>(was != expected, was, expected, "!=", sub_unit);
	};
	template<class T>
	void AssertLess(T was, T expected, int sub_unit = 0) {
		Assert<T>(was < expected, was, expected, "<", sub_unit);
	};
	template<class T>
	void AssertLessEqual(T was, T expected, int sub_unit = 0) {
		Assert<T>(was <= expected, was, expected, "<=", sub_unit);
	};
	template<class T>
	void AssertMore(T was, T expected,int sub_unit = 0) {
		Assert<T>(was > expected, was, expected, ">", sub_unit);
	};
	template<class T>
	void AssertMoreEqual(T was, T expected, int sub_unit = 0) {
		Assert<T>(was >= expected, was, expected, "<more or equal than>=", sub_unit);
	};

protected:
	std::string m_Name;
	TestTypes   m_Type;
	int m_NumTests;
	int m_NumFails;
	int m_Level;
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

