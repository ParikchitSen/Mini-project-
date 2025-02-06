
// Risham Raj herera push gara
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

class HuffmanNode {
public:
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char c, int f) {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

// Comparison function (non-operator overloading)
bool compare(HuffmanNode* a, HuffmanNode* b) {
    return a->freq > b->freq;  // Return true if 'a' has greater frequency than 'b'
}

class HuffmanCoding {
public:
    void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCode) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr) {
            huffmanCode[root->ch] = code;
        }
        generateCodes(root->left, code + "0", huffmanCode);
        generateCodes(root->right, code + "1", huffmanCode);
    }

    void buildHuffmanTree(const string& text) {
        unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(&compare)> pq(compare);
        for (auto pair : freq) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();
            HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
            merged->left = left;
            merged->right = right;
            pq.push(merged);
        }

        unordered_map<char, string> huffmanCode;
        generateCodes(pq.top(), "", huffmanCode);

        cout << "Huffman Codes:\n";
        for (auto pair : huffmanCode) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }
};

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);
    HuffmanCoding hc;
    hc.buildHuffmanTree(text);
    return 0;
}
