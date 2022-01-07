//The command pattern encapsulates a request as an object, thereby allowing you to parameterize other
//objects with different requests, queue, log requests, and support undoable operations
//The command pattern allows you to decouple the requester of an action from the object that actually
//performs the action. you can do this by introducing the "command objects" into your design.
//A command object encapsulates a request to do something(e.g. turning on a light) on a specific object
//(e.g. the living room light object).
//you can use lambda expression inplace of each command class if you have too many commands
//lambda expressims are designed specfically to replace methods in functional interfaces partly as
//a way to reduce the ode that is required when you have a lot of small classes with functional
//interfaces.
//A functional interface cannot have more than one method.(concept of java)
//Command pattern can be used in many applications such as schedulers, thread pools, job queues, logging etc.
//When you need to decouple an object making requests from the object that knows how to perform
//the requests, use the command pattern

#include <iostream>
#include <vector>
#include <string>

class Light
{
	std::string room_;
public:
	Light(std::string room)
	{
		room_ = room;
	}
	void on()
	{
		std::cout << "turning on the " << room_ << " light\n";
	}
	void off()
	{
		std::cout << "turning of the " << room_ << " light\n";
	}
};

class GarageDoor
{
public:
	void up()
	{
		std::cout << "Garage Door is Open\n";
	}
	void down()
	{
		std::cout << "Garage Door is Closed\n";
	}
	void stop()
	{
		std::cout << "Garage Door is Stopped\n";
	}
	void lightOn()
	{
		std::cout << "Garage Light is On\n";
	}
	void lightOff()
	{
		std::cout << "Garage Light is Off\n";
	}
};

class Stereo
{
public:
	void on()
	{
		std::cout << "Turn on the Stereo\n";
	}
	void off()
	{
		std::cout << "Turn off the Stereo\n";
	}
	void setCD()
	{
		std::cout << "Playing from CD\n";
	}
	void setDVD()
	{
		std::cout << "playing from DVD\n";
	}
	void setVolume(uint8_t volume_level)
	{
		std::cout << "vloume level is set to " << static_cast<int>(volume_level)
		<< "\n";
	}
};

class CeilingFan
{
public:
	enum class SPEED{OFF = 0, LOW, MEDIUM, HIGH};
	void high()
	{
		std::cout << "set fan speed to high\n";
		speed_ = SPEED::HIGH;
	}
	void medium()
	{
		std::cout << " set fan speed to medium\n";
		speed_ = SPEED::MEDIUM;
	}
	void low()
	{
		std::cout << "set fan speed to low\n";
		speed_ = SPEED::LOW;
	}
	void off()
	{
		std::cout << "turn off the fan\n";
		speed_ = SPEED::OFF;
	}
	SPEED getSpeed() const
	{
		return speed_;
	}
private:
	SPEED speed_ = SPEED::OFF;
};

class Command
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

class LightOnCommand : public Command
{
	Light* light_;
public:
	LightOnCommand(Light* light)
	{
		light_ = light;
	}
	void execute() override
	{
		light_->on();
	}
	void undo() override
	{
		light_->off();
	}
};

class LightOffCommand: public Command
{
	Light* light_;
public:
	LightOffCommand(Light* light)
	{
		light_ = light;
	}
	void execute() override
	{
		light_->off();
	}
	void undo()
	{
		light_->on();
	}
};
class GarageDoorOpenCommand : public Command
{
	GarageDoor* garage_door_;
public:
	GarageDoorOpenCommand(GarageDoor* garage_door)
	{
		garage_door_ = garage_door;
	}
	void execute() override
	{
		garage_door_->up();
	}
	void undo() override
	{
		garage_door_->down();
	}
};

class GarageDoorCloseCommand: public Command
{
	GarageDoor* garage_door_;
public:
	GarageDoorCloseCommand(GarageDoor* garage_door)
	{
		garage_door_ = garage_door;
	}
	void execute() override
	{
		garage_door_->down();
	}
	void undo() override
	{
		garage_door_->up();
	}
};

class StereoOnCOmmand: public Command
{
	Stereo* stereo_;
public:
	StereoOnCOmmand(Stereo* stereo)
	{
		stereo_ = stereo;
	}
	void execute() override
	{
		stereo_->on();
		stereo_->setCD();
		stereo_->setVolume(9);
	}
	void undo() override
	{
		stereo_->off();
	}
};

class StereoOffCommand: public Command
{
	Stereo* stereo_;
public:
	StereoOffCommand(Stereo* stereo)
	{
		stereo_ = stereo;
	}
	void execute() override
	{
		stereo_->off();
	}
	void undo() override
	{
		stereo_->on();
	}
};

class CeilingFanHighCommand: public Command
{
	CeilingFan* ceiling_fan_;
	CeilingFan::SPEED prev_speed_;
public:
	CeilingFanHighCommand(CeilingFan* ceiling_fan)
	{
		ceiling_fan_ = ceiling_fan;
		prev_speed_ = CeilingFan::SPEED::OFF;
	}
	void execute() override
	{
		prev_speed_ = ceiling_fan_->getSpeed();
		ceiling_fan_->high();
	}
	void undo() override
	{
		if (prev_speed_ == CeilingFan::SPEED::LOW)
			ceiling_fan_->low();
		else if (prev_speed_ == CeilingFan::SPEED::MEDIUM)
			ceiling_fan_->medium();
		else if (prev_speed_ == CeilingFan::SPEED::OFF)
			ceiling_fan_->off();
	}
};

class CeilingFanLowCommand : public Command
{
	CeilingFan* ceiling_fan_;
	CeilingFan::SPEED prev_speed_;
public:
	CeilingFanLowCommand(CeilingFan* ceiling_fan)
	{
		ceiling_fan_ = ceiling_fan;
		prev_speed_ = CeilingFan::SPEED::OFF;
	}
	void execute() override
	{
		prev_speed_ = ceiling_fan_->getSpeed();
		ceiling_fan_->low();
	}
	void undo() override
	{
		if (prev_speed_ == CeilingFan::SPEED::HIGH)
			ceiling_fan_->high();
		else if (prev_speed_ == CeilingFan::SPEED::MEDIUM)
			ceiling_fan_->medium();
		else if (prev_speed_ == CeilingFan::SPEED::OFF)
			ceiling_fan_->off();
	}
};

class CeilingFanOffCommand: public Command
{
	CeilingFan* ceiling_fan_;
	CeilingFan::SPEED prev_speed_;
public:
	CeilingFanOffCommand(CeilingFan* ceiling_fan)
	{
		ceiling_fan_ = ceiling_fan;
		prev_speed_ = CeilingFan::SPEED::OFF;
	}
	void execute() override
	{
		prev_speed_ = ceiling_fan_->getSpeed();
		ceiling_fan_->off();
	}
	void undo() override
	{
		if (prev_speed_ == CeilingFan::SPEED::HIGH)
			ceiling_fan_->high();
		else if (prev_speed_ == CeilingFan::SPEED::MEDIUM)
			ceiling_fan_->medium();
		else if (prev_speed_ == CeilingFan::SPEED::LOW)
			ceiling_fan_->low();
	}
};

class SimpleRemoteControl
{
	const uint8_t number_of_slots_;
	std::vector<Command*> on_commands_;
	std::vector<Command*> off_commands_;
	Command* undo_command_;
public:
	SimpleRemoteControl(const uint8_t number_of_slots) : number_of_slots_(number_of_slots)
	{
		on_commands_.reserve(number_of_slots_);
		off_commands_.reserve(number_of_slots_);
		for(int i = 0; i < number_of_slots_; i++)
		{
			on_commands_.push_back(nullptr);
			off_commands_.push_back(nullptr);
		}
		undo_command_ = nullptr;
	}
	void setCommand(int slot, Command* onCommand, Command* offCommand)
	{
		on_commands_[slot] = onCommand;
		off_commands_[slot] = offCommand;
	}
	void onButtonPressed(int slot)
	{
		on_commands_[slot]->execute();
		undo_command_ = on_commands_[slot];
	}
	void offButtonPressed(int slot)
	{
		off_commands_[slot]->execute();
		undo_command_ = off_commands_[slot];
		
	}
	void undoCommandPressed()
	{
		undo_command_->undo();
	}
};

/*
int main()
{
	Light* kitchen_light = new Light("kitchen");
	LightOnCommand* kitchen_light_on_command = new LightOnCommand(kitchen_light);
	LightOffCommand* kitchen_light_off_command = new LightOffCommand(kitchen_light);
	SimpleRemoteControl* simple_remote_control = new SimpleRemoteControl(7);
	simple_remote_control->setCommand(0, kitchen_light_on_command, kitchen_light_off_command);
	simple_remote_control->offButtonPressed(0);

	GarageDoor* garage_door = new GarageDoor;
	GarageDoorOpenCommand* garage_door_open_command = new GarageDoorOpenCommand(garage_door);
	GarageDoorCloseCommand* garage_door_close_command = new GarageDoorCloseCommand(garage_door);
	simple_remote_control->setCommand(1, garage_door_open_command, garage_door_close_command);
	simple_remote_control->onButtonPressed(1);
	
	Stereo* stereo = new Stereo;
	StereoOnCOmmand* stereo_on_command = new StereoOnCOmmand(stereo);
	StereoOffCommand* stereo_off_command = new StereoOffCommand(stereo);
	simple_remote_control->setCommand(2, stereo_on_command, stereo_off_command);
	simple_remote_control->onButtonPressed((2));
	simple_remote_control->undoCommandPressed();

	CeilingFan* ceiling_fan = new CeilingFan;
	CeilingFanLowCommand* ceiling_fan_low_command = new CeilingFanLowCommand(ceiling_fan);
	CeilingFanHighCommand* ceiling_fan_high_command = new CeilingFanHighCommand(ceiling_fan);
	CeilingFanOffCommand* ceiling_fan_off_command = new CeilingFanOffCommand(ceiling_fan);
	simple_remote_control->setCommand(3, ceiling_fan_high_command, ceiling_fan_off_command);
	simple_remote_control->setCommand(4, ceiling_fan_low_command, ceiling_fan_off_command);

	simple_remote_control->onButtonPressed(3);
	simple_remote_control->onButtonPressed(4);
	simple_remote_control->undoCommandPressed();
	//simple_remote_control->setCommand(5, [ceiling_fan]() {ceiling_fan->medium(); }, [ceiling_fan]() {ceiling_fan->off(); });
}*/