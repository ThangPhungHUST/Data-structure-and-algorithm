#include <iostream>
using namespace std;

typedef struct nodeDT {
	int bac;
	double heso;
	nodeDT* next;
};

typedef struct listDT {
	nodeDT* firstDT;
};

void init(listDT& list) {
	list.firstDT = 0;
}

void dispose(listDT& p) {
	while (p.firstDT) {
		nodeDT* n = p.firstDT;
		p.firstDT = n->next;
		delete[] n;
	}
}

void append(listDT& p, int bac, double heso) {
	nodeDT* n = new nodeDT;
	n->bac = bac;
	n->heso = heso;
	n->next = 0;
	if (p.firstDT) {
		nodeDT* current = p.firstDT;
		while (current->next) {
			current = current->next;
		}
		current->next = n;
	}
	else {
		p.firstDT = n;
	}
}

void print(listDT& p) {
	cout << "f(x) = ";
	nodeDT* current = p.firstDT;
	while (current->next) {
		cout << current->heso << "x^" << current->bac << " + ";
		current = current->next;
	}
	cout << current->heso;
}

int main() {
	listDT list;
	init(list);
	int n;
	cout << "Nhap bac da thuc: ";
	cin >> n;
	for (int i = 0; i < n + 1; i++) {
		double a;
		cout << "Nhap he so bac " << n - i << ": ";
		cin >> a;
		if (a != 0) {
			append(list, n - i, a);
		}
	}
	print(list);
	dispose(list);
}
