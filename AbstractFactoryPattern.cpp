// An AbstractFactory gives us an interface for creating a family of objects(related or dependent) without
// specifying their concrete classes
// By writing code that uses this interface we decouple our code from the actual factory that creates
// the products. That allows us to implement a variety of factories that produce products meant for
// different contexts- such as different regions, different look and feel.
// Both Factory and Abstract factory encapsulate object creation to keep applications loosely coupled
// and less dependent on implementations
// Factory method relies on inheritance: object creation is delegated to sub classes, which implement
// the factory method(createPizza()) to create objects
// Abstract Factory relies on composition: object creation is implemented in methods exposed in the
// factory interface

#include<iostream>

class PizzaIngredientFactory
{
public:
	virtual std::string createDough() = 0;
	virtual std::string createSauce() = 0;
	virtual std::string createCheese() = 0;
	virtual ~PizzaIngredientFactory() = default;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	std::string createDough() override { return std::string("ThinCrustDough"); }
	std::string createSauce() override { return std::string("MarinaraSauce"); }
	std::string createCheese() override { return std::string("ReggianoCheese");}
};

class Pizza
{
protected:
	std::string name_;
	std::string sauce_;
	std::string dough_;
	std::string cheese_;
public:
	virtual void prepare() = 0;
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
	void setName(const std::string& name) { name_ = name; }
	std::string getName() { return name_; }
	virtual ~Pizza() = default;
};
class CheesePizza : public Pizza
{
	PizzaIngredientFactory* ingredient_factory_;
public:
	CheesePizza(PizzaIngredientFactory* factory) : ingredient_factory_(factory) {}
	void prepare() override
	{
		dough_ = ingredient_factory_->createDough();
		sauce_ = ingredient_factory_->createSauce();
		cheese_ = ingredient_factory_->createCheese();
		std::cout << "Prepare " << name_ << " " << dough_ << " " << sauce_ << " " << cheese_  << "\n";
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
		PizzaIngredientFactory* ingredient_factory = new NYPizzaIngredientFactory();
		if (pizza_type == "cheese")
		{
			pizza_ = new(std::nothrow) CheesePizza(ingredient_factory);
			pizza_->setName("NewYork Style Cheese Pizza");
		}
		/*else if (pizza_type == "greek")
			pizza_ = new(std::nothrow) GreekPizza();
		else if (pizza_type == "pepperoni")
			pizza_ = new(std::nothrow) PepperoniPizza();*/
		return pizza_;
	}
};

int main()
{
	PizzaStore* ny_pizza_store = new NYPizzaStore();
	ny_pizza_store->orderPizza("cheese");
	return 0;
}
