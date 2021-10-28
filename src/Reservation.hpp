#ifndef RESERVATION_HPP
#define RESERVATION_HPP

typedef long IdType;

namespace Reservation_H{

	struct Customer{
		IdType userID;
		std::string name;
		int session;
		int pax_no;
		char menu_selection;
	};

	class Reservation{
		private:
			//private attributes
			struct Node{
				struct Customer cust;
				Node* next;
			};
			Node* headptr;
			
			//random number generator
			int random_num();
			
			//merge sort
			void merge_sort(Node*& head);
			void split(Node*& start, Node*& front, Node*& back);
			Node* merge_sorted_list(Node*& list1,Node*& list2);
			void sorting();							//perform sorting

			//binary search
			Node* middle(Node*& start, Node*& last);
			Node* binarySearch(Node*& head,const IdType value,Node*& prev);

		public:
			//static attributes
			static int counter_sess1;
			static int counter_sess2;

			//constructor & destructor
			Reservation();
			~Reservation();

			//basic functionalities
			bool is_empty()const;
			void getcount( Node*& head); 			//assign value to 2 static counter_sess1
			void notification( Node*& node);
			void collect_info(Node*& node);
			void make_reservation();
			void cancel_res(const IdType value);
			void edit_res(const IdType value);
			void display(); 						//display all record
			void display_record(const IdType value);//display a particular record

			//file handling
			void save();
			void load();
			bool exist_test(const std::string& fname); //check for file existence
	};

	int Reservation::counter_sess1 = 0;
    int Reservation::counter_sess2 = 0;

};  // end namespace

#endif
