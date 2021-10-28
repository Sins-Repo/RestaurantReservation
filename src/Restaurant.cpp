#include<iostream>
#include "Restaurant.hpp"
#include "Reservation.cpp"
#include "Feedback.cpp"
using namespace std;
using namespace Restaurant_H;

void Restaurant::display_session(){
	cout << "*****************************\n";
	cout << "Session time as shown below.\n";
	cout << "*****************************\n";
	cout << "Session 1: 4:00p.m. - 6:00 p.m.\n";
	cout << "Session 2: 8:00p.m. - 10:00 p.m.\n";
	cout << "\n\n";
}

void Restaurant::display_menu(){
	cout << "*****************************\n";
	cout << "Menu as shown below.\n";
	cout << "*****************************\n";
	cout << "Package A\tAll-You-Can-Eat buffet \tRM40.00/pax\n";
	cout << "Package B\tSpecial Occasion buffet\tRM50.00/pax\n";
	cout << "Package C\tHealthy Concept buffet \tRM45.00/pax\n";
	cout << "--------------------------------------------------\n";
}

bool Restaurant::authorized_entry(){
	string tmp;
	cout << "*****************************\n";
	cout << "Authorized Personnel Only\n";
	cout << "*****************************\n";
	cout << "Please Enter Passcode: ";
	cin >> tmp;
	if(tmp == passcode){
		return true;
	}else{
		return false;
	}
}

void Restaurant::delete_all(bool flag){
	if(flag){
		remove(fname.c_str());
		cout << "All record has been deleted\n";
	}else{
		cout << "File does not exist.\n";
	}
}

void Restaurant::query( IdType& id){
	cout << "Enter your user ID: ";
	cin >> id;
}

void Restaurant::stay_or_leave(char& yesorno){
	cout << endl << "Would you like to continue(y/n)?: ";
    cin >> yesorno;
}

void Restaurant::main_page(){
	IdType id;
	char yesorno;

	do{
		loop:
        Reservation res;
        system("cls");
		cout << "Seoul Garden Restaurant\n";
		cout << "1.Make Reservation\n";
		cout << "2.View Reservation Status\n";
		cout << "3.Cancel Reservation\n";
		cout << "4.Edit Reservation\n";
		cout << "5.Feedback\n";
		cout << "6.Exit\n";
		cout << "----------------------------\n";
		cout << "\tStaff Only\n";
		cout << "----------------------------\n";
		cout << "7.Display All Reservation\n";
		cout << "8.Delete All Reservation\n\n";
		cout << "Enter your selection:";
		int choice;
		cin >> choice;

		switch(choice){
			case 1:
				system("cls");
				display_session();
				display_menu();
				res.make_reservation();
				break;

			case 2:
				system("cls");
				query(id);
				res.display_record(id);
				break;

			case 3:
				system("cls");
				cout << "********************\n";
				cout << "Cancel Reservation\n";
				cout << "********************\n";
				query(id);
				res.cancel_res(id);
				break;

			case 4:
				system("cls");
				query(id);
				display_session();
				display_menu();
				res.edit_res(id);
				break;

			case 5:
			{
				Stack aStack;
				string str;
				system("cls");
				cin.ignore();
				cout << "Enter your feedback:";
				getline(cin,str);
				aStack.push(str);
				aStack.display();
                break;
			}
			case 6:
				exit(0);
				break;

			case 7:
				system("cls");
				if(authorized_entry()){
					res.load();
					res.display();
					cout << endl << "Number of booked table(s) of session 1: " << Reservation::counter_sess1;
					cout << endl << "Number of booked table(s) of session 2: " <<Reservation::counter_sess2 << endl;
				}else{
					cout << "Please leave this page\n";
				}

				break;

			case 8:
				system("cls");
				if(authorized_entry()){
					cout << "This action will delete all existing reservation record\n";
					cout << "Do you want to proceed?(y/n) : ";
					cin >> yesorno;
					if(yesorno == 'Y' || yesorno == 'y'){
						delete_all(res.exist_test(fname));
					}
				}else{
					cout << "Please leave this page\n";
				}
				break;


			default:
				system("cls");
				cout << "Invalid input\n";
				getch();
				goto loop;
		}
		stay_or_leave(yesorno);
		Reservation::counter_sess1 = 0;
		Reservation::counter_sess2 = 0;
	}while(yesorno == 'Y' || yesorno == 'y');
}


int main(){
    Restaurant start;
	start.main_page();
	return 0;
}
