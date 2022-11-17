#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct Node {
	char data;
	Node* left, * right;
	Node(char data) {
		this->data = data;
		this->left = nullptr;
		this->right = nullptr;
	}
	Node(char data, Node* left, Node* right) {
		this->data = data;
		this->left = left;
		this->right = right;
	}
};
bool isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
void postorder(Node* root)
{
	if (root == nullptr) {
		return;
	}
	postorder(root->left);
	postorder(root->right);
	cout << root->data;
}

void inorder(Node* root)
{
	if (root == nullptr) {
		return;
	}	
	if (isOperator(root->data)) {
		cout << "(";
	}

	inorder(root->left);
	cout << root->data;
	inorder(root->right);
	
	if (isOperator(root->data)) {
		cout << ")";
	}
}
Node* construct(string infix)
{
	queue<char>postfixQueue;
	stack<char>Buff;
	for (char c : infix) {		
		if (isOperator(c)) {
			if (Buff.empty() || Buff.top() == '(') {
				Buff.push(c);
			}
			else if ((Buff.top() == '+' || Buff.top() == '-') && (c == '*' || c == '/')) {
				Buff.push(c);
			}
			else if ((Buff.top() == '+' || Buff.top() == '-' || Buff.top() == '*' || Buff.top() == '/') && (c == '^')) {
				Buff.push(c);
			}
			else if (Buff.top() == '^' && c == '^') {
				while (!Buff.empty() && Buff.top() != '+' && Buff.top() != '-' && Buff.top() != '*' && Buff.top() != '/' && Buff.top() != '(') {
					postfixQueue.push(Buff.top());
					Buff.pop();
				}
				Buff.push(c);
			}
			else if ((Buff.top() == '^' || Buff.top() == '*' || Buff.top() == '/') && (c == '*'||c=='/')) {
				while (!Buff.empty() && Buff.top() != '+' && Buff.top() != '-' && Buff.top() != '(') {
					postfixQueue.push(Buff.top());
					Buff.pop();
				}
				Buff.push(c);
			}
			else if ((Buff.top() == '^' || Buff.top() == '*' || Buff.top() == '/'|| Buff.top() == '+' || Buff.top() == '-') && (c == '+' || c == '-')) {
				while (!Buff.empty() && Buff.top() != '(') {
					postfixQueue.push(Buff.top());
					Buff.pop();
				}
				Buff.push(c);
			}
		}
		else {
			if (c == '(') {
				Buff.push(c);
			}
			else if (c == ')') {
				while (!Buff.empty() && Buff.top() != '(') {
					postfixQueue.push(Buff.top());
					Buff.pop();
				}
				if (Buff.top() == '(') {
					Buff.pop();
				}
			}
			else
				postfixQueue.push(c);
		}
	}
	while (!Buff.empty()) {
		postfixQueue.push(Buff.top());
		Buff.pop();
	}
	string postfix;

	while (!postfixQueue.empty()) {
		postfix.push_back(postfixQueue.front());
		postfixQueue.pop();
	}
    
    if (postfix.length() == 0) {
        return nullptr;
    }


    stack<Node*> s;
    
    for (char c : postfix)
    {        
        if (isOperator(c))
        {            
            Node* x = s.top();
            s.pop();

            Node* y = s.top();
            s.pop();
            
            Node* node = new Node(c, y, x);

            s.push(node);
        }
        else {
            s.push(new Node(c));
        }
    }
    return s.top();

}

void count(Node* root) {
	if (root == nullptr) {
		return;
	}
	count(root->left);
	count(root->right);
	if (root->data == '+') {		
		root->data = int(root->left->data) - '0' + int(root->right->data);		
	}
	else if (root->data == '-') {
		root->data = int(root->left->data) + '0' - int(root->right->data);
	}
	else if (root->data == '*') {
		root->data = (int(root->left->data) - '0') * (int(root->right->data)-'0')+'0';
	}
	else if (root->data == '/') {
		root->data = (int(root->left->data) - '0') / (int(root->right->data) - '0') + '0';
	}
	else if (root->data == '^') {
		root->data = '1';
		for (int i = 0; i<int(root->right->data) - '0'; i++) {
			root->data = (int(root->data) - '0') * (int(root->left->data) - '0') + '0';
		}
	}
	
}
int countL(Node* root) {
	count(root->left);
	if (root->left->data > 57) {
		return 9 + int(root->left->data) % 57;
	}
	else
		return int(root->left->data)-'0';
}

int countR(Node* root) {
	count(root->right);
	if (root->right->data > 57) {
		return 9 + int(root->right->data) % 57;
	}
	else
		return int(root->right->data)-'0';
}

int countRoot(Node* root) {
	if (root->data == '+') {
		root->data = int(root->left->data) + int(root->right->data) - '0' - '0';
		return int(root->data);
	}
	else if (root->data == '-') {
		root->data = int(root->left->data) - int(root->right->data);
		return int(root->data);
	}
	else if (root->data == '*') {
		root->data = (int(root->left->data) - '0') * (int(root->right->data) - '0');
		return int(root->data);
	}
	else if (root->data == '/') {
		root->data = (int(root->left->data) - '0') / (int(root->right->data) - '0');
		return int(root->data);
	}
	else if (root->data == '^') {
		root->data = '1';
		for (int i = 0; i<int(root->right->data) - '0'; i++) {
			root->data = (int(root->data) - '0') * (int(root->left->data) - '0') + '0';
		}
		return int(root->data) - '0';
	}
}
int main() {
	string infix;
	getline(cin, infix);
	Node* root = construct(infix);	
	cout << "Postfix Expression: ";
	postorder(root);
	cout << "\nInfix Expression: ";
	inorder(root);
	cout << endl << "Result for left subTree: " << countL(root) << endl;
	cout  << "Result for right subTree: " << countR(root) << endl;
	cout << "Result for Tree: " << countRoot(root) << endl;
	return 0;
}