#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

/*
 * When we split sentences into words we can group sentences that have the same beginning. To store
sentences we can use trie data structure (called also prefix tree).  We can easily obtain possible
continuations of given sentence.
Start with file ex_9_3_Trie.cpp implement
 • Trie data structure using std::map,
 • method add that adds sentence to trie,
 • method printPossibleEndings that for given beginning of sentence prints all possible
endings
 */
/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code. 
 */
class Trie {
    map<string, Trie*> children;
public:
    static void printSentence(const vector<string>& sentence) {
        for (const auto& w : sentence)
            cout << w << " ";
    }

    bool isLast() {
        return children.empty();
    }

    void add(const vector<string>& sentence) {
        cout << "Adding : ";
        printSentence(sentence);
        cout << "\n";

        Trie* node = this;
        for (const auto& word : sentence) {
            auto result = node->children.insert({word, nullptr});
            if (result.second) { // If the insertion took place
                result.first->second = new Trie();
            }
            node = result.first->second;
        }
    }

    void printPossibleEndings(const vector<string>& beginningOfSentence) {
        cout << "Endings for \"";
        printSentence(beginningOfSentence);
        cout << "\" are :\n";

        Trie* node = this;
        for (const auto& word : beginningOfSentence) {
            auto it = node->children.find(word);
            if (it == node->children.end()) {
                return;
            }
            node = it->second;
        }

        string prefix = " > ";
        for(const auto& [word, child] : node->children){
            prefix += word + " ";
            child->printEndings(prefix);
        }
    }

    void printEndings(string prefix = "") {
        if (isLast()) {
            cout << prefix << endl;
            return;
        }
        for(const auto& [word, child] : children){
            child->printEndings(prefix + word + " ");
        }
    }

    void load(const string& fileName) {
        ifstream file(fileName);
        if (!file) {
            cerr << "Error when opening file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while (file >> word) {
            sentence.push_back(word);
            if (word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }

    ~Trie() {
        for(auto& child : children) {
            delete child.second;
        }
    }

};


int main(){
    Trie dictionary;
    dictionary.load("../sample.txt");
    //dictionary.load("hamletEN.txt");

    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse","was","killed"});

    /* cout << "Beginning of sentence (ended with single .): ";
    string word;
    vector<string> sentence;
    while(true){
        cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
    }*/
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */