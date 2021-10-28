#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<vector>
#include<bits/stdc++.h>
#include "Feedback.hpp"
using namespace std;
using namespace Feedback_H;

const StackItemType fname2 = "Feedback";


Stack::Stack():topPtr(NULL){}

Stack::Stack(const Stack& aStack){
    if(aStack.topPtr == NULL)
        topPtr == NULL;
    else{
        topPtr = new StackNode;
        topPtr->item = aStack.topPtr->item;

        StackNode *newPtr = topPtr;
        for(StackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next){
            newPtr->next = new StackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

Stack::~Stack(){
while(!isEmpty())
    pop();
}

bool Stack::isEmpty() const{
    return topPtr == NULL;
}

bool Stack::exist_test(const StackItemType& fname2){
	ifstream f(fname2.c_str());
	return f.good();
}

void Stack::push(const StackItemType& newItem){
    if(exist_test(fname2)){
		load();
		remove(fname2.c_str());
	}

	StackNode *newPtr = new StackNode;
		newPtr->item = newItem;
		newPtr->next = topPtr;
		topPtr = newPtr;
		cout<<"Your feedback has been submitted!\n\n"<<endl;
		save();
}

void Stack::pop(){
    if (isEmpty()){}

    else{
        StackNode *temp = topPtr;
        topPtr = topPtr->next;
		temp->next = NULL;
		cout << temp->item << endl;
		delete temp;
		temp = nullptr;
    }
}


void Stack::display(){
    cout << "*******************\n";
    cout << "Customer Review\n";
    cout << "*******************\n";
	//make use of pop operation to display 
	//all the elements in the stack
	//with LIFO manner
}

void Stack::save(){
	ofstream outfile;
	outfile.open(fname2.c_str());
   for (StackNode *cur = topPtr; cur != NULL; cur = cur->next)
   {
      outfile << cur->item << endl;
   }
   outfile.close();
}

void Stack::load(){
	ifstream inFile( fname2.c_str() );
	string str;
	bool flag = true;
	vector<string> fb;

   if ( inFile.good() )
   {
         topPtr = new StackNode;
		 
		 while(getline(inFile,str)){
			 fb.push_back(str);
		 }
		 
		 for(vector<string>::reverse_iterator i = fb.rbegin(); 
			i != fb.rend(); ++i )
		{
			if(flag){
				topPtr->item = *i;
				topPtr->next = NULL;
				flag = false;
			}else{
				StackNode* temp = new StackNode;
				temp->item = *i;
				temp->next = topPtr;
				topPtr = temp;
			}
		}
		 		 		 
   }  // end if
   inFile.close();
}

