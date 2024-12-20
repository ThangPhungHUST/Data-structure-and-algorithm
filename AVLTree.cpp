#include <iostream>
using namespace std;

typedef struct AVLNode {
	int key;
	int height;
	AVLNode* right;
	AVLNode* left;
}AVLNode;

int height(AVLNode* t) {
	return t == NULL ? 0 : t->height;
}

int max(int a, int b) {
	return a >= b ? a : b;
}

int isBalance(AVLNode* t) {
	return t == NULL ? 0 : height(t->left) - height(t->right);
}

void rotateWithLeftChild(AVLNode*& k2) {
	AVLNode* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2 = k1;
}
void rotateWithRightChild(AVLNode*& k2) {
	AVLNode* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2 = k1;
}
void DoubleWithLeftChild(AVLNode*& k3) {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}
void DoubleWithRightChild(AVLNode*& k3) {
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}
void balance(AVLNode*& t) {
	int b = isBalance(t);
	if (b > 1) {
		if (isBalance(t->left) >= 0) {
			rotateWithLeftChild(t);
		}
		else {
			DoubleWithLeftChild(t);
		}
	}
	if (b < -1) {
		if (isBalance(t->right) <= 0) {
			rotateWithRightChild(t);
		}
		else {
			DoubleWithRightChild(t);
		}
	}
	t->height = max(height(t->left), height(t->right)) + 1;
	return;
}

AVLNode* createNode(int key) {
	AVLNode* t = new AVLNode;
	t->key = key;
	t->right = t->left = NULL;
	t->height = 0;
	return t;
}

void insert(AVLNode*& t, int key) {
	if (t == NULL) {
		t = createNode(key);
	}
	else if (key <= t->key) {
		insert(t->left, key);
	}
	else if (key > t->key) {
		insert(t->right, key);
	}
	t->height = max(height(t->left), height(t->right)) + 1;
}

void printPreO(AVLNode* t) {
	if (t) {
		cout << t->key << " ";
		printPreO(t->left);
		printPreO(t->right);
	}
}
void printInO(AVLNode* t) {
	if (t) {
		printInO(t->left);
		cout << t->key << " ";
		printInO(t->right);
	}
}

void printPostO(AVLNode* t) {
	if (t) {
		printPostO(t->left);
		printPostO(t->right);
		cout << t->key << " ";
	}
}

void insert_balance(AVLNode*& t, int key) {
	if (t == NULL) {
		t = createNode(key);
	}
	else if (key <= t->key) {
		insert_balance(t->left, key);
	}
	else if (key > t->key) {
		insert_balance(t->right, key);
	}
	balance(t);
}

int main() {
	int A[12] = { 17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58 };
	
	AVLNode* t = NULL;
	for (int i = 0; i < 12; i++) {
		insert(t, A[i]);
	}
	printPreO(t);
	bool yes = (isBalance(t) <= 1) && (isBalance(t) >= -1);
	cout << "\nCay " << (yes ? "da " : "chua ") << "can bang" << endl;
	
	cout << "-----------" << endl;
	
	if (!yes) {
		AVLNode* q = NULL;
		for (int j = 0; j < 12; j++) {
			insert_balance(q, A[j]);
		}
		cout << "Cay " << ((isBalance(q) <= 1) && (isBalance(q) >= -1) ? "da " : "chua ") << "can bang" << endl;
		printPreO(q);
	}
}