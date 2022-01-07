// Observer Pattern - It defines one-to-many objects dependency so that when one object changes state, all it dependency
// are notified and updated automatically.

//Loose coupling - When two objects are loosely coupled, they can interact but have very little knowledge of each other.
//The observer pattern provides an object design where subjects and observers are loosely coupled.

//DESIGN PRINCIPLE 4 - Strive for loosely coupled designs between objects that interact

//Loosly couple designs allow us to build flexible OO systems that can handle change because they minimize the interdependency between objects.

// Design Principle 1 - Identify the aspects of your application that vary and separate them from what stays the same.
//The thing that varies in the observer pattern is the state of the subject and the number and type of observers. With this pattern, you can vary the objects
// that are dependent on the state of the subject without having to change the subject.

// Design Principle 2 - Program to an interface, not an implementation
// Both the subject and observers use interfaces. The subject keeps track of the number of objects implementing the observer interface, while the observers
// register with and get notified by the subject interface. This keeps things nice and loosly coupled   (coupling means dependency from eitherside)

//Design Principle 3 - Favor composition over inheritance
// In this pattern, both subject and observer are linked together by composition at runtime.

// Observer Pattern can be used  in either push or pull method
// push method - subject can push the data, when data gets changed using notify observers as below
// pull method - subject can inform observers when data gets changed, hence observer can pull the data

#include<iostream>
#include<vector>
#include<algorithm>

class IObserver
{
public:
	virtual void update(double temperature, double pressure, double humidity) = 0;
};
class IWeatherData
{
public:
	virtual void registerObserver(IObserver* o) = 0;
	virtual void removeObserver(IObserver* o) = 0;
	virtual void notifyObservers() = 0;
};

class WeatherData : public IWeatherData
{
public:
	void registerObserver(IObserver* o)
	{
		observer_array.emplace_back(o);
	}
	void removeObserver(IObserver* o)
	{
		auto itr = std::remove_if(observer_array.begin(), observer_array.end(), [&](IObserver* obs) {return obs == o; });
		if(itr != observer_array.end())
			observer_array.erase(itr);
		
	}
	void notifyObservers()
	{
		for(auto itr: observer_array)
		{
			itr->update(temp_, pres_, humid_);
		}
	}
	void measurementsChanged()
	{
		notifyObservers();
	}
	void setMeasurements(double temp, double pres, double humid)
	{
		temp_ = temp;
		pres_ = pres;
		humid_ = humid;
		measurementsChanged();
	}
private:
	std::vector<IObserver*> observer_array{};
	double temp_ = 0, pres_ = 0, humid_ = 0;
};

class IDisplay
{
public:
	virtual void display() = 0;
};

class CurrentDataDisplay : public IObserver, IDisplay
{
public:
	CurrentDataDisplay(IWeatherData& obj): subject(obj)
	{
		subject.registerObserver(this);
	}
	void update(double temp, double pres, double humid)
	{
		temp_ = temp;
		pres_ = pres;
		humid_ = humid;
		display();
	}
	void display()
	{
		std::cout << "I am Current Data Display\n";
		std::cout << "temperature = " << temp_ << "\n";
		std::cout << "pressure = " << pres_ << "\n";
		std::cout << "humidity = " << humid_ << "\n";
 	}
private:
	double temp_ = 0, pres_ = 0, humid_ = 0;
	IWeatherData& subject;
};

class StatisticsDataDisplay : public IObserver, IDisplay
{
public:
	StatisticsDataDisplay(IWeatherData& obj): subject(obj)
	{
		subject.registerObserver(this);
	}
	void update(double temp, double pres, double humid)
	{
		temp_ = temp;
		pres_ = pres;
		humid_ = humid;
		display();
	}
	void display()
	{
		std::cout << "I am Statistics Data Display\n";
		std::cout << "temperature = " << temp_ << "\n";
		std::cout << "pressure = " << pres_ << "\n";
		std::cout << "humidity = " << humid_ << "\n";
	}
private:
	double temp_ = 0, pres_ = 0, humid_ = 0;
	IWeatherData& subject;
};
/*
int main()
{
	WeatherData* obj = new WeatherData();
	CurrentDataDisplay subscriber_obj(*obj);
	StatisticsDataDisplay statistics_obj(*obj);
	obj->setMeasurements(10.0, 8.7, 9.5);
	obj->removeObserver(&statistics_obj);
	obj->setMeasurements(5.3, 4.5, 2.9);
}*/