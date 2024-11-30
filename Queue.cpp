#include <iostream>
using namespace std;

typedef struct DS_hanghoa {
	char s[30];
	int soluong;
}DS_hanghoa;

typedef struct Node {
	int maKH;
	double cost;
	DS_hanghoa* p;
	Node* next;
}Node;

typedef struct Queue {
	int MAX_SIZE;
	Node* front;
	Node* rear;
}Queue;

bool mystrcmp(char* a,  const char* b) {
	int i = 0;
	while (a[i] && b[i]) {
		if (a[i] != b[i++]) {
			return false;
		}
	}
	return true;
}

void init(Queue* q, int MAX) {
	q->front = q->rear = NULL;
	q->MAX_SIZE = MAX;
}

void del(Queue* q) {
	while (q->front != NULL) {
		Node* tmp = q->front;
		q->front = tmp->next;
		delete tmp;
	}
	q->rear = NULL;
}

bool Isempty(Queue* q) {
	return q->front == NULL;
}

int count_queue(Queue* q) {
	Node* tmp = q->front;
	int c = 0;
	while (tmp) {
		c++;
		tmp = tmp->next;
	}
	return c;
}

bool Isfull(Queue* q) {
	return count_queue(q) == q->MAX_SIZE;
}

void append(Queue* q, Node* p) {
	if (Isempty(q)) {
		q->front = q->rear = p;
	}
	else if (Isfull(q)){
		cout << "Day" << endl;
	}
	else {
		q->rear->next = p;
		q->rear = p;
	}
}

void remove(Queue* q) {
	if (Isempty(q)) {
		cout << "Empty" << endl;
		return;
	}
	Node* tmp = q->front;
	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	delete tmp;
}

void print(Queue* q) {
	Node* tmp = q->front;
	while (tmp) {
		cout << tmp->maKH << '\t' << tmp->cost << endl;
		tmp = tmp->next;
	}
}

double total(Queue* q) {
	double c = 0;
	Node* tmp = q->front;
	while (tmp) {
		c += tmp->cost;
		tmp = tmp->next;
	}
	return c;
}

char* prompt(Queue* q) {
	char* txt = new char[3];
	Node* tmp = q->front;
	while (true) {
		cout << "Is " << tmp->maKH << " paid?" << endl;
		cin >> txt;
		if (mystrcmp(txt, "yes") || mystrcmp(txt, "no")) {
			tmp = tmp->next;
			break;
		}
	}
	return txt;
}

void Ispaid(Queue* q) {
	char* txt = new char[3];
	Node* tmp = q->front;
	while (tmp) {
		txt = prompt(q);
		if (mystrcmp(txt, "yes")) {
			remove(q);
			cout << "Da xoa khach hang khoi hang cho" << endl;
			print(q);
			tmp = tmp->next;
		}
		else {
			cout << "Da goi bao ve" << endl;
		}
	}
	delete[] txt;
}

int Isinlist(DS_hanghoa* p, const char* s) {
	int i = 0;
	while (p[i].s != NULL) {
		if (mystrcmp(p[i].s, s)) {
			return p[i].soluong;
		}
		i++;
	}
	return 0;
}

void count_SP(Queue* q, const char* s) {
	int c = 0;
	Node* tmp = q->front;
	while (tmp) {
		c += Isinlist(tmp->p, "A");
		tmp = tmp->next;
	}
	cout << "So luong san pham " << *s << " da ban duoc la: " << c << endl;
}

int main() {
	Queue q;
	init(&q, 3);
	DS_hanghoa p1[5] = { {"A", 30}, {"B", 45}, {"C", 67}, {"D", 89}, {"E", 76}};
	DS_hanghoa p2[5] = { {"F", 13}, {"B", 11}, {"J", 8}, {"G", 0}, {"E", 6} };
	DS_hanghoa p3[5] = { {"A", 27}, {"H", 16}, {"C", 9}, {"K", 72}, {"E", 2} };
	Node p = { 12, 3.7, p1, NULL};
	Node a = { 113, 8.9, p2, NULL };
	Node b = { 99, 17.8, p3, NULL };
	append(&q, &p);
	append(&q, &a);
	append(&q, &b);
	print(&q);
	cout << "-------\n" << endl;
	cout << "Tong so tien thu ngan thu duoc la: " << total(&q) << endl;
	cout << "-------\n" << endl;
	Ispaid(&q);
	cout << "-------\n" << endl;
	count_SP(&q, "A");
	return 0;
}