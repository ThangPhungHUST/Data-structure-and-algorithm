#include <iostream>
using namespace std;

typedef struct tms {
	unsigned int sec;
	unsigned int min;
	unsigned int hour;
	unsigned int day;
	unsigned int month;
	unsigned int year;
}tms;

typedef struct fl {
	char name[20];
	char location[50];
	double size;
	tms time;
	fl* next;
}fl;

typedef struct fl_D{
	fl* first_file;
}fl_D;

void mystrcpy(char* source, const char* data, int source_size) {
	int i = 0;
	while (data[i] && i < source_size - 1) {
		source[i] = data[i];
		i++;
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

void init(fl_D* fileD) {
	fileD->first_file = 0;
}

void dispose(fl_D* fileD) {
	while (fileD->first_file) {
		fl* tmp = fileD->first_file;
		fileD->first_file = tmp->next;
		delete[] tmp;
	}
}

int cmp_time(tms tm1, tms tm2) {
	if (tm1.year != tm2.year) {
		return tm1.year - tm2.year;
	}
	else if (tm1.month != tm2.month) {
		return tm1.month - tm2.month;
	}
	else if (tm1.day != tm2.day) {
		return tm1.day - tm2.day;
	}
	else if (tm1.hour != tm2.hour) {
		return tm1.hour - tm2.hour;
	}
	else if (tm1.min != tm2.min) {
		return tm1.min - tm2.min;
	}
	else {
		return tm1.sec - tm2.sec;
	}
}


int cmp_file(fl* p1, fl* p2) {
	if (mystrcmp(p1->name, p2->name)) {
		return 1;
	}
	else if (p1->size == p2->size) {
		return 1;
	}
	else if (cmp_time(p1->time, p2->time) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void append(fl_D* fileD, const char* name, const char* location, double size, unsigned int sec, unsigned int min, unsigned int hour, unsigned int day, unsigned int month, unsigned int year) {
	fl* newfile = new fl;
	mystrcpy(newfile->name, name, 20);
	mystrcpy(newfile->location, "D:\\Document", 50);
	newfile->size = size;
	newfile->time = { sec, min, hour, day, month, year };
	newfile->next = 0;
	if (fileD->first_file) {
		fl* p = fileD->first_file;
		while (p->next) {
			p = p->next;
		}
		p->next = newfile;
	}
	else {
		fileD->first_file = newfile;
	}
}

int is_in_file(fl_D* source, fl* file) {
	fl* p = source->first_file;
	while (p) {
		if (cmp_file(p, file) == 1) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}

tms find_max_time(fl_D* fileD, fl_D* sortfile) {
	fl* p = fileD->first_file;
	tms max = {0, 0, 0, 0, 0, 0};
	while (p) {
		if (is_in_file(sortfile, p) == 0) {
			if (cmp_time(p->time, max) > 0) {
				max = p->time;
			}
		}
		p = p->next;
	}
	return max;
}

fl_D* sort_time(fl_D* fileD) {
	fl_D* sortfiles = new fl_D;
	sortfiles->first_file = NULL;
	fl* p = fileD->first_file;
	tms max = find_max_time(fileD, sortfiles);
	while (p) {
		fl* k = fileD->first_file;
		while (k) {
			if (cmp_time(k->time, max) == 0) {
				append(sortfiles, k->name, k->location, k->size, k->time.sec, k->time.min, k->time.hour, k->time.day, k->time.month, k->time.year);
				max = find_max_time(fileD, sortfiles);
			}
			k = k->next;
		}
		p = p->next;
	}
	return sortfiles;
}

double sum_size(fl_D * fileD) {
	double total = 0;
	fl* p = fileD->first_file;
	while (p) {
		total += p->size;
		p = p->next;
	}
	return total;
}

double find_max_size(fl_D* fileD, fl_D* sortfile) {
	double max = 0;
	fl* p = fileD->first_file;
	while (p) {
		if (is_in_file(sortfile, p) == 0) {
			if (p->size >= max) {
				max = p->size;
			}
		}
		p = p->next;
	}
	return max;
}

fl_D* sort_size(fl_D* fileD) {
	fl_D* sortfiles = new fl_D;
	sortfiles->first_file = NULL;
	double max = find_max_size(fileD, sortfiles);
	fl* p = fileD->first_file;
	while (p) {
		fl* q = fileD->first_file;
		while (q) {
			if (q->size == max) {
				append(sortfiles, q->name, q->location, q->size, q->time.sec, q->time.min, q->time.hour, q->time.day, q->time.month, q->time.year);
				max = find_max_size(fileD, sortfiles);
			}
			q = q->next;
		}
		p = p->next;
	}
	return sortfiles;
}

void remove_size(fl_D* fileD) {
	fl* ptr = fileD->first_file;
	while (ptr->next->next) {
		ptr = ptr->next;
	}
	fl* p = ptr->next;
	ptr->next = NULL;
	delete p;
}

void save_USB(fl_D* fileD, double sz) {
	while (sum_size(fileD) > sz) {
		remove_size(fileD);
	}
}

void print(fl_D* fileD) {
	fl* p = fileD->first_file;
	while (p) {
		cout << p->name << '\t' << p->location << '\t' << p->size << '\t' << p->time.day << '/' << p->time.month << '/' << p->time.year << endl;
		p = p->next;
	}
}

int main() {
	fl_D fileD;
	init(&fileD);
	append(&fileD, "Anh1.jpg", "D:\\Document", 0.6, 11, 24, 11, 15, 11, 2024);
	append(&fileD, "Anh2.png", "D:\\Document", 1.2, 34, 22, 11, 15, 11, 2024);
	append(&fileD, "Algorithm.pdf", "D:\\Document", 29, 45, 36, 11, 15, 11, 2024);
	append(&fileD, "Note.txt", "D:\\Document", 2, 29, 8, 19, 17, 12, 2024);
	append(&fileD, "Powerpoint", "D:\\Document", 15, 37, 12, 19, 14, 10, 2024);
	print(&fileD);
	cout << "----------" << endl;
	append(&fileD, "Video AI", "D:\\Hoc tap\\Chuyen nganh", 29.875, 12, 42, 15, 16, 11, 2024);
	fl_D* newfileD = sort_time(&fileD);
	print(newfileD);
	cout << "----------" << endl;
	cout << "Tong kich thuoc cac file trong thu muc la: " << sum_size(&fileD) << endl;
	newfileD = sort_size(&fileD);
	cout << "----------" << endl;
	print(newfileD);
	cout << "----------" << endl;
	save_USB(newfileD, 32);
	print(newfileD);
	dispose(&fileD);
	dispose(newfileD);
	return 0;
}