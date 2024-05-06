#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
/*
 * Exercise 2.  Word count – Standard associative containers
 Implement program words that:
• counts number of distinct words in file redirected to standard input ,
 • prints the 20 most popular words with the number of occurrences.
The result of calling
 ./words < hamletEN.txt
 should be similar to hamletOUT.txt
Hints:
 • Use toLowerAlpha function from previous exercise to standardize words (lower case,
alphanumeric only).
• Use standard associative container map<string,int> to eliminate duplicates and to count
occurrences.
 • Compare the speed of map and unordered_map.
 • Use multimap<int, string> to “reverse” map and find most popular words.
 */

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */

void toLowerAlpha(std::string & s1) {
    s1.erase(std::remove_if(s1.begin(), s1.end(), [](unsigned char c){ return !std::isalnum(c); }), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c){ return std::tolower(c); });
}

int main(){
    std::string word;
    map<string, int> c;
    while(cin >> word) {
        toLowerAlpha(word);
        if(word != ""){
            c[word]++;
        }
    }

    multimap<int, string> m2;
    for (auto &pair : c) {
        m2.insert(make_pair(pair.second, pair.first));
    }

    cout << "Number of distinct words : " << c.size() << endl;
    cout << "\nThe top 20 most popular words: \n";

    auto it = m2.rbegin();
    for (int i = 0; i < 20 && it != m2.rend(); ++i, ++it) {
        cout << it->second << " : " << it->first << endl;
    }

    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */