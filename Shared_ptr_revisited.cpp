#include <iostream>
#include <memory>
#include <string>

//#define blk1
//#define blk2
//#define blk3
#define blk4
//#define blk5
//#define blk6
#define blk7
#define blk8
/*
	
	Smart Pointers
	Why they are smart?
	Mostly, they prevent you from doing stupid things like memory leaks

*/

/*


	Start from showing you some dumb things
	What is the potential problem of this???
*/
#ifdef blk1
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built" << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship" << m_shipName << std::endl; }
	Space_Ships& laserShots() { 
		if (m_laserAmmo){
			--m_laserAmmo;
			std::cout << "--------------------------<===================[]\n";
		}
		else {
			throw std::string("Out of Ammo");
		}
		return *this;
	};
};

void buildAndFire() {
	Space_Ships* newShip = new Space_Ships("Death Star");
	newShip->laserShots().laserShots().laserShots();
	delete newShip;
}



int main() {
	try{
		buildAndFire();
	}
	catch (std::string& err){
		std::cout << err << std::endl;
	}
}
#endif // blk1
// The anwser is quite obvious//
// The destructor did not get called//
// because of throwing exception in laserShot will redirect the program
// So the delete statement won't be triggered//

// allocated memory did not get deleted meaning?
// MEMORY LEAK!!!!!!!!!!!!!!!!!!!!


// How to fix it ?// 
// We can use the way I did for my assignment// 
// Something like a middle ware to collect the exception and do your stuff and then throw again//
// In the buildAndFire()

#ifdef blk2
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built "<<name << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship " << m_shipName << std::endl; }
	Space_Ships& laserShots() {
		if (m_laserAmmo) {
			--m_laserAmmo;
			std::cout << "--------------------------<===================[]\n";
		}
		else {
			throw std::string("Out of Ammo");
		}
		return *this;
	};
};

void buildAndFire() {
	Space_Ships* newShip = new Space_Ships("Death Star");
/*----------------------------------------------------*/
	try{
		newShip->laserShots().laserShots().laserShots();
	}
	catch (const std::string& err){
		delete newShip;
		throw err;
	}
	delete newShip;
/*----------------------------------------------------*/
}



int main() {
	try {
		buildAndFire();
	}
	catch (std::string& err) {
		std::cout << err << std::endl;
	}
}
#endif // blk2


/* 

	But it seems dumb.
	Any better solutions?
	That's why we need the smart ptrs

	Smart Ptr helps you strictly follow with the RAII
		Even you manmually allocated the memory. 
		So even you forget the delete statement.
		It will still redirect your program to the destructor( memory leaks will be prevented )
*/


/* 
	Shared_Ptr:
		Allows multiple ptr pointing at the same resource. 
		Copyable and moveable.
		By using the ref count to determine if the program needs to free the resource.
		When ref_count reaches 0, the resource will be destroyed by destructor
*/
#ifdef blk3
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built " << name << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship " << m_shipName << std::endl; }
	Space_Ships& laserShots() {
		if (m_laserAmmo) {
			--m_laserAmmo;
			std::cout << "--------------------------<===================[]\n";
		}
		else {
			throw std::string("Out of Ammo");
		}
		return *this;
	};
};

void buildAndFire() {
	std::shared_ptr<Space_Ships> newShipPtr1 (new Space_Ships("Death Star"));
	newShipPtr1->laserShots();
	std::cout <<"Num of ptr pointed at the same resource " << newShipPtr1.use_count() << "\n";
	// A mini scope for testing the shared_ptr
	{
		std::shared_ptr<Space_Ships> newShipPtr2(newShipPtr1);
		std::cout << "Num of ptr pointed at the same resource " << newShipPtr1.use_count() << "\n";
		newShipPtr2->laserShots().laserShots();
	}

}



int main() {
	try {
		buildAndFire();
	}
	catch (std::string& err) {
		std::cout << err << std::endl;
	}
}
#endif // blk3




/*
*------------------Warning: Some dumb ways to use share_ptr---------------------------
*/
#ifdef blk4
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built " << name << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship " << m_shipName << std::endl; }
	Space_Ships& laserShots() {
		if (m_laserAmmo) {
			--m_laserAmmo;
			std::cout << "--------------------------<===================[]\n";
		}
		else {
			throw std::string("Out of Ammo");
		}
		return *this;
	};
};

void buildAndFire() {
	std::shared_ptr<Space_Ships> newShipPtr1(new Space_Ships("Death Star"));
	newShipPtr1->laserShots();
	std::cout << "Num of ptr pointed at the same resource " << newShipPtr1.use_count() << "\n";

	{	// Letting two shared_ptr pointed at the raw ptr is dumb and unsafe// 
		// Cuz the use count won't be tracked properly// 
		// Multiple destruction on the same resource is -----deallocating garbage values----undefined behavior
		// Because it is not a smart PTR!!!// 
		Space_Ships* raw_ptr = (new Space_Ships("Home One"));
		std::shared_ptr<Space_Ships> newShipPtr2(raw_ptr);
		std::shared_ptr<Space_Ships> newShipPtr3(raw_ptr);
		std::cout << "Num of ptr pointed at the rawPTR resource " << newShipPtr2.use_count() << "\n";
		newShipPtr2->laserShots().laserShots();

		// Same thing will happen if you used the smart_ptr.get() 
		// .get will return the raw ptr back// 
		Space_Ships* temp = newShipPtr2.get();
		//// Isn't this a double delete? Undefined behavior!!!!!//
		//delete temp;

	}
}
int main() {
	try {
		buildAndFire();
	}
	catch (std::string& err) {
		std::cout << err << std::endl;
	}
}
#endif // blk4


/*
*------------------What if your initialization on the smart ptr triggers some exceptions?----------------
* That would be a memory leak again. 
* That's why we should always use the make_shared wrapping around new... 
*/
#ifdef blk5
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built " << name << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship " << m_shipName << std::endl; }
	Space_Ships& laserShots() {
		if (m_laserAmmo) {
			--m_laserAmmo;
			std::cout << "--------------------------<===================[]\n";
		}
		else {
			throw std::string("Out of Ammo");
		}
		return *this;
	};
};

void buildAndFire() {
	//Something my prof never showed before//
	// make_shared is not only fast//
	// But also exception safe //
	// syntax // 
	// std::make_shared<typeName>(constructorArgument)
	std::shared_ptr<Space_Ships> newShipPtr1 = std::make_shared<Space_Ships>("Death Star");
	newShipPtr1->laserShots();
	std::cout << "Num of ptr pointed at the same resource " << newShipPtr1.use_count() << "\n";

	{	
		std::shared_ptr<Space_Ships> newShipPtr2(newShipPtr1);
		std::cout << "Num of ptr pointed at the same resource " << newShipPtr1.use_count() << "\n";
		newShipPtr2->laserShots().laserShots();
	}
}
int main() {
	try {
		buildAndFire();
	}
	catch (std::string& err) {
		std::cout << err << std::endl;
	}
}
/*
	You could use templated ptr cast on the smart ptr too btw

*/
#endif // blk5



/*

	As a matter of fact, not just ref count will cause a shared_ptr's resource deleted

*/
#ifdef blk6
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built " << name << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship " << m_shipName << std::endl; }
	Space_Ships& laserShots() {
		if (m_laserAmmo) {
			--m_laserAmmo;
			std::cout << "--------------------------<===================[]\n";
		}
		else {
			throw std::string("Out of Ammo");
		}
		return *this;
	};
};

void buildAndFire() {
	std::shared_ptr<Space_Ships> newShipPtr1 = std::make_shared<Space_Ships>("Death Star");
	std::shared_ptr<Space_Ships> newShipPtr2 = std::make_shared<Space_Ships>("Star Destroyer"); 
	std::shared_ptr<Space_Ships> newShipPtr3 = std::make_shared<Space_Ships>("Lambda-class shuttle");
	std::shared_ptr<Space_Ships> newShipPtr4 = std::make_shared<Space_Ships>("Super Star Destroyer");
	std::cout << "-------------------Start testing the ways to get the resources destroyed------------------------\n";
	// using assignment operator to move//
	newShipPtr1 = newShipPtr4;
	// set the smart ptr to nullptr // 
	newShipPtr2 = nullptr;
	// calling member methods to reset smartptr// 
	newShipPtr3.reset();
	std::cout << "-------------------End testing the ways to get the resources destroyed------------------------\n";
	
	/* 
		you could have shared_ptr with the customized deleter
			So the resource will be deleted in the cutomized way
	*/

	std::cout << "-------------------Start deleting the resource in the custom deleter------------------------\n";
	// Be aware that make_shared cannot be used with a custom deleter//
	// But why?//
	// These coders' anwsers are so inspiring  https://stackoverflow.com/questions/34243367/how-to-pass-deleter-to-make-shared //
	// This is wrong//
	/*std::shared_ptr<Space_Ships> newShipPtr4(std::make_shared<Space_Ships>("Special Super Star Destroyer"), [](const std::shared_ptr<Space_Ships>) {std::cout << "The ship is in the customized deleter"; });*/
	// Thus, you have to use the old fasion way to delcare// 
	std::shared_ptr<Space_Ships> newShipPtr5(new Space_Ships[6], [](Space_Ships* src) {std::cout << "The fleet is in the customized deleter\n"; delete[]src; });
	// Think about it , if you don't use the customize deleter, from index 1 - 5, memory will leak //
	std::cout << "-------------------End deleting the resource in the custom deleter------------------------\n";
}
int main() {
	try {
		buildAndFire();
	}
	catch (std::string& err) {
		std::cout << err << std::endl;
	}
}

#endif // blk6


