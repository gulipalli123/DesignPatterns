#include<iostream>
#include<string>
#include<new>
class Pizza
{
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
class CheesePizza: public Pizza
{
	void prepare()
	{
		std::cout << "Prepare Cheese Pizza\n";
	}
};

class GreekPizza : public Pizza
{
	void prepare()
	{
		std::cout << "Prepare Greek Pizza\n";
	}
};

class PepperoniPizza : public Pizza
{
	void prepare()
	{
		std::cout << "Prepare Pepperoni Pizza\n";
	}
};

class SimplePizzaFactory
{
public:
	Pizza* createPizza(const std::string& pizza_type)
	{
		Pizza* pizza_ = nullptr;
		if (pizza_type == "cheese")
			pizza_ = new(std::nothrow) CheesePizza();
		else if (pizza_type == "greek")
			pizza_ = new(std::nothrow) GreekPizza();
		else if (pizza_type == "pepperoni")
			pizza_ = new(std::nothrow) PepperoniPizza();
		return pizza_;
	}

};

class PizzaStore
{
	SimplePizzaFactory* factory_;
public:
	PizzaStore(SimplePizzaFactory* factory): factory_(factory)
	{
		
	}
	Pizza* orderPizza(const std::string& pizza_type)
	{
		Pizza* pizza_ = nullptr;
		pizza_ = factory_->createPizza(pizza_type);
		if (nullptr != pizza_)
		{
			pizza_->prepare();
			pizza_->bake();
			pizza_->cut();
			pizza_->box();
		}

		return pizza_;
	}
	~PizzaStore() = default;
};


/*int main()
{
	//const auto factory = new SimplePizzaFactory();
	const auto factory = std::make_shared<SimplePizzaFactory>();
	PizzaStore ny_pizza_store(factory.get());
	ny_pizza_store.orderPizza("greek");
	return 0;
}*/