#include<iostream>
#include<fstream>

#include<string>
#include<algorithm>

#include "node.h"
#include "timer.h"

using namespace std;
using std::string;
using std::cin;
using std::cout;
using std::fstream;
using std::ifstream;
using std::ofstream;

//cleanWord method
string cleanWord(string word) {
  string tmpS = word;
  string safe = "`~!@#$%^&*()_+=-[]\":;.>,<|/{}? ";

  for (int i = 0; i < word.length(); i++) {
    for (int j = 0; j < safe.length(); j++) {
      if (word[i] == safe[j]) {
        char c = word[i];
        tmpS.erase(std::remove(tmpS.begin(), tmpS.end(), c), tmpS.end());
      }
    }
  };
  transform(tmpS.begin(), tmpS.end(), tmpS.begin(), ::tolower);
  return tmpS;
};

int main() {
  //Prep to read file
  ifstream dictionary;
  ifstream bookComplete;

  //Declare lists
  BinarySearchTree<string> dictTree;
  BinarySearchTree<string> outputTree;

  //variables for insert
  string word;
  string scrubbedWord;

  //count variables
  long int compareCountT = 0;
  long int compareCountF = 0;
  long int notFound = 0;
  long int bookSize = 0;
  long int dictionarySize = 0;
  long int outputSize = 0;

  //delcare timer
  Timer timer;

  //put dictionary words into their list
  dictionary.open("dict.txt", ifstream::in);
  int i = 1;
  while (true) {

    dictionary >> word;
    cout << i << endl;
    if (word.size() == (0 || 1)) { //reads last empty line still
      cout << "empty";
    }
    else {
      dictTree.insert(word);
    };
    if (dictionary.eof()) {
      break;
    };
    i++;
  };
  dictionary.close();
  cout << "dictionary finished" << endl;
  timer.Start();
  dictionarySize = dictTree.getNodes();

  //open book, get a word, scrub it, then check and then put into output list 
  bookComplete.open("book.txt", ifstream::in);
  i = 0;
  while (true) {
    bookComplete >> word;
    //check book here
    scrubbedWord = cleanWord(word);
    bookSize++;
    cout << "book checked " << i << endl;
    if (scrubbedWord.length() == 0) {
      notFound++;
    }
    else if (dictTree.find(scrubbedWord) == nullptr) {
      compareCountT++;
    }
    else {
      compareCountF++;
      outputSize++;
      outputTree.insert(scrubbedWord);
    };
    if (bookComplete.eof()) {
      break;
    };
    i++;
  };
  bookComplete.close();

  //stop timer
  timer.Stop();

  //size of output list
  //outputSize = outputTree.getNodes();

  //put mismatched words into output file
  //ofstream out;
  //out.open("output.txt", ios::out);
  //for (int i = 0; i < outputSize; i++) {
  //  out << outputTree.front() << "\n";
  //  outputTree.remove();
  //}
  //out.close();

  outputTree.printPreorder(outputTree.getRoot());

  cout << "dictionary size " << dictionarySize << "\n";
  cout << "Done checking and these are the results\n";
  cout << "finished in time: " << timer.Time() << "\n";

  //cout << "There are " << compareCountT << " words found in the dictionary\n";


  //cout << () << " compares. Average: " << () << "\n";

  //cout << "There are " << compareCountF << " words NOT found in the dictionary\n";

  //cout << () << " compares. Average: " << () << "\n";

  //cout << "There are " << notFound << " words not checked.";

  return 0;
}