// Singleton pattern - It ensures that a class has only one instance and provides a global point of access
// to it.
// Singleton class may give more than one object if it is used in multithreading environment, suppose thread1
// executed the statement if (unique_instance == nullptr) and now context switching happened, thread2 started
// executing if (unique_instance == nullptr) and unique_instance = new Singleton() and got the object, then
// context switching happened again and thread1 took the control and resumed at unique_instance =
// new Singleton() which means thread1 created another object of our singleton class.
//
// This problem can be solved using 3 mechanisms:
// 1. using synchronization/mutex protection to the getInstance() code but it can decrease the performance
// of your code.So do nothing if performance of getInstance() is not critical to your application.
// 2. Move to an eagerly created instance rather than a lazily created one.
//  private:
//		static Singleton* unique_instance = Singleton();
//		Singleton() { }
//  public:
//		Singleton* getInstance()
//		{
//			return unique_instance; //we have already got an instance so just return it.
//		}
// 3. Use double-checked locking to reduce the use of synchronization in getInstance()
// private:
//		volatile static Singleton* unique_instance;
//		Singleton() {}
//public:
// static Singleton* getInstance()
// {
//	 if(unique_instance == nullptr)
//		mtx.lock();
//		if(unique_instance == nullptr)
//		{
//			unique_instance = new Singleton();
//		}
//		mtx.unlock();
//	return unique_instance;
//	Singleton is not following the SingleResponsibility Principle.
//	Singleton is not only responsible for managing its one instance(and providing its global access),
//	it is also responsible for whatever its main role is in the application. It is certainly not hard to
//	see that there is an utility in a class managing its own instance; it certainly makes the overall
//	design simpler.
//	You cannot subclass a singleton class, because its constructor is private. You cannot extend a class
//	with private constructor. So you have to move the contructor to protected or public, and hence
//	it is really no more a singleton class as other classes can instantiate it.
#include<iostream>

class Singleton
{
private:
	static Singleton* unique_instance;
	int i = 0;
	Singleton() {}
public:
	static Singleton* getInstance()
	{
		if (unique_instance == nullptr)
			unique_instance = new Singleton();
		return unique_instance;
	}
	void print()
	{
		i++;
		std::cout << i << "\n";
	}
};

Singleton* Singleton::unique_instance = nullptr;
/*int main()
{
	Singleton* obj1 = Singleton::getInstance();
	obj1->print();
	Singleton* obj2 = Singleton::getInstance();
	obj2->print();
}*/