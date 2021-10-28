#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

typedef long IdType;
namespace Restaurant_H{
	class Restaurant{
		private:
		std::string passcode = "12345";

		public:
		void main_page();
		void display_menu();
		void display_session();
		void stay_or_leave(char& yesorno);
		void query(IdType& id);
		bool authorized_entry();
		void delete_all(bool flag);
	};
};

#endif
