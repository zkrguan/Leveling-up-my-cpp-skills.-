#include <algorithm>
#include <vector>
#include <iostream>
/*
*
* STL algorithms are really powerful 
*	if you are looking at my notes. 
*	You are less likely to be able to write a logic faster than those poineers or senpais 
*	who wrote the STL algorithms. 
*	
*	STL's predicate can take anything callable and also the functions from <functional> 
* 
*/


/*

	non-modifying algorithms
	
*/

//#define blk1
#define blk2
#define blk3
#define blk4
#define blk5
#define blk6

int main() {
// count and count_if
#ifdef blk1
	/*
		std::count(beginIterator,endIterator,valueYouWantToCount)
		It will return 0 if the value you want to count does not exist in the container.
		Otherwise, it will return the occurence back.
	*/
	std::vector<int> vec_int = { 4,5,2,2,2,2,26,1,3,8,9,10,11 };
	//If the value exists.//
	int count1 = std::count(vec_int.begin(), vec_int.end(), 2);
	std::cout << "There are " << count1 << " '2' in this vector\n";
	//If the value does not exist// 
	int count2 = std::count(vec_int.begin(), vec_int.end(), 0);
	std::cout << "There are " << count2 << " '0' in this vector\n";
	// If it is a user-defined type, the == operator must be overloaded for comparing//
	class comparingEG {
		int m_value{};
	public:
		comparingEG(const int& src) :m_value{ src } {};
		// Put a break point next line, and you will see the std::count invoked the == operator//
		bool operator ==(const comparingEG& src) { return src.m_value == m_value; }
	};
	std::vector<comparingEG> vec_obj{};
	for (size_t i = 0; i < 5; i++){
		vec_obj.push_back(comparingEG(i + 90));
	}
	int count3 = std::count(vec_obj.begin(), vec_obj.end(), 90);
	std::cout << "There are " << count3 << " '90' in this vector\n";

	
	/*
	*	Just like std::count, 
		std::count_if(beginIterator,endIterator,unaryPredicate);
		It will return 0 if the value you want to count does not exist in the container.
		Otherwise, it will return the occurence back.

		A unary lambda is most common way. 
		The predicate must return a boolean back 
			If true, increase the count.
			If false, count remains the same

		Again you will need to make sure the comparison operators overloaded for your logic.
		Or you can set some getter to compare with a value you want to compare with.
	*/
	class comparingEG2 {
		int m_value{};
	public:
		comparingEG2(const int& src) :m_value{ src } {};
		bool operator ==(const comparingEG2& src) const { return src.m_value == m_value; }
		bool operator <(const int& src) const { return m_value < src; }
	};
	std::vector<comparingEG2> vec_obj_2{};
	for (size_t i = 0; i < 6; i++){
		vec_obj_2.push_back(comparingEG2(i + 20));
	}
	int count4 = std::count_if(vec_obj_2.begin(), vec_obj_2.end(), [](const comparingEG2& src) {return src < 30; });
	std::cout << "There are " << count4 << " elements greater than '30' in this vector\n";

#endif // blk1


#ifdef blk2
/*
	std::min_element() and std::max_element()
	These two will return an iterator back 
		That iterator will point at the min or max element. 
		If there are multiple mins and maxs, the first min ro max iterator will be returned. 

	std::min_element(beginingItr,endItr)
	std::max has the same syntax as min.

	You could have a predicate inside the min_element or max_element
		But it must be a BINARY callable.
			(para1 is the current element, and para2 is the next element)
*/
	int arr[] = { 1,2,3,4,5 };
	// Calling a std::min_element, and get the max.//
	auto max_itr = std::min_element(arr, arr + 5, [](const int& src1,const int& src2) {return src1>src2; });
	std::cout <<"used min_element to get the max instead with the predicate----------> " << *max_itr;
/*
	std::min() and std::max() are quite different comparing to min or max element
	These two return a element back instead of a iterator. 
	And you can not use ITERATOR to set the boundary for comparing. 
	But you still can have a predicate inside the funciton call of min or max.
		So you could the customized logic for comparing.
*/
	std::cout << "which is smaller? 999 or 1? ========> " << std::min(999, 1)<<std::endl;
	std::cout << "which is bigger? 999 or 1? ===========> " << std::min(999, 1, [](const int& src1, const int src2) {return src1 > src2; }) << std::endl;


#endif // blk2
}

