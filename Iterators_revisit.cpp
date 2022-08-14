#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <deque>
#include <string>
#include <iostream>
/*
At school, profs only introduced how to use iterators. 
Now we need to elvate this thing to the next level
*/


/*
Iterators has following types:

1. Random Accesse iterator: vector, deque, array
	We can use post or pre increment/decrement or itr +- number 
	to move around the iterator.

2. Birdirectional iterators: list, set, map
	We can ONLY use post or pre increment/decrement to move 
	around the iterator. 

3. Forward Iterator: forward_list
	forward_list<int> itr;
	++itr;
	Unordered container provide "at least" forward iterators.

4. Input Iterator:
	Read and Process values while iterating forward(ONLY FORWARD)
	int x = *itr

5. Output Iterator:
	Output values while iterating forward.
	*itr = 100
*/

/* 
All the STL containers has a iterator and a const_iterator
	const_iterator gives the read_only access to the container element.
*/

/*
Iterator Functions:
	advance(itr,offSet) e.g. advance(itr,5) move forward 5 elements
	distance(itr1,itr2)	e.g. distance(itr1,itr2) returns the offset of the itr1 and itr2
*/

/*
Iterator adapters:( Really powerful, I will show an example of how I used this to
make my code better than the other ppl at my class )
	Basically they are special but powerful iterators. 


		




	4. Move iterators:

*/

////1. Insert Iterators :
//
//// Copying values from one container to another
//// With filters.
//// Normally my classmates would probably use a manual loop, 
//// Or find_if to filter the containers's element. 
//// Then copy and transform to the dst//
//
//// But you could actually do this in one shot 
//// With the power of the Insert Iterators.
// uncomment below
//----------------------------------------------
//int main() {
// 
// 	std::vector<int> dst{ 4,6,8 };
//	std::vector<int> src{ 2,4,7,8,11 };
//	std::deque<int>  dst2{};
//	std::vector<int> dst3{ 100,200,300,400,500 };
//	
//    // 1. back insert interator
//	// back_inserter will simply return a back_insert_iterator back according to the argument sent//
//	std::copy_if(src.cbegin(), src.cend(), std::back_inserter(dst), [](const int source) {return !(source % 2); });
//    // 2. front insert iterator( Can only be used on a container allowing add front
//    //	Which means it must have a member function called push_front() (like deque has it)
//	std::copy_if(src.cbegin(), src.cend(), std::front_inserter(dst2), [](const int source) {return !(source % 2); });
//
//    // 3. The OG way to do the Insert iterator:
//    // Use find_if to get the iterator pointing to 2/
//	std::vector<int>::iterator itr = std::find(dst3.begin(), dst3.end(), 200);
//	// Highly recommend back/front_inserter if you don't need to find a specific index to insert//
//	// std::insert_iterator<std::containerTypeName<containedEleName>> inserter_iteratorName (containerVariableName,iteratorName)//
//	std::insert_iterator<std::vector<int>> i_itr(dst3, itr);
//	// copy will add BEFORE the inserter_iterator's index(NOT AFTER)//
//	std::copy(src.begin(), src.end(), i_itr);
//	for (int& x : dst3) {
//		std::cout << "dst3 values" << x << "\n";
//	}
//
//	for (int& x : dst) {
//		std::cout<<"dst values:" << x << "\n";
//	}
//
//	for (int& x : dst2) {
//		std::cout<<"dst2 values" << x << "\n";
//	}
//	 
//	return 0;
//}
//// until here
//----------------------------------------------

// 2. Stream Iterators :

//int main() {
//	std::vector<std::string> vec{"They call me Roger", "They call me Jinder", "That's not my name"};
//	
//	
//	// Isn't that sick? Instead of using a dumb for_each,
//	// we copy the data to the ostream, and cout the result and separated by space
//	std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, "~~~ "));
//	
//	//// We could also use the istream_iterator, to treat it like a container iterator
//	//// first arg is saying set the std::cin as the begining of the data
//	//// second arg is saying the end( by using the default constructor of the istream iterator
//	//// third arg is saying store it in the vec from the back
//	////std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::back_inserter(vec));
//
//	// You could also have something like this 
//	// Just showing whatever you entered
//	std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::ostream_iterator<std::string>(std::cout, "~~~ "));
//
//}
//

//// 3. Reverse Iterators:
//// As simple as you can imagine
//int main() {
//	std::vector<int> vec{ 4,5,6,7 };
//	std::reverse_iterator<std::vector<int>::iterator> ritr;
//	for (ritr = vec.rbegin(); ritr != vec.rend(); ++ritr){
//		std::cout << *ritr << std::endl;
//	}
//}




