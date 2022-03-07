#include <iostream>
#include "List.h"
#include <string>

using namespace std;

int main()
{
	int n;
	List q;
	string frase("What do you want to do?\n"
		"If you want to add element print \"1\"\n"
		"If you want to delete the first element in the queue print \"2\"\n"
		"If you want to get information about head of queue print \"3\"\n"
		"If you want to know size of queue print \"4\"\n"
		"If you want to check operation of copy constructors and moving functions print \"5\"\n"
		"If you want to clear queue print \"6\"\n"
		"if you want to finish testing print any other number\n");
	cout << "You have priority queue.";
	do {
		cout << frase;
		cin >> n;
		if (n == 1) {
			int data, pr;
			cout << "Set element data and priority (high - 1, medium - 2, low - 3)\nData:\n";
			cin >> data;
			cout << "Priority:\n";
			cin >> pr;
			if (pr == 1) {
				q.push_back(data, priority::high);
			}
			else if (pr == 2) {
				q.push_back(data, priority::medium);
			}
			else if (pr == 3) {
				q.push_back(data, priority::low);
			}
			else {
				cout << "wrong priority\n";
			}
			cout << "your queue:\n" << q<<endl;
		}
		else if (n == 2) {
			q.pop_front();
			cout << "your queue:\n" << q<<endl;
		}
		else if (n == 3) {
			auto inf = q.GetHead();
			if (inf.second == priority::high) {
				cout << "Head data:\n" << inf.first << "\nHead priority:\nHigh\n";
			}else if (inf.second == priority::medium) {
				cout << "Head data:\n" << inf.first << "\nHead priority:\nMedium\n";
			}else if (inf.second == priority::low) {
				cout << "Head data:\n" << inf.first << "\nHead priority:\nLow\n";
			}
		}
		else if (n == 4) {
			cout << "Size of queue = " << q.GetSize() << "\nNumber of low elements = " << q.GetLowSize() << "\nNumber of medium elements = " << q.GetMediumSize() << "\nNumber of high elements = " << q.GetHighSize() << endl;
		}
		else if (n == 5) {
			cout << "Your queue\n" << q<<endl;
			List q1(q);
			cout << "Copied queue\n" << q1<<endl;
			List q2(move(q));
			cout << "Moved queue\n" << q2<<endl;
			q = move(q2);
			cout << "Moved back queue\n" << q << endl;
			List q3;
			cout << "New empty queue\n" << q3 << endl;
			q3 = q;
			cout << "Copied queue\n" << q3 << endl;
		}
		else if (n == 6) {
			q.clear();
			cout << "Your queue is empty now!" << endl;
		}
	} while (n != 0);
}