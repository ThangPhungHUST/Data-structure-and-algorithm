#include <iostream>
using namespace std;

bool mystrcmp(const char* s1, const char* s2) {
	int i = 0;
	while (s1[i] && s2[i]) {
		if (s1[i] != s2[i++]) {
			return false;
		}
	}
	return true;
}

void mystrcpy(char* s1, const char* s2) {
	int i = 0;
	while (s2[i]) {
		s1[i] = s2[i++];
	}
	s1[i] = '\0';
}

void mygets(char* s, int maxLen) {
	int i = 0;
	char c;
	while ((c = getchar()) != '\n' && i < maxLen - 1) {
		s[i++] = c;
	}
	s[i] = '\0';
}

int mystrlen(const char* s) {
	int i = 0, c = 0;
	while (s[i++]) {
		c++;
	}
	return c;
}

struct Node {
	char* title;
	int start;
	int end;
	int numchild;
	Node** children;
	~Node() {
		delete[] title;
		if (children != nullptr) {
			for (int i = 0; i < numchild; ++i) {
				delete children[i];
			}
			delete[] children;
		}
	}
};

void print(Node* node, int level = 0) {
	if (node == NULL) {
		return;
	}
	for (int i = 0; i < level; i++) {
		cout << "    ";
	}
	cout << node->title << (level == 0 ? "" : " ..........") << " (" << node->start << "-" << node->end << ")" << endl;
	for (int j = 0; j < node->numchild; j++) {
		print(node->children[j], level + 1);
	}
}

void create(Node* root) {
	const int MAX_TITLE_LEN = 256;
	char tmp[MAX_TITLE_LEN];
	
	cout << "Nhap tieu de: ";
	mygets(tmp, MAX_TITLE_LEN);
	
	int len = mystrlen(tmp);
	root->title = new char[len + 1];
	mystrcpy(root->title, tmp);

	cout << "Nhap so trang bat dau: ";
	cin >> root->start;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Nhap so trang ket thuc: ";
	cin >> root->end;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cout << "Nhap so luong de muc con (Nhap 0 de ket thuc): ";
	cin >> root->numchild;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	if (root->numchild > 0) {
		root->children = new Node * [root->numchild];
		for (int i = 0; i < root->numchild; i++) {
			root->children[i] = new Node;
			create(root->children[i]);
		}
	}
}

int countchapter(Node* root) {
	return root->numchild;
}

void findlargestchapter(Node* root) {
	if (!root) {
		return;
	}
	int largest = 0;
	int j = 0;
	for (int i = 0; i < root->numchild; i++) {
		if (root->children[i]->end - root->children[i]->start + 1 > largest) {
			largest = root->children[i]->end - root->children[i]->start + 1;
			j = i;
		}
	}

	cout << "Chuong dai nhat cua cuon sach la: " << root->children[j]->title << " voi " << largest << " trang." << endl;
}

bool find_and_remove_title(Node* root, const char* s, char* s1, int& total) {
	if (!root) return false;

	for (int i = 0; i < root->numchild; i++) {
		if (mystrcmp(root->children[i]->title, s)) {
			total = root->children[i]->end - root->children[i]->start + 1;
			for (int j = i; j < root->numchild - 1; j++) {
				root->children[j] = root->children[j + 1];
				root->children[j]->start -= total;
				root->children[j]->end -= total;
			}
			root->children[root->numchild - 1] = NULL;
			root->numchild--;
			mystrcpy(s1, root->children[i]->title);
			return true;
		}
		else  {
			find_and_remove_title(root->children[i], s, s1, total);
		}
	}
}

bool isinthis(Node* root, const char* s) {
	if (!root) return false;
	if (mystrcmp(root->title, s)) {
		return true;
	}
	else {
		for (int i = 0; i < root->numchild; i++) {
			isinthis(root->children[i], s);
		}
	}
}
void update(Node* root, const char* s) {
	int total = 0;
	int c = 0;
	char* s1 = new char[256];
	if (find_and_remove_title(root, s, s1, total)) {
		cout << "Da xoa muc luc: " << s << endl;
		for (int i = 0; i < root->numchild; i++) {
			bool trueorfalse = isinthis(root->children[i], s1);
			if (trueorfalse || c) {
				root->children[i]->start -= ((root->children[i]->start == 1) || trueorfalse ? 0 : total);
				root->children[i]->end -= total;
				c = 1;
			}
		}
		root->end -= total;
	}
	else {
		cout << "Khong tim thay" << endl;
	}
}


int main() {
	Node* root = new Node;
	create(root);
	print(root);
	cout << "So chuong cua cuon sach la: " << countchapter(root) << endl;
	findlargestchapter(root);
	update(root, "sec1");
	print(root);
	delete root;
	return 0;
}