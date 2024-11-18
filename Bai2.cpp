#include <iostream>
using namespace std;

typedef struct tu {
	char s[50];
	tu* next;
}tu;

typedef struct cau {
	tu* first;
}cau;

void mystrcpy(char* source, const char* data) {
	int i = 0;
	while (data[i]) {
		source[i] = data[i++];
	}
	source[i] = '\0';
}

int mystrcmp(const char* s1, const char* s2) {
	int i = 0;
	while (s2[i] && s1[i]) {
		if (s1[i] != s2[i++]) {
			return 0;
		}
	}
	return 1;
}

int mystrlen(const char* s) {
	int c = 0;
	while (*s++) {
		c++;
	}
	return c;
}

void init(cau* cau) {
	cau->first = 0;
}

void dispose(cau* cau) {
	while (cau->first) {
		tu* p = cau->first;
		cau->first = p->next;
		delete[] p;
	}
}

void append(cau* cau, const char* data) {
	tu* newtu = new tu;
	mystrcpy(newtu->s, data);
	newtu->next = 0;
	if (cau->first) {
		tu* tmp = cau->first;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = newtu;
	}
	else {
		cau->first = newtu;
	}
}

int find_tu(cau* cau, const char* data) {
	int c = 0;
	tu* p = cau->first;
	while (p) {
		if (mystrcmp(p->s, data)) {
			c++;
		}
		p = p->next;
	}
	return c;
}

int find_max(cau* cau) {
	int max = 0;
	tu* p = cau->first;
	while (p) {
		int c = find_tu(cau, p->s);
		if (c >= max) {
			max = c;
		}
		p = p->next;
	}
	return max;
}

int check_tulay(const char* s) {
	int n = int(mystrlen(s) / 2);
	int m = n + 1;
	for (int i = 0; i < n; i++) {
		if (s[i] != s[i + m]) {
			return 0;
		}
	}
	return 1;
}

void delete_tulay(cau* cau) {
	tu* p = cau->first;
	while (p) {
		if (check_tulay(p->s)) {
			p->s[int(mystrlen(p->s) / 2)] = '\0';
		}
		p = p->next;
	}
}

void find_the_most(cau* cau) {
	tu* p = cau->first;
	int max = find_max(cau);
	delete_tulay(cau);
	while (p) {
		int c = 1;
		tu* q = p->next;
		while (q) {
			if (mystrcmp(p->s, q->s)) {
				c++;
			}
			q = q->next;
		}
		if (c >= max) {
			cout << "Tu xuat hien nhieu nhat (" << max << " lan) la: " << p->s << endl;
		}
		p = p->next;
	}
}

void print(cau* cau) {
	tu* p = cau->first;
	while (p) {
		cout << p->s << endl;
		p = p->next;
	}
}

int check(cau* source, const char* data) {
	int c = 1;
	tu* p = source->first;
	while (p) {
		if (mystrcmp(p->s, data)) {
			c = 0;
			break;
		}
		p = p->next;
	}
	return c;
}

void count_tu(cau* c) {
	cau count_cau;
	init(&count_cau);
	tu* p = c->first;
	while (p) {
		if (check(&count_cau, p->s)) {
			cout << p->s << " xuat hien " << find_tu(c, p->s) << " lan." << endl;
			append(&count_cau, p->s);
		}
		p = p->next;
	}
	
}

int main() {
	cau TV;
	init(&TV);
	append(&TV, "xanh xanh");
	append(&TV, "do");
	append(&TV, "xanh");
	append(&TV, "vang vang");
	append(&TV, "xanh");
	append(&TV, "do do");
	append(&TV, "do");
	find_the_most(&TV);
	print(&TV);
	count_tu(&TV);
}