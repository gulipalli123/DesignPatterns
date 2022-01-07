//Attempt to put a square peg in a round hole.
//Say you have got an existing software system that you need to work a new vendor class library into, but the new vendor designed their class interfaces differently than the old vendor.
//Okay you dont have to solve the problem by changing your exisitng code(and you cannot change the vendors code).Then what shall you do?
//You can write a class which adapts the new vendor interface into the one you are expecting.
//Adapter implements the interface your class expect and talk to venodr interface to service your requests.
//The Adapter pattern's role is to convert one interface into another.While most examples of adapter pattern show an adapter wrapping one adaptee, but we may have situations where
//adapter holds two or more adaptees to implement target interface. This relates to another pattern called Facade pattern.
//Adapter pattern converts the interface of a class into another iterface that the client expects.
// This pattern  lets classes to work together that couldn't otherwise because of incompatible interfaces.
//Adapter acts to decouple the client from the implemented interface, and if we expect the interface to change over time, the adapter encapsulates that change
//so that the cleint does not have to be modified each time.
// Two kind of adapters- class adapters, object adapters.
//object adapters - adpter inherits target interface and uses composition for storing adaptee object
//class adpaters - uses multiple inheritance, inherits both target and adaptee
#include <iostream>