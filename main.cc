#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

//Build a vector of strings so each vector[] contains a WHOLE string line from the text file
vector<string> makeVector (){

   vector<string> v;
   vector<string> words;
   string line;

   while(getline(cin, line)){
      v.push_back (line);
   }
   return v;
}

string builder (string& edit, string word){
   size_t index;
   size_t wordLen = word.length();

   index = edit.find(word);

   while (index != string::npos){
     if(!(isalpha(edit[(index - 1)])) && !(isalpha(edit[(index + wordLen)]))){
        edit.replace(index, wordLen, "CENSORED");
        index = edit.find(word, index + 1);
     }

     else if(index != edit.length()){
        index = edit.find(word, index + 1);  
     }
   }
return edit;
}

vector<string> editString(vector<string>& toEdit, vector<string>& wordCen){
//goes through each line in the vector and each line is sorted
   for(string i : wordCen){
     for(size_t j = 0; j < toEdit.size(); j++){
       
       string singleLine = toEdit[j];
       
       singleLine = builder(singleLine, i);
 
       toEdit[j] = singleLine;
    }
  }
   return toEdit;
}

//gets the information from all files given 
vector<string> fileReader(vector<string>& fileName){
  vector<string> fileContent;
  ifstream myFile;
  string line;

  for(string i : fileName){
    myFile.open(i);
    if(myFile.is_open()){
      while(getline(myFile, line)){
        fileContent.push_back(line);
      }
    myFile.close();
    }
    else if(!(myFile.is_open())){
      cerr<<"hw3 ERROR cannot open file : "<<i<<"\n";
      exit(1);
    }    
  }
  return fileContent;
}

vector<string> argSort(vector<string>& in){
  vector<string> args;

  for(size_t i = 0; i < in.size();i++){
    if(!(in[i] == "-")){
      args.push_back(in[i]);
    }    
    else{
      break;
    }
  }
  return args;
}

vector<string> fileSort(vector<string>& in){
  vector<string> file;
  size_t index = 0;
  bool isFound = false;

  for(size_t i = 0; i < in.size(); i++){
    if(in[i] == "-"){
    //just finds where the mandatory dash is and sets that as the starting 
    //point for next loop to add file names  
      index = i;
      isFound = true;
    }
  }

  if(!isFound){
      cerr<<"hw3 ERROR invalid argument syntax\n";
      exit(1);
    }

   //sorts through array after found index and gets the file name/path 
  for(size_t j = index; j < in.size(); j ++){

    if(index < in.size() && index != (in.size()-1)){
      index ++;
      file.push_back(in[index]);
    }
  }
  return file;    
}

void argAlpha(vector<string>& in){
  for(string str : in){
    for(size_t j = 0; j < str.length(); j++){
      if(!(isalpha(str[j]))){
        cerr<<"hw3 ERROR bad argument, " << str << " is not purely alphabetic\n";
        exit(1);
      }
    }
  }
}


bool duplicate(vector<string>& in){
  sort(in.begin(), in.end());
  
  if(in.size() == 2){
    if(in[0] == in[1]){
      cerr<<"hw3 ERROR: duplicate arguments : "<< in[0]<<"\n";
      return true;
    }
  }
  else{
    for (size_t i = 1; i < (in.size()); i++){
      if(in[i-1] == in[i]){
        cerr<<"hw3 ERROR: duplicate arguments : "<< in[i] <<"\n";
        exit(1);
      }
    }
  }
  return false;
}

void printVector(vector<string> vector){
    for(string i: vector){
      cout << i << "\n";
    }
}

int main(int argc, char *argv[] ) {
  vector <string> args;  
  vector <string> files;
  vector <string> fileContent;
  [[maybe_unused]]  bool dup = false;

  for(int i = 1; i < argc; i++){
    args.push_back(argv[i]);
    files.push_back(argv[i]);
  }
 
  args = argSort(args);
  files = fileSort(files);
 
  argAlpha(args);
  dup = duplicate(args);

  if(files.size() != 0){
    fileContent = fileReader(files);
    fileContent = editString(fileContent, args);
    printVector(fileContent);
  }
  
  else {
    vector<string> textFileLines = makeVector();
    textFileLines = editString(textFileLines, args);
    printVector(textFileLines);
  }
   return 0;
}

