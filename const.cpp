#include <iostream>
/*
Const 
	First of all, it is a constraint during the COMPILE time. 
	Secondly, that constraint can make the object or variable NOT modifiable. 
*/

int main() {
	// You are smart enough to know that i can not be changed with ++i.
	const int i = 9;
	
	// But what about this?
	const int* ptr = &i;
	// Still can't compile right? Cuz this is a const ptr which stores a read only location//
	//*ptr = 5;
	// Now I have this? 
	const int* ptr2{};
	ptr2 = ptr;
	std::cout<<++ptr2<<std::endl;
	// ???
	// It seems I modified a const. 
	// Remember, const int*  ptr meaning the variable ptr pointed at is CONST// 
	// Not meaning ptr itself is CONST //

	// So how to make a ptr const, but variable is not const?//
	int j{ 10 };
	int* const ptr3{&j};
	// this is something we haven't seen in the school right?
	// You are pretty much saying const is only working on the ptr3 itself, not the vairable it points to//
	// Let's test it//
	// Does not compile lol//
	//++ptr3;
	// Now you actually modified the ptr3's variable//
	*ptr3 = 109;
	std::cout <<"ptr3's value on that address is " << *ptr3 << " and the j is " << j << std::endl;

	// Now you are thinking there could be something like this right?//
	const int f{ 20 };
	const int* const ptr4{ &f };
	std::cout << "ptr4's value on that address is " << *ptr4 << " and the f is " << f << std::endl;
	// Although I haven't seen anyone code like this yet, but its existence proves it is useful in some cases//




	/*
	-----------------Leveling up----------------
	*/
	// what is this thing?
	// Start operator dereferencing? Or declaring ptr? Declaring an int?
	// who is the const who is not?
	int const *ptr5{ &i };
	// The rule is 
		// const qualifier on the left of * , meaning the	VARIABLE pointed by ptr is const.
		// const qualifier on the right of *, meaning the	ptr itself is const.
		// As for dereferencing? This is obviously declaring a new variable.
		// When declaring variable, although the * is not right beside the type name, it still 
		// meaning we are declaring a ptr. (don't write like this, it is actually annoying to look at//
	std::cout << "ptr4's value on that address is " << *ptr5 << " and the i is " << i << std::endl;

	/*
	
	----------------using const_cast to deal with const and const ref-----------------
	
	*/

	const int a_const{ 4 };
	int n{ 100 };
	const int& n_ref{ n };
	// Some more notes about const_cast
	// You can use it for removing the const-ness from a reference
	// But that reference must not be referred to a const val. 
	// MS compiler won't give you error, but your variable valules won't be changed//
	// But g++ will tell you this is undefined behavior//
	const_cast<int&>(n_ref) = 800;
	std::cout << "Making n_ref lose const, and change the val " << n << std::endl;
	// Also the const_cast will return the value not const, you could store it in a new var//
	int not_const = const_cast<int&> (a_const) = 400;
	std::cout<<"Not so const "<< not_const << std::endl;



	/*
	
	---------------using static_cast to make a variable const----------------
	
	*/

	int k{ 600 };
	// This will return a const reference to k//
	const int& l = static_cast<const int&> (k);
	// of course this is undefined bahvior//
	//l = 100;
	//But can you still change k's value?//
	k = 100;
	std::cout << "k now is? " << k << std::endl;
	// Because it is actually not making k a const variable// 
	// It is returning a const reference referring to k// 
	// k is still not a const//

	/*
		Cuz: CONST IS HAPPENING DURING THE COMPILATION TIME
		
		Essentially, const qualifier is forcing you stay away from doing things 
		potenially blow the universe.
	*/

}