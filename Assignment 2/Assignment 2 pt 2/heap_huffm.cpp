#include <bits/stdc++.h>
using namespace std;

class MinHeapNode {
public:
    char data;
    int freq;
    MinHeapNode *left, *right;

    MinHeapNode(char d, int f) {
        left = right = NULL;
        data = d;
        freq = f;
    }
};

struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

void PrintCode(MinHeapNode* root, string str) {
    if (!root) return;
    if (root->data != '#') {
        cout << root->data << ": " << str << endl;
    }
    PrintCode(root->left, str + "0");
    PrintCode(root->right, str + "1");
}

string Decode(MinHeapNode* root, char* str, int size) {
    string out = "";
    MinHeapNode* curr = root;
    for (int i = 0; i < size; i++) {
        if (str[i] == '0') curr = curr->left;
        else curr = curr->right;

        if (curr->left == NULL && curr->right == NULL) {
            out += curr->data;
            curr = root;
        }
    }
    return out;
}

MinHeapNode *decoded = NULL;

void HuffmanCode(char* data, int* freq, int size) {
    MinHeapNode *right, *left, *top;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minheap;

    for (int i = 0; i < size; i++) {
        minheap.push(new MinHeapNode(data[i], freq[i]));
    }

    while (minheap.size() != 1) {
        left = minheap.top();
        minheap.pop();
        right = minheap.top();
        minheap.pop();

        MinHeapNode* temp = new MinHeapNode('#', left->freq + right->freq);
        temp->left = left;
        temp->right = right;
        minheap.push(temp);
    }
    decoded = minheap.top();
    PrintCode(minheap.top(), "");
}


int main() {
    char arr[] = { 'a','b','c','d','e' };
    int freq[] = { 10,5,2,14,15 };
    int size = 5;
    HuffmanCode(arr, freq, size);

    char str[] = "000001010111";
    int str_size = strlen(str);
    string s1;
    s1 = Decode(decoded, str, str_size);
    cout << s1 << endl;

    return 0;
}
