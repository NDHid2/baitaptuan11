#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <cctype>
using namespace std;

// Cau truc node cay bieu thuc
struct ExprNode {
    string val;
    ExprNode* left;
    ExprNode* right;
    
    ExprNode(string v) {
        val = v;
        left = NULL;
        right = NULL;
    }
};

// Kiem tra do uu tien cua toan tu
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Kiem tra co phai toan tu không
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Chuyen bt trung to sng hau to
string infixToPostfix(const string& infix) {
    string postfix = "";
    stack<char> ops;
    
    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        
        // Bo qua khoang trong
        if (c == ' ') continue;
        
        // Neu la toan hang
        if (isalnum(c)) {
            postfix += c;
            postfix += ' '; 
        }
        // Neu la dau mo ngoac
        else if (c == '(') {
            ops.push(c);
        }
        // Neu la dau dong ngoac
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                postfix += ops.top();
                postfix += ' ';
                ops.pop();
            }
            if (!ops.empty()) ops.pop(); // b? '('
        }
        // Neu la toan tu
        else if (isOperator(c)) {
            while (!ops.empty() && ops.top() != '(' && 
                   precedence(ops.top()) >= precedence(c)) {
                postfix += ops.top();
                postfix += ' ';
                ops.pop();
            }
            ops.push(c);
        }
    }
    
    // Lay ton tu con lai
    while (!ops.empty()) {
        postfix += ops.top();
        postfix += ' ';
        ops.pop();
    }
    
    return postfix;
}

// Xây dung cay bieu thuc tu bieu thuc hau to
ExprNode* buildExpressionTree(const string& postfix) {
    stack<ExprNode*> st;
    string token = "";
    
    for (size_t i = 0; i <= postfix.length(); i++) {
        char c = postfix[i];
        
        if (c != ' ' && i < postfix.length()) {
            token += c;
        } 
        else if (!token.empty()) {
            // Ne la toan tu
            if (token.length() == 1 && isOperator(token[0])) {
                ExprNode* node = new ExprNode(token);
                node->right = st.top(); st.pop();
                node->left = st.top(); st.pop();
                st.push(node);
            }
            // Neu la toan hang
            else {
                st.push(new ExprNode(token));
            }
            token = "";
        }
    }
    
    return st.top();
}

// Duyet tien to
void preorder(ExprNode* root) {
    if (root == NULL) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// Duyet trung to co ngoac
void inorder(ExprNode* root) {
    if (root == NULL) return;
    
    // Thêm ngoac la toan tu, k phai lá
    bool needParen = (root->left != NULL || root->right != NULL);
    
    if (needParen && root->left != NULL) 
        cout << "(";
    
    inorder(root->left);
    cout << root->val;
    inorder(root->right);
    
    if (needParen && root->right != NULL) 
        cout << ")";
}

// Duyet hau to
void postorder(ExprNode* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

// Giai phong bo nho cay
void deleteTree(ExprNode* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string infix;
    
    cout << "Nhap bieu thuc : ";
    getline(cin, infix);
    
    // Chuyen sang hau to
    string postfix = infixToPostfix(infix);
    cout << "\nBieu thuc hau to: " << postfix << endl;
    
    // Xd bieu thuc
    ExprNode* root = buildExpressionTree(postfix);
    
    // Duyet cây
    cout << "\nDuyet tien to : ";
    preorder(root);
    cout << endl;
    
    cout << "Duyet trung to : ";
    inorder(root);
    cout << endl;
    
    cout << "Duyet hau to : ";
    postorder(root);
    cout << endl;
    
    deleteTree(root);
    
    return 0;
}
