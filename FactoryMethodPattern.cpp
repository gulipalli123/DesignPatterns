#include<iostream>
#include<string>
#include<new>
//Factory Method Pattern defines an interface for creating an object, but lets subclasses decide which
//class to instantiate.
//A Factory method handles object creation and encapsulates it in a subclass.This decouples the client code
//in the super class from the object creation code in the subclass.
// A Factory method may be parameterised (or not) to select among several variations of a product
// A Factory method isolates the client code(the code in the super class, like orderPizza()) from knowing
// what kind of concrete product is actually created.
// A Factory method returns a Product which is typically used within the methods defined in superclass
// A Factory method is abstract so that sub classes are counted on to handle object creation
// After applying the Factory method, you will notice that our high-level component, the PizzaStore
// and our low level components, the pizzas both depend on Pizza, the abstraction.
// Factory method is not the only technique to adhere to the Dependency Inversion Principle, but it is one
// of the more powerful ones.
// Guidelines that can help you avoid OO designs that violate the Dependency Inversion Principle
// 1.No variable should hold a reference to a concrete class(If you use new, you will be holding a
// reference to a concrete class, use a factory to get around it
// 2.No class should derive from a concrete class(If you derive from a concrete class, you are depending
// on a concrete class.Derive from an abstraction, like an interface or an abstract class.
// 3.No method should override an implemented method of any of its base classes.(If you override an
// implemented method, then your base class wasn't really an abstraction to start with.Those methods
// implemented in your base class are meant to be shared by all your subclasses.
class Pizza
{
protected:
	std::string name;
	std::string sauce;
	std::string dough;
public:
	virtual void prepare()
	{
		std::cout << "Preparing Pizza\n";
	}
	void bake()
	{
		std::cout << "Baking Pizza\n";
	}
	void cut()
	{
		std::cout << "Cutting Pizza\n";
	}
	void box()
	{
		std::cout << "Put Pizza in a box\n";
	}
	virtual ~Pizza() = default;
};
class NYStyleCheesePizza : public Pizza
{
	void prepare() override
	{
		name = "NY style sauce and cheese pizza";
		dough = "Thin crust dough";
		sauce = "Marinara sauce";
		std::cout << "Prepare " << name << " " << dough << " " << sauce << "\n";
	}
};

class ChicagoStyleCheesePizza : public Pizza
{
	void prepare() override
	{
		name = "Chicago style sauce and cheese pizza";
		dough = "Thick crust dough";
		sauce = "Plum tomato sauce";
		std::cout << "Prepare " << name << " " << dough << " " << sauce << "\n";
	}
};

class PepperoniPizza : public Pizza
{
	void prepare()
	{
		std::cout << "Prepare Pepperoni Pizza\n";
	}
};



class PizzaStore
{
public:
	Pizza* orderPizza(const std::string& pizza_type)
	{
		Pizza* pizza_ = nullptr;
		pizza_ = createPizza(pizza_type);
		if (nullptr != pizza_)
		{
			pizza_->prepare();
			pizza_->bake();
			pizza_->cut();
			pizza_->box();
		}

		return pizza_;
	}
protected:
	virtual Pizza* createPizza(const std::string& pizza_type) = 0;
	~PizzaStore() = default;
};

class NYPizzaStore : public PizzaStore
{
public:
	Pizza* createPizza(const std::string& pizza_type) override
	{
		Pizza* pizza_ = nullptr;
		if (pizza_type == "cheese")
			pizza_ = new(std::nothrow) NYStyleCheesePizza();
		/*else if (pizza_type == "greek")
			pizza_ = new(std::nothrow) GreekPizza();
		else if (pizza_type == "pepperoni")
			pizza_ = new(std::nothrow) PepperoniPizza();*/
		return pizza_;
	}
};

class ChicagoPizzaStore : public PizzaStore
{
public:
	Pizza* createPizza(const std::string& pizza_type) override
	{
		Pizza* pizza_ = nullptr;
		if (pizza_type == "cheese")
			pizza_ = new(std::nothrow) ChicagoStyleCheesePizza();
		/*else if (pizza_type == "greek")
			pizza_ = new(std::nothrow) GreekPizza();
		else if (pizza_type == "pepperoni")
			pizza_ = new(std::nothrow) PepperoniPizza();*/
		return pizza_;
	}
};


/*int main()
{
	PizzaStore* ny_pizza_store = new NYPizzaStore();
	ny_pizza_store->orderPizza("cheese");
	PizzaStore* chicago_pizza_store = new ChicagoPizzaStore();
	chicago_pizza_store->orderPizza("cheese");
	return 0;
}*/