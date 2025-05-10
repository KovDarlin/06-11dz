#include <iostream>
#include <stdexcept>

using namespace std;

class Exception : public runtime_error {
public:
	explicit Exception(const string& msg) : runtime_error(msg) {}
};


struct Bale {
	int info;
	Bale* prev;
	Bale* next;
	Bale(int val) : info(val), prev(nullptr), next(nullptr) {}
};

class Link {
private:
	Bale* head;
	Bale* tail;
public:
	Link() :head(nullptr), tail(nullptr) {}
	~Link() {
		while (head) {
			Bale* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void push_back(int value) {
		try {
			Bale* newBale = new Bale(value);
			if (!head) {
				head = tail = newBale;
			}
			else {
				tail->next = newBale;
				newBale->prev = tail;
				tail = newBale;
			}
		}
		catch (const bad_alloc&) {
			throw Exception("Error! No memory");
		}
	}


	void pop_back() {
		if (!tail) {
			throw Exception("Error! Empty list");
		}
		Bale* temp = tail;
		if (head == tail) {
			head = tail = nullptr;
		}
		else {
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete temp;

	}

	void print() {
		Bale* temp = head;
		while (temp) {
			cout << temp->info << " ";
			temp = temp->next;
		}
		cout << "\n";
	}
};

int main() {
	Link element;
	try {
		element.push_back(1);
		element.push_back(2);
		element.push_back(3);
		element.print();

		element.pop_back();
		element.pop_back();
		element.pop_back();
		element.pop_back();
		
	}
	catch (const Exception& e) {
		cerr << e.what() << endl;
	}
	return 0;
}