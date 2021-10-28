#include<bits/stdc++.h>
#include<fstream>
#include<conio.h> //C header file
#include "Reservation.hpp"
using namespace Reservation_H;
using namespace std;

const int MAX_PAX = 20;
const string fname = "Reservation_list";


int Reservation::random_num(){
	srand((unsigned) time(0));
	int randomNumber = (rand()%999999)+100000;
	return randomNumber;
}

Reservation::Reservation():headptr(nullptr){}

Reservation::~Reservation(){
	Node* helper = headptr;
	while(headptr!=NULL){
        headptr = headptr->next;
        delete helper;
        helper = headptr;
	}
	helper = nullptr;
}

bool Reservation::is_empty() const{
    return headptr == NULL;
}


void Reservation::edit_res(const IdType value){
	if(exist_test(fname)){
		load();
		sorting();
		remove(fname.c_str());
	}
	Node* prev = nullptr;
	Node* temp = binarySearch(headptr,value, prev);
	cout << endl;
	cout << "\n\nYour original record as shown below\n";
	display_record(value);
	cout << endl;
	if(temp!=NULL){
		collect_info(temp);
		cout << "\n\nUpdated record as shown below\n";
		display_record(value); 				//updated record displayed
	}else{
		cout << "Sorry. No record is found.";
	}
	save();
}

void Reservation::collect_info(Node*& node){
	do{
		cout << "Select session:";
		cin >> node -> cust.session;
	}while(node -> cust.session <= 0 || node -> cust.session > 2);
	cout << "Enter your surname:";
	cin >> node -> cust.name;
	do{
		cout << "Enter menu selection (A/B/C):";
		cin >> node -> cust.menu_selection;
	}while(node -> cust.menu_selection > 'C');
	cout << "How many Package(pax) " << node->cust.menu_selection << " do you need?:";
	cin >> node -> cust.pax_no;
}

void Reservation::cancel_res(const IdType value){
	if(exist_test(fname)){
		load();
		sorting();
		remove(fname.c_str());
	}
	Node* prev = headptr;
	Node* temp = binarySearch(headptr,value, prev);
	if(temp != NULL){
		if(temp == headptr){ 		//compare the pointers, see if they are pointing to the same location
			headptr = headptr->next;	 //the deleted node is the first node
		}else{
			prev->next = temp->next;	//the deleted node is not the first node
		}
		delete temp;
		temp = nullptr;
		cout << "Reservation is canceled\n";
	}
	save();
	prev = nullptr;
}

Reservation::Node* Reservation::middle(Node*& start,Node*& last)
{
    if (start == NULL)
        return NULL;

	Node* slow = start;
    Node* fast = start -> next;

    while (fast != last)
    {
        fast = fast -> next;
        if (fast != last)
        {
            slow = slow -> next;
            fast = fast -> next;
        }
    }
    return slow;
}

//pointer prev is for cancel_reservation only, else just pass nullptr as an actual parameter to here
Reservation::Node* Reservation::binarySearch(Node*& head,const IdType value, Node*& prev)
{
    Node* start = head;
    Node* last = NULL;

    do
    {
        // Find middle
        Node* mid = middle(start, last);

        // If middle is empty
        if (mid == NULL)
            return NULL;

        // If value is present at middle
        if (mid -> cust.userID == value)
            return mid;

        // If value is more than mid
        else if (mid -> cust.userID < value){
            if(prev != NULL) //additional
				prev = mid;
            start = mid -> next;
        }

        // If the value is less than mid.
        else
            last = mid;

    } while (last == NULL ||
             last != start);

    // value not present
    return NULL;
}

void Reservation::display_record(const IdType value){
	if(exist_test(fname)){
		load();
		sorting();
	}
	Node* prev = nullptr;
	Node* temp = binarySearch(headptr,value,prev);
	if(temp != NULL){
		cout << "\nUser ID:" << temp->cust.userID << endl;
		cout << "Name:" << temp->cust.name << endl;
		cout << "Session:" << temp->cust.session << endl;
		cout << "Pax:" << temp->cust.pax_no << endl;
		cout << "Menu_selection:" << temp->cust.menu_selection << endl;
	}else{
		cout << "\nRecord doesn't exist.\n";
	}
}

void Reservation::getcount(Node*& head){
    Node* temp = head;
    while(temp != NULL){
		if(temp->cust.session == 1)
			counter_sess1++;
		else
			counter_sess2++;
        temp = temp->next;
    }
	temp = nullptr;
}

Reservation::Node* Reservation::merge_sorted_list(Node*& list1, Node*& list2){
	Node* sorted = nullptr;

	//base cases
	if(list1 == NULL) return list2;
	if(list2 == NULL) return list1;

	//recursive
	//perform comparison
	//sort by ID
	if(list1->cust.userID <= list2->cust.userID){
		sorted = list1;
		sorted->next = merge_sorted_list(list1->next,list2);
	}else{
		sorted = list2;
		sorted->next = merge_sorted_list(list1,list2->next);
	}
	//return back to the first function call
	return sorted;
}

void Reservation::split( Node*& start, Node*& front, Node*& back){
	Node* ptr1;
	Node* ptr2;
	ptr2 = start;
	ptr1 = start->next;

	//ptr1 incremented twice, ptr2 incremented once
	while(ptr1 != NULL){
		ptr1 = ptr1-> next;
		if(ptr1 != NULL){
			ptr1 = ptr1 ->next;
			ptr2 = ptr2 ->next;
		}
	}
	front = start;
	back = ptr2->next;
	ptr2->next = NULL;
}

void Reservation::merge_sort(Node*& head){
	Node* tmp = head;
	Node* ptr1;
	Node* ptr2;

	//base case
	//if it's not null or it's not the last node
	//then it'll continue spliting
	//else return nothing
	if(tmp == NULL || (head->next == NULL))
		return;

	split(tmp, ptr1, ptr2);

	//recursive call
	merge_sort(ptr1);
	merge_sort(ptr2);

	//for the first function call
	//any changes done here
	//will also affect the head pointer in main function
	head = merge_sorted_list(ptr1, ptr2);
}

void Reservation::sorting(){
	merge_sort(headptr);
}

//check if the file exists
bool Reservation::exist_test(const string& fname){
	ifstream f(fname.c_str());
	return f.good();
}

void Reservation::notification(Node*& node){
	system("cls");
	node -> cust.userID = random_num();
	cout << "\n*****************************************\n";
	cout << "Your reservation is successful\n";
	cout << "Your user ID is " << node -> cust.userID ;
	cout << "\nPlease remember this ID ";
	cout << "\n*****************************************\n";
}

void Reservation::make_reservation(){
	if(exist_test(fname)){
		load();
		remove(fname.c_str());
	}

		Node* node = new Node;
		cout << "Select session:";
		cin >> node -> cust.session;
		bool flag = false;
		if(node -> cust.session == 1)flag = true;
		cout << "Your selected session: " << node -> cust.session << endl;

		if((flag && (Reservation::counter_sess1 < MAX_PAX)) || (!flag && (Reservation::counter_sess2 < MAX_PAX))){
            cout << "Enter your surname:";
            cin >> node -> cust.name;
            do{
                cout << "Enter menu selection (A/B/C):";
                cin >> node -> cust.menu_selection;
            }while(node -> cust.menu_selection >  'C');
            cout << "How many Package(Pax) " << node->cust.menu_selection << " do you need?:";
            cin >> node -> cust.pax_no;

            if(((node->cust.session == 1)&&counter_sess1<= MAX_PAX) ||
                ((node->cust.session == 2)&&counter_sess2<= MAX_PAX)){
                notification(node);
                if(is_empty())
                    node->next = NULL; 		//first node
                else
                    node->next = headptr; 	//not the first node

                headptr = node;
                save();
            }else{
                cout << "Sorry. This session is fully booked\n";
                node->next = NULL;
                delete node;
            }
        }else{
            save();
            cout << "There is no more available table. Kindly consider other session. Thank you.\n";
        }
}

void Reservation::display(){
	sorting();
	Node* temp = headptr;
	if(temp != NULL){
        while(temp != NULL){
            cout << temp->cust.userID << " " << temp->cust.name << " " << temp->cust.menu_selection
                << " " << temp->cust.pax_no << " " << temp->cust.session << "\n";
            temp = temp->next;
        }
        cout << "\n";
    }else{
        cout << "Empty list\n";
    }

    temp = nullptr;
}

void Reservation::save(){
	ofstream outfile;
	outfile.open(fname.c_str(),std::ios_base::app );
   for (Node *cur = headptr; cur != NULL; cur = cur->next)
   {
      outfile << cur->cust.userID << " " << cur->cust.name << " "
	  << cur->cust.menu_selection << " " << cur->cust.pax_no << " "
	  << cur->cust.session << endl;
   }
   outfile.close();
}

void Reservation::load(){
	ifstream inFile( fname.c_str() );
   IdType c1;
   string c2;
   char c3;
   int c4;
   int c5;

   if ( inFile.good() ) // Is file empty?
   {  // File not empty:
		inFile>>c1>>c2>>c3>>c4>>c5;
         headptr = new Node;
         // Add the first node to the list.
         headptr->cust.userID = c1;
		 headptr->cust.name = c2;
		 headptr->cust.menu_selection = c3;
		 headptr->cust.pax_no = c4;
		 headptr->cust.session = c5;
         headptr->next = NULL;

         // Add remaining to linked list.
         while ( inFile >> c1>> c2>>c3>>c4>>c5 )
         {
            Node* temp = new Node;
			temp->cust.userID = c1;
			 temp->cust.name = c2;
			 temp->cust.menu_selection = c3;
			 temp->cust.pax_no = c4;
			 temp->cust.session = c5;
			 temp->next = headptr;
			 headptr = temp;

         }  // end while
   }  // end if
   getcount(headptr);

   inFile.close();
}


