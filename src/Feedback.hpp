#ifndef FEEDBACK_HPP
#define FEEDBACK_HPP

typedef std::string StackItemType;

namespace Feedback_H{
	class Stack{
		public:
			Stack();
			Stack(const Stack& aStack);
			~Stack();

			bool isEmpty() const;
			void push(const StackItemType& newItem);
			void pop();
			void display();
			void save();
			void load();
			bool exist_test(const StackItemType& fname);

		private:
			struct StackNode{
				StackItemType item;
				StackNode *next;
			};

			StackNode *topPtr;
	};
};

#endif
