#include<vector>
#include<iostream>

/*
class Square {
	//details
};

class Renderer {
public:
	void render(const std::vector<Square>& squares);
};

void Renderer::render(const std::vector<Square>& squares)
{
	for (auto& square : squares)
	{
		//Render square object
	}
}

//Now you add support for circles, so you create a circle class:
class Circle {
	//Details
};
*/
// To be able to render circle, you have to modify the render() method of the Renderer class as follows:
/*void Renderer::render(const std::vector<Square>& squares, const std::vector<Circle> circles)
{
	for (auto& square : squares)
	{
		//Render square object
	}
	for (auto& circle : circles)
	{

	}
}*/

// While doing this, you feel there is something wrong! Yes in order to extend functionality to add support for circles,
// you have to modify the current implementation of the render() method, so its not closed for modification and its violating
// the open-closed Solid Principle
//Your design should use inheritance in this case as follows:

class Shape {
public:
	virtual void render() = 0;
};

class Square: public Shape {
public:
	virtual void render() override {
		std::cout << "rendering square" << "\n";
	}
};

class Circle : public Shape {
public:
	virtual void render() override {
		std::cout << "rendering circle" << "\n";
	}
};

class Renderer {
public:
	void render(const std::vector<Shape*>& shapes);
};

void Renderer::render(const std::vector<Shape*>& shapes) {
	for (auto &shape : shapes) {
		shape->render();
	}
}

int main(){
	Square s1, s2, s3;
	Circle c1, c2, c3;
	std::vector<Shape*> s;
	s.push_back(&s1);
	s.push_back(&s2);
	s.push_back(&s3);
	std::vector<Shape> c;
	c.push_back(c1);
	c.push_back(c2);
	c.push_back(c3);
	Renderer r;
	r.render(s);

}