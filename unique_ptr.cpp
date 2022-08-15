#include <iostream>
#include <memory>
#include <string>

//#define blk1
//#define blk2
//#define blk3
#define blk4
//#define blk5


/*

	Smart Pointers
	Why they are smart?
	Mostly, they prevent you from doing stupid things like memory leaks

*/

/*
	Same like shared_ptr, we start with using this class
	Same issue, exception could cause the potential memory leak
	
	This time we will use unique_ptr
		When a unique_ptr out of scope or allocated with new resources
		The destructor will be called.
		unique_ptr only has the move constructor and move assignment operator. 
				   copy is banned

	Advantages about unique_ptr:
		Almost same effcient as the raw ptr. 
		Exclusive ownership.
		Whenever it is possible, use unique_ptr.
*/

#ifdef blk1
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built" << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship --->" << m_shipName << std::endl; }
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
	// same like shared_ptr, it is better to use make_unique<typeName>(constructorArgs...)
	std::unique_ptr<Space_Ships> newShipPtr(std::make_unique<Space_Ships>("Death Star"));
	newShipPtr->laserShots().laserShots();

	// similar like shared_ptr, unique_ptr has member function .release()
	// It will return a raw ptr of the unique_ptr wrapper//
	// Be aware that once released, newShipPtr will give up the ownership of the resource//
	// Which means you have to handle the resource memory yourself//
	// This is totally different from .get() method from shared_ptr//
	Space_Ships* temp = newShipPtr.release();
	delete temp;
}



int main() {
	try {
		buildAndFire();
	}
	catch (std::string& err) {
		std::cout << err << std::endl;
	}
}
#endif // blk1



/*
	
	More member methods from unique_ptr class

*/

#ifdef blk2
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built" << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship --->" << m_shipName << std::endl; }
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
	// same like shared_ptr, it is better to use make_unique<typeName>(constructorArgs...)
	std::unique_ptr<Space_Ships> newShipPtr(std::make_unique<Space_Ships>("Death Star"));
	newShipPtr->laserShots().laserShots();
	// Notice you can not use reset and make_unique just like when you are delcaring something//
	// Reason is like you can not get borned twice//
	// Reset will trigger the destructor right away to deallocate and give up the unique//
	// Ownership of the previous resource and allocated with the new resource//
	newShipPtr.reset(new Space_Ships("Nebulon-B frigate"));
	if (newShipPtr){
		std::cout << "now I reset the newShipPtr with a new ship\n";
	}

	// Just like .reset//
	// make the ptr to nullptr also will destory the resource// 
	std::cout << "---------------------------------------start of the nullptr test-------------------\n";
	std::unique_ptr<Space_Ships> newShipPtr2(std::make_unique<Space_Ships>("Millennium Falcon"));
	newShipPtr2 = nullptr;
	std::cout << "---------------------------------------end of the nullptr test-------------------\n";

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

	Moving the unique_ptr and transfer the ownership

*/
#ifdef blk3
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built" << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship --->" << m_shipName << std::endl; }
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
	// same like shared_ptr, it is better to use make_unique<typeName>(constructorArgs...)
	std::unique_ptr<Space_Ships> newShipPtr(std::make_unique<Space_Ships>("Death Star"));
	newShipPtr->laserShots().laserShots();
	std::unique_ptr<Space_Ships> newShipPtr2(std::make_unique<Space_Ships>("Upgraded Death Star"));
	/*
		1. newShipPtr's resource => death star will be destoryed
		2. newShipPtr now is empty
		3. move the resource of newShipPtr2 to the newShipPtr
		4. newShipPtr now owns the newShipPtr2's resource
		5. newShipPtr2 is now empty
	*/
	std::cout << "---------------->Moving Started<---------------\n";
	newShipPtr = std::move(newShipPtr2);
	std::cout << "---------------->Moving Ended<---------------\n";
}

/* 
	Moving is automatically happening inside the funciton 
	When you are trying to return a unique_ptr
*/

std::unique_ptr<Space_Ships> spaceShipFacotry(const std::string& name) {
	// It could only move but no copy//
	// Again, exclusive ownership//
	return std::unique_ptr<Space_Ships>(new Space_Ships(name));
}

int main() {
	try {
		buildAndFire();
	}
	catch (std::string& err) {
		std::cout << err << std::endl;
	}
	std::cout << "---------------->Testing spaceShip Factory Started<---------------\n";
	std::unique_ptr<Space_Ships> brandNewShipPtr = spaceShipFacotry("Millennium Falcon");
	std::cout << "---------------->Testing spaceShip Factory Ended<---------------\n";
}
#endif // blk3



/*

	Deleter in unique_ptr class
*/

#ifdef blk4
class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name) :m_shipName{ name } { std::cout << "A new ship is built" << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship --->" << m_shipName << std::endl; }
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
	std::unique_ptr<Space_Ships> newShipPtr(std::make_unique<Space_Ships>("Death Star"));
	newShipPtr->laserShots().laserShots();
	/* unique ptr is specialised for array*/
	/* You actually do need to make a customize deleter*/
	/* Do remember you need to indicate in the typeArgument*/
	std::unique_ptr<Space_Ships[]> newShipPtrArr(new Space_Ships[5]);
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