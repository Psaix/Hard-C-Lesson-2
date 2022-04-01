/* _______________<< C++ Difficult parts Lesson 2 HomeWork >>_______________
(Coder - Psaix)
							<<<< Task 1 >>>> :
________________________________________________________________________________

	Implement a Swap template function that takes two pointers and performs 
 the swap of the values that ??these pointers points to (you need to exchange
 pointers themselves, variables must remain at the same memory addresses).
________________________________________________________________________________
 

							<<<< Task 2 >>>> :
________________________________________________________________________________

	Implement a SortPointers template function that takes a vector of pointers 
 and sorts pointers by the values ??they point to.
________________________________________________________________________________
 

							<<<< Task 3 >>>> :
________________________________________________________________________________

	Count the number of vowels in the book War and Peace. Use 4 to count ways:
 
		1: count_if and find
		2: count_if and for loop
		3: for and find loop
		4: 2 for loops
 
	Measure the time of each counting method and draw conclusions.

							<<<< Reference >>>> :

 count_if is an algorithmic function from the STL that takes 3 parameters: an iterator
 on start, end iterator, and unary predicate (a function that takes one parameter and
 returning type bool).find is a method of the string class that returns the position of
 the character (string) passed to as a parameter, in the source string. If the symbol is
 not found, then the method returns string::npos.
 __________________________________________________________________________________________*/
#include <iostream>
#include <vector>		//	For std::vector - vector is a sequence container that encapsulates dynamic size arrays.
#include <fstream>		//	For std::find, std::ifstream(input stream class to operate on files).
#include <string>		//	For getline and other string methods.Strings are objects that represent sequences of characters.
#include <algorithm>	//	For std::count_if, std::sort. 
#include "Timer.h"
#include <chrono>

using Open = std::fstream;	// Open is alias for std::fstream.

const std::vector <char> vLetters	 // Global vector that contains vowels. We will use this vector to compare it's char elements with char variables from "War and Peace.txt"
{ 'A', 'I', 'E', 'O', 'U', 'Y',		//	An entity declared outside any block has global scope, meaning that its name is valid anywhere in the code.
'a', 'i', 'e', 'o', 'u', 'y' };		//	This will help me to create functions for <Task 3>.

									

template<class T>								
void __fastcall Swap(T& ptr1, T& ptr2) {	// Template function "Swap" that swaps the pointers."Swap" takes two pointers as parameters and operate with them.
												
	auto swapPtr = ptr1;	//	"swapPtr" is a pointer created to copy pointer 1. We need this to save the value of pointer 1. 
	ptr1 = ptr2;           //	Pointer 1 copies pointer 2. After this row "ptr1" becomes "ptr2". That's why we neede "swapPtr" (address of the pointer 1 and address it points to).
	ptr2 = swapPtr;		   //	Now we can copy pointer 1 value into ponter 2. Pointers were swapped.			   
}

template<class T>											//	Template function "SwapPointers" that takes a vector of pointers and sorts pointers by the values ??they point to.
void __fastcall SortPointers(std::vector<T*>& vPointers) {	//  std::sort  - sorts the elements in the range[first, last) in non - descending order.
	std::sort(vPointers.begin(), vPointers.end(),			//	Here we go from the first element of the vector that was taken as a parameter to his last element.
		[](T* a, T* b) -> bool {return *a < *b;});			//  At each step, we check the truth of the statement (*a < *b). The lambda funtcion returns bool variable - true or false.
															//	If the statement is false - nothing happens. If the statement is true - elements are swapped.
}

template<class T>											 
void __fastcall PrintPointers(std::vector<T*>& vPointers) {	 //  "PrintPointers" template function takes vector of pointers and prints all of it's elements.
	std::cout << "Vector of pointers = { ";
	for (const auto& pt : vPointers)         //	auto "pt" - auto inititialized iterator for the vector of pointers(vPointers).This syntax is equal to (first[element], last[element])
		std::cout << *pt << ", ";			//  (pt) = address iterator points to, (*pt) = value iterator points to.
	std::cout << "}" << "\n\n";
}
              
// Iterator(from English iterator - enumerator) - an interface that provides access to the elements of a collection(array or container) and navigation through them


// "FindFunc" are bool functions. This functions will be used as a third parameter(unary predicate) for std::count_if method().
// If this funcs return "true"
// All of them take a char variable as a parameter - we need to count the amount of vowels from txt.file.

bool FindFunc_1(char cLetter)      
{
	auto it = std::find(vLetters.begin(), vLetters.end(), cLetter); //	If std::find.method() finds "cLetter" - char variable taken from txt.file as third function parameter
																	//	it will return the position of "cLetter" in the vector. Otherwise it will return "string::npos"(as a return value, used to indicate no matches)
	
	return (it != vLetters.end());      // iterator "it" is initialized by the result of find.method(). This statement returns true if "it" is not equal to vector.end()(npos). 
}


bool FindFunc_2(char cLetter)
{
	for (auto it = vLetters.begin(); it != vLetters.end(); it++) {   // for loop where itrator "it" goes from the first element to the last element of the vector
		if (*it == cLetter) {										// if the value of the element that "it" is equal to "cLetter" returns "true" and break. If we don't break out the loop
			return true;											// we will have incorrect count of returned "true's"
			break;
		}
	}

	return false;													// if no elements contains the value that is equal to "cLetter" the function will return "false"
}


// FindVowel functions - functions that count the vowels from "War and peace" in different ways. They take as parameter "std::fstream" variable that copies "txt.file" content.

void __fastcall FindVowel_1(Open& file)	
{
	Timer timer("Time");         // "timer" is an object of a class "Time"(#include "Timer.h"). This object will count the time needed for the function to complete. 
	try
	{
		if (!file.is_open())			// try to open the "fstream" stream. Throw exception if "file" wasn't opened.
		{
			throw std::logic_error("Can't open the file");
		}
		else
		{
			__int64 cVow{ 0 };									// If "file is opened, we declare "cVow" - this variable will store "count_if.method" results.
			std::string sVow;									// "sVow" is a string that will contain the whole file.
			while (!file.eof()) {
				getline(file, sVow);											// Get the whole book as string(char container) with getline.
				cVow += std::count_if(sVow.begin(), sVow.end(), FindFunc_1);	// Everytime count_if returns true - we increase the value of cVow
			}
			std::cout << cVow << " vowels found" << "\t";             // Output the amount of vowels this function found;
		}
	}
	catch (std::logic_error& Error) {							// Here we catch the exception
		std::cout << Error.what() << std::endl;
	}
	file.close();			// Closing file stream
	timer.print();			// Outputting the time this function was working
}


void __fastcall FindVowel_2(Open& file)
{
	Timer timer("Time");
	try
	{
		if (!file.is_open())
		{
			throw std::logic_error("Can't open the file");
		}
		else
		{
			__int64 cVow{0};
			std::string sVow;
			while (!file.eof()) {
				getline(file, sVow);
				cVow += std::count_if(sVow.begin(), sVow.end(), FindFunc_1);
			}
			std::cout << cVow << " vowels found" << "\t";
		}
	}
	catch (std::logic_error& Error) {
		std::cout << Error.what() << std::endl;
	}
	file.close();
	timer.print();
}

void __fastcall FindVowel_3(Open& file)
{
	Timer timer("Time");
	try
	{
		if (!file.is_open())
		{
			throw std::logic_error("Can't open the file");
		}
		else
		{
			int amount{0};             // amount stores the result of the for loop
			std::string sVow;
			while (!file.eof()) {
				getline(file, sVow);
				for (size_t i{0}; i < sVow.size(); i++)			// Here we use for loop to count the vowels.
				{
					if (FindFunc_1(sVow[i]))         // Everytime the std::find function returns true (each iteration new element is taken as a parameter) we increase amount;
						amount++;
				}
			}
			std::cout << amount << " vowels found" << "\t";
		}
	}
	catch (std::logic_error& Error) {
		std::cout << Error.what() << std::endl;
	}
	file.close();
	timer.print();
}


void __fastcall FindVowel_4(Open& file)
{
	Timer timer("Time");
	try
	{
		if (!file.is_open())
		{
			throw std::logic_error("Can't open the file");
		}
		else
		{
			int amount{0};
			std::string sVow;
			while (!file.eof()) {
				getline(file, sVow);
				for (size_t i{0}; i < sVow.size(); i++)     // Two for loops implementation
				{
					if (FindFunc_2(sVow[i]))
						amount++;
				}
			}
			std::cout << " " << amount << " vowels found" << "\t";
		}
	}
	catch (std::logic_error& Error) {
		std::cout << Error.what() << std::endl;
	}
	file.close();
	timer.print();
}

int main() {

	int a{10}, b{25};
	int *ptr1{&a}, *ptr2{&b};

	std::cout << "<><><><><><><><><><>:: Variables info ::<><><><><><><><><><>" << "\n\n";
	std::cout << "Variable a = " << a << " and &a = (" << &a << ")" << "\n";
	std::cout << "Variable b = " << b << " and &b = (" << &b << ")" << "\n\n";

	std::cout << "<><><><><><><><><><>: Pointers data before swap function ::<><><><><><><><><><>" << "\n\n";
	std::cout << "Pointer *ptr1 = " << *ptr1 << " and ptr1 adress =(" << ptr1 << ")" << "\n";
	std::cout << "Pointer *ptr2 = " << *ptr2 << " and ptr2 adress =(" << ptr2 << ")" << "\n\n";

	Swap(ptr1, ptr2);

	std::cout << "<><><><><><><><><><>:: Pointers data after swap function ::<><><><><><><><><><>" << "\n\n";
	std::cout << "Pointer *ptr1 = " << *ptr1 << " and ptr1 adress =(" << ptr1 << ")" << "\n";
	std::cout << "Pointer *ptr2 = " << *ptr2 << " and ptr2 adress =(" << ptr2 << ")" << "\n\n";


	std::vector<int> varVector{ 4, 2, 5, 9, 1, 7, 10, 12, 3 };

	const size_t SIZE = varVector.size();

	std::vector<int*> ptVector;
	for (size_t i{0}; i < SIZE; i++)
		ptVector.push_back(&varVector[i]);


	std::cout << "<><><><><><><><><><>:: Vector of pointers before sorting function ::<><><><><><><><><><>" << "\n\n";

	PrintPointers(ptVector);
	SortPointers(ptVector);

	std::cout << "<><><><><><><><><><>:: Vector of pointers after sorting function ::<><><><><><><><><><>" << "\n\n";

	PrintPointers(ptVector);


	const std::string text = "War and peace.txt";

	Open file_1(text), file_2(text), file_3(text), file_4(text);


	std::cout << "Func1.result:" << "\t";
	FindVowel_1(file_1);

	std::cout << "\n";

	std::cout << "Func2.result:" << "\t";
	FindVowel_2(file_2);

	std::cout << "\n";
	
	std::cout << "Func3.result:" << "\t";
	FindVowel_3(file_3);

	std::cout << "\n";

	std::cout << "Func4.result:" << "\t";
	FindVowel_4(file_4);

	std::cout << "\n";

	return 0;
}