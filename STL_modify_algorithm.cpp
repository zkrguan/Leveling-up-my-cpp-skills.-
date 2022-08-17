#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
/*

	These algorithms will change the container's element values
		STL Modifiers Algorithms
*/


class Space_Ships {
	std::string m_shipName{};
	unsigned m_laserAmmo{ 2 };
public:
	Space_Ships(const std::string& name, const unsigned& ammo) :m_shipName{ name }, m_laserAmmo{ ammo } { std::cout << "A new ship is built" << std::endl; }
	Space_Ships() { std::cout << "This ship has no name, but we built it already" << std::endl; }
	~Space_Ships() { std::cout << "Destroying ship" << m_shipName << std::endl; }
	Space_Ships& laserShots() {
		if (m_laserAmmo) {
			--m_laserAmmo;
			std::cout << "--------------------------<===================[]\n";
		}
		else {
			throw std::string("Out of Ammo");
		}
		return *this;
	}
	Space_Ships& operator = (const Space_Ships& src) {
		std::cout << "cloning the ship " + src.m_shipName << std::endl;
		if (this != &src)
		{
			m_shipName = src.m_shipName;
			m_laserAmmo = src.m_laserAmmo;
			return *this;
		}
	}
	bool operator >(const Space_Ships& src) { return m_laserAmmo > src.m_laserAmmo; }
	bool operator <(const Space_Ships& src) { return m_laserAmmo < src.m_laserAmmo; }
	bool operator == (const Space_Ships& src) { return m_laserAmmo == src.m_laserAmmo; }

};

//
//#define blk1
//#define blk2
//#define blk3
#define blk4
//#define blk5
//#define blk6
#define blk7
#define blk8
#define blk9

int main() {

	/*
	*	copy, copy_if,
	*
		DstIterator std::copy(SrcIterator f, SrcIterator l, DstIterator o)

		First two args are the range of the copying src
		The third arg is where the container start getting the started

		Return value?
		Will return the third argument back. Does not matter if you put a back_inserter
		or a container.begin(). copy will spit it out.

		Will invoke the assignment operator if the type name is user defined

	*/
#ifdef blk1
	std::vector<int>vec_int{ 1,2,5,8,7,9,3,19,10 };
	//std::vector<int>new_vec(vec_int.size());
	// What if I declare a empty container with 0 size?//
	// We need to use back inserter instead// 
	std::vector<int>new_vec{};
	auto itr1 = std::copy(vec_int.begin(), vec_int.end(), std::back_inserter(new_vec));
	for (size_t i = 0; i < new_vec.size(); i++) {
		std::cout << new_vec[i] << "\n";
	}
	// copy will trigger the assignment operator of a user-defined type//
	//Space_Ships ship1("First Ship", 3u);
	//Space_Ships ship2("Second Ship", 10u);
	//Space_Ships ship3("Third Ship", 5u);
	//std::vector<Space_Ships> fleet{};
	//std::vector<Space_Ships> new_fleet{};
	//fleet.push_back(ship1);
	//fleet.push_back(ship2);
	//fleet.push_back(ship3);
	//std::copy(fleet.begin(), fleet.end(), std::back_inserter(new_fleet));
	/* TD: toy around the itr1*/



#endif // blk1

#ifdef blk2
	/*
	* Syntax:
		std::transform has two versions:
			One can have unary predicate, the other is for binary predicate.

		OutputIterator std::transform(InputIterator f, InputIterator l, OutputIterator o, Fn u)

		OutputIterator std::transform(InputIterator f, InputIterator l, InputIterator g, OutputIterator o, Fn b)
			Third argument is the src2's begining iterator
			Fourth argument is the dst's begining iterator
	* return value:
	* Would be the arugment you supplied during the function call to represent the output container iterator
	*
	*
	*/

	std::vector<int>int_vec{ 1,2,4,3,5,8,9,10,54,22,11 };
	std::vector<int>fst_new_vec(int_vec.size());
	std::vector<int>sec_new_vec(int_vec.size());
	std::cout << "Unary trans\n";
	std::transform(int_vec.begin(), int_vec.end(), fst_new_vec.begin(), [](const int& src) {return src + 100; });
	std::for_each(fst_new_vec.begin(), fst_new_vec.end(), [](const int& s) {std::cout << s << "\n"; });
	std::cout << "Binary trans\n";
	std::transform(int_vec.begin(), int_vec.end(), fst_new_vec.begin(), sec_new_vec.begin(), [](const int& src1, const int& src2) {return src1 + src2 + 100; });
	std::for_each(sec_new_vec.begin(), sec_new_vec.end(), [](const int& s) {std::cout << s << "\n"; });

	/*
		fill
			fill won't return any values back
			syntax:
				void fill(ForwardIterator f, ForwardIterator l, const T& new_t)
				first two arguments are the range of the container you would fill into the
				The third argument is the value you would like to fill for the specific range

		fill_n
			syntax:
				OutputIterator fill_n(OutputIterator f, size n, const T& t)
				This time syntax is different:
					first argument is starting filling from
					second argument is how many elements to fill
					third argument is filled with what value
	*/
	std::vector<double>double_vec(5, 0.4);
	std::fill(double_vec.begin(), double_vec.end(), -0.1);
	std::for_each(double_vec.begin(), double_vec.end(), [](const double& src) {std::cout << src << std::endl; });
	std::fill_n(double_vec.begin(), 2, -0.2);
	std::for_each(double_vec.begin(), double_vec.end(), [](const double& src) {std::cout << src << std::endl; });

#endif // blk2

#ifdef blk3
	/*
		replace
		Syntax:
			void replace(ForwardIterator f, ForwardIterator l, const T& s, const T& t)
			first two are the range of the container
			third is the old value
			fourth is the new value you would like to replace by.

		replace_if()
		syntax:
			void replace_if(ForwardIterator f, ForwardIterator l, Fn predicate, const T& t)
			first two again are the range of the container
			!!!!!!third is the predicate!!!!!!!
			fourth is the new value you would like to replace.
	*/
	std::vector<int>int_vec{ 1,2,2,2,2,2,2,2,4,3,5,8,9,10,54,22,11 };
	std::replace(int_vec.begin(), int_vec.end(), 2, 200);
	std::for_each(int_vec.begin(), int_vec.end(), [](const int& s) {std::cout << s << "\n"; });
	std::cout << "====================================================================\n";
	std::replace_if(int_vec.begin(), int_vec.end(), [](const int& src) {return src > 100; }, 300);
	std::for_each(int_vec.begin(), int_vec.end(), [](const int& s) {std::cout << s << "\n"; });


#endif // blk3


#ifdef blk4
	/*
		!!!!remove!!!!
			remove elements by meeting the criteria from the range
			returns a past the end iteraor for the new end of the range.
			------------------------------------------------
			removing is done by shifting. After removal, the data will be gone, and the element will
			be moved to the end of the container.
			In the other word, only the data will be erased. But the physical size won't be changed.
			SO YOU NEED TO RESIZE THE CONTAINER YOURSELF.
			^^^^^^^^^^^^^^
		syntax:
		ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );
			Again, first two set the range
			The last one meaning comparing with this value.
	*/
	std::vector<int>int_vec{ 1,2,2,2,2,2,2,2,4,3,5,8,9,10,54,22,11 };
	std::cout << "====================================================================\n";
	std::cout << "the current size is " << int_vec.size() << std::endl;
	std::for_each(int_vec.begin(), int_vec.end(), [](const int& s) {std::cout << s << "\n"; });
	std::cout << "====================================================================\n";
	std::remove(int_vec.begin(), int_vec.end(), 2);
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	/*You think you will print the empty values out
	  But no, it won't. Because the logical size's end is updated after remove
	  So the int_vec.end() would return a adjusted logical size's end
	*/
	std::for_each(int_vec.begin(), int_vec.end(), [](const int& s) {std::cout << s << "\n"; });
	std::cout << "the current size is " << int_vec.size() << std::endl;
	std::cout << "====================================================================\n";
	
	/*
		use remove/remove_if with erase()
		It will help you resize as well
	*/
	std::vector<int>int_vec2{ 1,2,2,2,2,2,2,2,4,3,5,8,9,10,54,22,11 };
	std::cout << "====================================================================\n";
	std::cout << "the current size is " << int_vec2.size() << std::endl;
	std::for_each(int_vec2.begin(), int_vec2.end(), [](const int& s) {std::cout << s << "\n"; });
	std::cout << "====================================================================\n";
	// all the credits go to my classmate Xi Chen//
	// She came up this simplest logic//
	int_vec2.erase(std::remove(int_vec2.begin(), int_vec2.end(), 2),int_vec2.end());
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
	std::for_each(int_vec2.begin(), int_vec2.end(), [](const int& s) {std::cout << s << "\n"; });
	std::cout << "the current size is " << int_vec2.size() << std::endl;
	std::cout << "====================================================================\n";

#endif // blk4

#ifdef blk5
	
	/* 
	* std::merge
		merge needs to be sorted first 
		syntax:
			OutputIterator merge(InputIterator f1, InputIterator l1, InputIterator f2, InputIterator l2, OutputIterator o)	
	*/

	std::cout << "merged" << std::endl;
	int first[] = { 10,15,5,20,25 };
	int second[] = { 50,40,30,20,10 };
	std::vector<int> v(10);
	std::sort(first, first + 5); // 5, 10, 15, 20, 25
	std::sort(second, second + 5); // 10, 20, 30, 40, 50
	//OutputIterator merge(InputIterator f1, InputIterator l1, InputIterator f2, InputIterator l2, OutputIterator o)
	merge(first, first + 5, second, second + 5, v.begin());
	for (auto& x : v) {
		std::cout << x << ", ";
	}
	std::cout << std::endl;
#endif // blk5


#ifdef blk6
	/*
	std::accumulate
		This will return the accumulated result back
		It has two versions:

		T accumulate(InputIterator f, InputIterator l, T init)

		T accumulate( InputIt first, InputIt last, T init, BinaryOperation op );

		the first two again are the range
		the third is the initial accumulated value
		The forth must be a binary predicate
*/


	std::vector<int> int_vec{ 10,15,5,20,25 };



	int Sum = std::accumulate(int_vec.begin(), int_vec.end(), 0);
	std::cout << "The sum is: " << Sum << std::endl;
#endif // blk6



}