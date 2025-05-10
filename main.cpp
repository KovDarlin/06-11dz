#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <new>

using namespace std;

class MyClass {
public:
	virtual const char* what() const = 0;
};

class MathClass : public MyClass {
public:
	const char* what() const override {
		return "Math error!";
	}
};

class ZeroClass : public MathClass {
public:
	const char* what() const override {
		return "Division by zero!";
	}
};

class NegativeClass : public MathClass {
public:
	const char* what() const override {
		return "Negative sqrt error!";
	}
};

class FileClass : public MyClass {
public:
	const char* what() const override {
		return "I can`t found file error!";
	}
};

class IndexClass : public MyClass {
public:
	const char* what() const override {
		return "Index out of range error!";
	}
};

void testMath(int a, int b) {
	if (b == 0) throw ZeroClass();
	cout << "Division result: " << a / b << endl;

	if (a < 0) throw NegativeClass();
	cout << "Sqrt of a: " << sqrt(a) << endl;
}

void testMemory() {
	int* bigArray = new(nothrow) int[100000000];
	if (!bigArray) throw FileClass();
	delete[] bigArray;
}

void testFile() {
	ifstream file("nofile.txt");
	if (!file.is_open()) {
		throw FileClass();
	}
	file.close();
}

void testIndex(int index, int size) {
	if (index < 0 || index >= size) throw IndexClass();
	cout << "Index range: " << index << endl;
}

int main() {
	try {
		testMath(12, 2);         
		testMath(-5, 2);        
		testMemory();           
		testFile();             
		testIndex(10, 3);        

	}
	catch (MyClass& e) {
		cerr << e.what() << endl;
	}

	return 0;
}