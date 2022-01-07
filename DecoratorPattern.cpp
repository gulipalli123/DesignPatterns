//Lookslike it is more rigid and not following open-closed principle
// Adding Size to the base class is not solving the problem - as the size variable once set is not carrying its
// same behaviour to top objects while wrapping around and hence for top objects Size is always the default value TALL
//While inheritance is powerful, it doesn't always lead to the most flexible or maintainable designs.
// By Dynamically composing objects, I can add new functionality by writing new code rather than altering existing code.
// Because I am not changing existing code, the changes of introducing bugs or causing unintended side effects in existing code
// are much reduced.

// Decorator Pattern - It attaches additional responsibilities to an object dynamically.Decorators provide a flexible alternative
//					   to subclassing for extending functionality.

// DESIGN PRINCIPLE 5 - Classes should be open for extension but closed for modification.

// Concentrate those areas that are most likely to change in your designs and apply the principles there.
// Be careful when choosing the areas of the code that need to be extended; applying the open-closed principle
// everywhere is wasteful and unnecessary, and can lead to complex and hard-to-understand code.

// Design Principle 1 - Identify the aspects of your application that vary and separate them from what stays the same.
//The thing that varies in the observer pattern is the state of the subject and the number and type of observers. With this pattern, you can vary the objects
// that are dependent on the state of the subject without having to change the subject.

// Design Principle 2 - Program to an interface, not an implementation
// Both the subject and observers use interfaces. The subject keeps track of the number of objects implementing the observer interface, while the observers
// register with and get notified by the subject interface. This keeps things nice and loosly coupled   (coupling means dependency from eitherside)

//Design Principle 3 - Favor composition over inheritance
// In this pattern, both subject and observer are linked together by composition at runtime.

//Design Principle 4 - Strive for loosely coupled designs between objects that interact

//Loosly couple designs allow us to build flexible OO systems that can handle change because they minimize the interdependency between objects.


#include<iostream>
#include<string>

class Beverages
{
public:
	enum class Size
	{
		TALL = 0, GRANDE, VENTI
	};
	virtual std::string getDescription()
	{
		return description_;
	}
	virtual double cost() = 0;
	Size GetSize() { return size_; }
	void SetSize(Size size) { size_ = size; }
protected:
	std::string description_ = "Unknown_beverages";
	Size size_ = Size::TALL;
};

/*class BeverageSize : public Beverages
{
	Beverages* beverages_;
public:
	BeverageSize(Beverages* beverages) { beverages_ = beverages; }
	std::string  getDescription()
	{
		switch (beverages_->GetSize())
		{
		case Beverages::Size::TALL:
				return beverages_->getDescription() + " TALL";
		case Beverages::Size::GRANDE:
			return beverages_->getDescription() + " GRANDE";
		case Beverages::Size::VENTI:
			return beverages_->getDescription() + " VENTI";
		default:
			break;
		}
	}
	double cost() { return beverages_->cost(); } //Unnecessary method in this class, so it is not a proper inheritance
};*/

class CondimentsDecorator : public Beverages
{
public:
	Beverages* beverages_ = nullptr;
	virtual std::string getDescription() = 0;
	Size GetSize()
	{
		if (beverages_)
			return beverages_->GetSize();
	}
};

class HouseBlend : public Beverages
{
public:
	HouseBlend()
	{
		description_ = "HouseBlend";
	}
	double cost()
	{
		return 1.23;
	}
};

class Mocha : public CondimentsDecorator
{
private:
	//Beverages* beverages_;
public:
	Mocha(Beverages* beverages)
	{
		beverages_ = beverages;
	}
	std::string getDescription()
	{
		return beverages_->getDescription() + " Mocha";
	}
	double cost()
	{
		switch (beverages_->GetSize())
		{
		case Size::TALL:
			return beverages_->cost() + 0.35;
			//break;
		case Size::GRANDE:
			return beverages_->cost() + 0.35 + 0.15;
			//break;
		case Size::VENTI:
			return beverages_->cost() + 0.35 + 0.15 + 0.20;
			//break;
		default:
			break;
		}
	} 

};

class SteamedMilk : public CondimentsDecorator
{
private:
	//Beverages* beverage_;
public:
	SteamedMilk(Beverages* beverage)
	{
		beverages_ = beverage;
	}
	std::string getDescription()
	{
		return beverages_->getDescription() + " SteamedMilk";
	} 
	double cost()
	{
		return beverages_->cost() + 0.56;
	}
};

int main()
{
	Beverages* houseblend = new HouseBlend();
	std::cout << houseblend->getDescription() << " " << houseblend->cost() << "$" << "\n";
	houseblend->SetSize(Beverages::Size::GRANDE);
	houseblend = new Mocha(houseblend);
	std::cout << houseblend->getDescription() << " " << houseblend->cost() << "$" << "\n";
	houseblend = new SteamedMilk(houseblend);
	std::cout << houseblend->getDescription() << " " << houseblend->cost() << "$" << "\n";
	houseblend = new Mocha(houseblend);
	std::cout << houseblend->getDescription() << " " << houseblend->cost() << "$" << "\n";

}