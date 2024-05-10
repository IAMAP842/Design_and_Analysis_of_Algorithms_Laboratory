#include <bits/stdc++.h>
using namespace std;
class Symbol {
public:
    char symbol;
    double probability;
    string code;

    Symbol(char s, double p) : symbol(s), probability(p), code("") {}
};

bool symbolCompare(Symbol s1, Symbol s2) {
    return s1.probability > s2.probability;
}

void shannonFano(vector<Symbol>& symbol, int start, int end) {
    if (end - start <= 1) return;

    int mid = start;
    double totalprobability = 0.0;

    for (int i = start; i < end; i++) {
        totalprobability += symbol[i].probability;
    }
    totalprobability /= 2.0;

    while (abs(int(totalprobability - symbol[mid].probability)) > abs(int(totalprobability - symbol[mid + 1].probability))) {
        mid++;
        totalprobability -= symbol[mid].probability;
    }

    for (int i = start; i <= mid; i++) {
        symbol[i].code += "0";
    }

    for (int i = mid + 1; i < end; i++) {
        symbol[i].code += "1";
    }

    shannonFano(symbol, start, mid + 1);
    shannonFano(symbol, mid + 1, end);
}

unordered_map<char, string> shannonFanoCode(const string& input) {
    unordered_map<char, double> symbolProbs;
    for (char c : input) {
        if (symbolProbs.find(c) == symbolProbs.end()) {
            symbolProbs[c] = 0.0;
        }
        symbolProbs[c] += 1.0;
    }
    vector<Symbol> symbols;
    for (auto it : symbolProbs) {
        double prob = it.second / input.length();
        symbols.push_back(Symbol(it.first, prob));
    }
    sort(symbols.begin(), symbols.end(), symbolCompare);
    shannonFano(symbols, 0, symbols.size());
    unordered_map<char, string> codewords;
    for (Symbol s : symbols) {
        codewords[s.symbol] = s.code;
    }
    return codewords;
}

int main() {
    string inputFileName = "input.txt";
    string outputFileName = "2ndencode.txt";

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cout << "Failed to open file: " << inputFileName << endl;
        return 1;
    }

    string input((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    unordered_map<char, string> codewords = shannonFanoCode(input);

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cout << "Failed to create output file: " << outputFileName << endl;
        return 1;
    }

    for (char c : input) {
        outputFile << codewords[c] << " ";
    }
    outputFile.close();

    cout << "Shannon-Fano encoded content has been stored in " << outputFileName << endl;

    return 0;
}