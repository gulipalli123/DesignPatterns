// DesignPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Why do you want to use inheritance- for code reuse, there can be  a base class, which has methods defining common properties and these can be inherited by sub classes.
// A common issue - once the inherit chain is build up, if you want to add a new method/ property to base class, then you should make sure that it is appropriate for the sub classes also.
// No matter how well you design an application, overtime an application must grow and change or it will die.

// DESIGN PRINCIPLE 1 -  Identify the aspects of your application that vary and separate them from what stays the same.

// Take what varies and "encapsulate" it so that it won't affect the rest of your code. 
// Advantages - Fewer unintended consequences from code changes and more flexibility in your system

//DESIGN PRINCIPLE 2 - Program to an interface, not an implementation.

// Program to an interface really means program to a supertype
// With this we get the benefit of REUSE without all the baggage that comes along with inheritance.
// In an OO system, yes classes represent things that have both state(instance variables) and behaviour(methods)
// In behaviour classes, behaviour is a thing because a behaviour(flying behaviour) can have both state and methods

// Design principles and patterns can be applied at any stage of the development cycle.

// Should we make Duck an interface too ? - Not in this case - Now that we have removed what varies from the Duck inheritance, 
// we get the benefit of this structure without the problems.

//DESIGN PRINCIPLE 3 - Favor composition over inheritance

//Creating systems using composition gives you a lot more flexibility. Notonly it lets you encapsulate a family of algorithms
// into their own set of classes but it lets you change behaviour at runtime

// STRATEGY PATTERN - It defines a family of algorithms, encapsulates each one and makes them interchangable.
// Strategy lets the algorithms vary independently from the clients that use it.

// Knowing concepts like abstraction, inheritance and polymorphism  does not make you a good object-oriented designer.
// A design guru thinks about how to make flexible designs that are maintainable and can cope with change.
// Good OO designs are reusable, extensible and maintainable.
// Patterns are proven object-oriented experience.
// Most patterns and prnciples address issues of change in software.

// Development constant is change.

//Strategy Pattern
#include <iostream>
class FlyBehaviour
{
public:
    virtual void Fly() = 0;
};
class FlyWithWings : public FlyBehaviour
{
public:
    void Fly()
    {
        std::cout << "I can fly with my wings\n";
    }
};

class FlyNoWay : public FlyBehaviour
{
public:
    void Fly()
    {
        std::cout << "I cannot fly\n";
    }
};

class QuackBehaviour
{
public:
    virtual void quack() = 0;
};

class Quack : public QuackBehaviour
{
    void quack()
    {
        std::cout << "quack\n";
    }
};

class MuteQuack : public QuackBehaviour
{
    void quack()
    {
        std::cout << "slience\n";
    }
};
class Duck
{
public:
    Duck() {}
    void performFly()
    {
        fly_behaviour_->Fly();
    }
    void performQuack()
    {
        quack_behaviour_->quack();
    }
    void swim()
    {
        std::cout << "I can swim\n";
    }
    virtual void display() = 0;
    void setFlyBehaviour(FlyBehaviour* fb)
    {
        fly_behaviour_ = fb;
    }
    void setQuackBehaviour(QuackBehaviour* qb)
    {
        quack_behaviour_ = qb;
    }
protected:
    FlyBehaviour* fly_behaviour_ = nullptr;
    QuackBehaviour* quack_behaviour_ = nullptr;
};


class MallardDuck : public Duck
{
public:
    MallardDuck()
    {
        fly_behaviour_ = new FlyWithWings();
        quack_behaviour_ = new Quack();
    }
    void display()
    {
        std::cout << "I am Mallard Duck\n";
    }
};

/*int main()
{
    Duck* mallard = new MallardDuck();
    mallard->display();
    mallard->performFly();
    mallard->performQuack();

    std::cout << "changing behaviour dynamically\n";
    mallard->setFlyBehaviour(new FlyNoWay());
    mallard->setQuackBehaviour(new MuteQuack());
    mallard->performFly();
    mallard->performQuack();
}*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
