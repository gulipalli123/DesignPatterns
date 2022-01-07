#include<iostream>
using namespace std;
class Test {
public:
	int a = 10;
	
	friend ostream& operator<<(ostream& obj, Test t)
	{
		obj << t.a;
		return obj;
	}
	void operator++()
	{
		a++;
	}
};

int main()
{
	Test t;
	std::cout << t;
	++t;
	std::cout << t;
}