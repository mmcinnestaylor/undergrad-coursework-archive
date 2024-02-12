#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

pair<int, char> loadCharMap(const char readIn, unordered_map<char, int>& charMap);
pair<int, pair<int, string> > loadStringMap(const string theString, unordered_map<string, pair<int, int>>& theMap, int theCounter);
void updateCharTT(const pair<int, char> charPair, vector<pair<int, char>>& topTen);
void updateStringTT(const pair<int, pair<int, string>> strPair, vector<pair<int, pair<int, string>>>& topTen);
struct Comparable{
  bool operator()(const pair<int,char>& lhs, const pair<int,char>& rhs){
    return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second>rhs.second);
  }
};


int main(){
  unordered_map<string, pair<int, int>> wordMap;
  unordered_map<string, pair<int, int>> numMap;
  unordered_map<char, int> charMap;
  vector<pair<int, pair<int, string>>> topWords;
  vector<pair<int, pair<int, string>>> topNums;
  vector<pair<int, char>> topChars;
  string theString;
  pair<int, char> charPair;
  pair<int, pair<int, string>> strPair;
  char readIn;
  int counter = 0;

  while(!cin.eof()){
    counter--;
    if(isalpha(cin.peek())){
      theString.clear();
      while(isalpha(cin.peek())){
        cin.get(readIn);
        charPair = loadCharMap(readIn, charMap);
        updateCharTT(charPair, topChars);
        readIn = tolower(readIn);
        theString += readIn;
      }
      strPair = loadStringMap(theString, wordMap, counter);
      updateStringTT(strPair, topWords);
    }
    else if(isdigit(cin.peek())){
      theString.clear();
      while(isdigit(cin.peek())){
        cin.get(readIn);
        charPair = loadCharMap(readIn, charMap);
        updateCharTT(charPair, topChars);
        theString += readIn;
      }
      strPair = loadStringMap(theString, numMap, counter);
      updateStringTT(strPair, topNums);
    }
    else{
      while(!isalnum(cin.peek()) && !cin.eof()){
        cin.get(readIn);
        charPair = loadCharMap(readIn, charMap);
        updateCharTT(charPair, topChars);
      }
    }
  }

  cout << "Total " << charMap.size() << " different characters, "
       << topChars.size() << " most used characters:\n";
  for(int i = topChars.size() - 1; i >= 0; i--){
    cout << "No. " << topChars.size() - 1 - i << ": ";
    if(topChars[i].second == '\t')
      cout << "\\t";
    else if(topChars[i].second == '\n')
      cout << "\\n";
    else
      cout << topChars[i].second;
    cout << "\t\t" << topChars[i].first << "\n";
  }

  cout << endl;

  cout << "Total " << wordMap.size() << " different words, "
       << topWords.size() << " most used words:\n";
  for(int i = topWords.size() - 1; i >= 0; i--){
    cout << "No. " << topWords.size() - 1 - i << ": " << topWords[i].second.second;
    cout << "\t\t" << topWords[i].first << "\n";
  }

  cout << endl;

  cout << "Total " << numMap.size() << " different numbers, "
       << topNums.size() << " most used numbers:\n";
  for(int i = topNums.size() - 1; i >= 0; i--){
    cout << "No. " << topNums.size() - 1 - i << ": " << topNums[i].second.second;
    cout << "\t\t" << topNums[i].first << "\n";
  }
  return 0;
}

pair<int, char> loadCharMap(const char readIn, unordered_map<char, int>& charMap){
  auto thePair = charMap.emplace(readIn, 1);
  auto itr = thePair.first;
  if(thePair.second == false)
    (*itr).second += 1;
  return make_pair((*itr).second, (*itr).first);
}

pair<int, pair<int, string>> loadStringMap(const string theString, unordered_map<string, pair<int, int>>& theMap, int theCounter){
  auto thePair = theMap.emplace(theString, make_pair(1, theCounter));
  auto itr = thePair.first;
  if(thePair.second == false)
    (*itr).second.first += 1;
  return make_pair((*itr).second.first, make_pair((*itr).second.second, (*itr).first));
}

void updateCharTT(pair<int, char> charPair, vector<pair<int, char>>& topTen){
  if(topTen.size() < 10){
    auto itr = find(topTen.begin(), topTen.end(), make_pair(charPair.first - 1, charPair.second));
    if(itr == topTen.end()){
      topTen.push_back(charPair);
      sort(topTen.begin(), topTen.end(), Comparable());
    }
    else{
      (*itr).first++;
      sort(topTen.begin(), topTen.end(), Comparable());
    }

  }
  else if(charPair.first >= (topTen.front()).first){
    auto itr = find(topTen.begin(), topTen.end(), make_pair(charPair.first - 1, charPair.second));
    if(itr == topTen.end()){
      if(charPair.first == (topTen.front()).first && charPair.second < (topTen.front()).second){
        topTen.front() = charPair;
        sort(topTen.begin(), topTen.end(), Comparable());
      }
      else if(charPair.first > (topTen.front()).first){
        topTen.front() = charPair;
        sort(topTen.begin(), topTen.end(), Comparable());
      }
    }
    else{
      (*itr).first++;
      sort(topTen.begin(), topTen.end(), Comparable());
    }
  }
}

void updateStringTT(pair<int, pair<int, string>> strPair, vector<pair<int, pair<int, string>>>& topTen){
  if(topTen.size() < 10){
    auto itr = find(topTen.begin(), topTen.end(), make_pair(strPair.first - 1, strPair.second));
    if(itr == topTen.end()){
      topTen.push_back(strPair);
      sort(topTen.begin(), topTen.end());
    }
    else{
      (*itr).first++;
      sort(topTen.begin(), topTen.end());
    }
  }
  else if(strPair.first >= (topTen.front()).first){
    auto itr = find(topTen.begin(), topTen.end(), make_pair(strPair.first - 1, strPair.second));
    if(itr == topTen.end()){
      if(strPair.first == (topTen.front()).first && strPair.second.first > (topTen.front()).second.first){
        topTen.front() = strPair;
        sort(topTen.begin(), topTen.end());
      }
      else if(strPair.first > (topTen.front()).first){
        topTen.front() = strPair;
        sort(topTen.begin(), topTen.end());
      }
    }
    else{
      (*itr).first++;
      sort(topTen.begin(), topTen.end());
    }
  }
}
