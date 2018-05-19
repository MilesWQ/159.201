/**
 * @brief 159201 assignment 2. The requirements refer to assignment specifications.
 *
 * @details Implement a calculator to parse Reverse Polish expression and compute the result with a stack.
 *
 * @author Wan Qian ID:17326163
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/**
 * the node encapsulated in a stack.
 */
struct StackNode {
	int mValue; ///< the operand of the expression
	StackNode *next; 
	/**
	 * Constructor.The pointer points to the next node is nullptr by default.
	 */
	StackNode(int _x) :mValue{ _x }, next(nullptr) {}
};

/**
 * a Stack implemented with a linked list to hold the operands
 */
class Stack {
public:
	/**
	 * Constructor.The pointer points to the internal linked list is nullptr by default.
	 */
	Stack();

	/**
	 * Destructor.Delete every node in the stack.
	 */
	~Stack();

	/**
	 * Add a new node storing the operand into the stack.
	 */
	void push(int);

	/**
	 * Delete the first node in the stack.
	 */
	void pop();

	/**
	 * get the operand value of the first node.
	 * It is required to check if the stack is empty before using this method.Otherwise might cause runtime error.
	 */
	int top();

	/**
	 * Check if the stack is empty.It should be invoked before top() for safety.
	 */
	bool isEmpty();

	/**
	 * print the value stored in the stack;
	 */
	void print();

private:
	StackNode * listptr_; ///< store the pointer points to a linked list
};

/**
* Constructor.The pointer points to the internal linked list is nullptr by default.
*/
Stack::Stack() :listptr_(nullptr) {}

/**
* Destructor.Delete every node in the stack.
*/
Stack::~Stack() {
	StackNode *to_be_del = listptr_;
	while (listptr_ != nullptr) {
        to_be_del = listptr_;
        listptr_ = listptr_->next;
		delete to_be_del;
	}
}

/**
* Add a new node storing the operand into the stack.
*/
void Stack::push(int _x) {
	StackNode *newNode = new StackNode(_x);
	newNode->next = listptr_;
	listptr_ = newNode;
}

/**
* Delete the first node in the stack.
*/
void Stack::pop() {
	if (listptr_ == nullptr) {
		return;
	}
	StackNode *temp = listptr_;
	listptr_ = listptr_->next;
	delete temp;
}

/**
* get the operand value of the first node.
* It is required to check if the stack is empty before use this method.Otherwise might cause runtime error.
*/
int Stack::top() {
	return listptr_->mValue;
}

/**
* Check if the stack is empty.It should be used before top() for safety.
*/
bool Stack::isEmpty() {
	return listptr_ == nullptr;
}

/**
* print the value stored in the stack;
*/
void Stack::print() {
	if (listptr_ == nullptr) {
		return;
	}
	StackNode *current = listptr_;
	while (current != nullptr) {
		cout << current->mValue << "->";
		current = current->next;
	}
}

/**
 * A calculator to parse Reverse Polish expression and calculate the result with a stack
 */
class Calculator {

public:
	/**
	 * Print the result.It is required to check if run() method is successful before invoke this method.
	 */
	void printResult();

	/**
	* Read the file to parse the expression and execute the calculation process.
	* It returns false if reading file fail or there's too many operators.
	* The operands will be pushed into a stack before encounter an operator.
	* When reach a operator, it will do the calculation with the previous two operands.
	* The final result will be pushed into the stack.
	* @param [in] _fileName the file to be parsed
	* @return false under 3 cases: (a)reading file fail (b)too many operator (c)Invalid operator
	*		  Otherwise true;
	*/
	bool run(const char*);

private:
	Stack stack; ///< a stack to store the operand.

	/**
	 * extract two operands from the stack and evaluate with the operator.
	 * @param [in] _operator the operator.
	 * @return false if there are too many operators(no enough operand).Otherwise true;
	 */
	bool calculate(const char&);
	
	/**
	* get an operand from the top of stack and delete it. 
	* @param [out] _operand the value of the operand when get successfully.
	* @return false if the stack is empty.Otherwise true.
	*/
	bool extractOperandFromStack(int&);

	/**
	* evaluate two operands with an operator and push the result into stack.
	* @param [in] op1 the first operand.
	* @param [in] op2 the second operand.
	* @param [in] oper the operator.
	*/
	void compute(int, int, char);
};

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "Please input a file name" << endl;
		exit(0);
	}
	Calculator cal;
	if (cal.run(argv[1])) {
		cal.printResult();
	}
}

/**
* Read the file to parse the expression and execute the calculation process.
* It returns false if reading file fail or there's too many operators.
* The operands will be pushed into a stack before encounter an operator.
* When reach a operator, it will do the calculation with the previous two operands.
* The final result will be pushed into the stack.
* @param [in] _fileName the file to be parsed
* @return false under 3 cases: (a)reading file fail (b)too many operator (c)Invalid operator
*		  Otherwise true;
*/
bool Calculator::run(const char* _fileName) {
	ifstream fin;
	fin.open(_fileName);
	if (!fin) {
		cerr << "Can not read file " << _fileName << ". Program terminates" << endl;
		return false;
	}
	while (!fin.eof()) {
		string line;
		int number = 0;
		char op;
		getline(fin, line);
		if (line.empty()) {
			continue;
		}
		if (isdigit(line[0])) {
			stringstream toInt(line);
			toInt >> number;
			cout << "reading number " << number << endl;
			stack.push(number);
		}
		else if (line == "+" || line == "-" || line == "*" || line == "/") {
			stringstream toChar(line);
			toChar >> op;
			cout << "reading operator " << op << endl;
			if (!calculate(op)) {
				return false;
			}
		}
		//Invalid token
		else {
			cerr << "Invalid operator " << line << "\nProgram terminated" << endl;
			return false;
		}
	}
	fin.close();
	return true;
}

/**
* Print the result.It is required to check if run() method is successful before invoke this method.
*/
void Calculator::printResult() {
	int result = 0;
	extractOperandFromStack(result);
	if (!stack.isEmpty()) {
		cerr << "too many numbers" << endl;
		return;
	}
	cout << "The result is " << result << endl;
}

/**
* extract two operands from the stack and evaluate with the operator.
* @param [in] _operator the operator.
* @return false if there are too many operators(no enough operand).Otherwise true;
*/
bool Calculator::calculate(const char& _operator) {
	int operand1 = 0, operand2 = 0;
	if (extractOperandFromStack(operand1) && extractOperandFromStack(operand2)) {
		compute(operand1, operand2, _operator);
		return true;
	}
	else {
		cerr << "too many operators" << endl;
		return false;
	}
}

/**
* get an operand from the top of stack and delete it.
* @param [out] _operand the value of the operand when get successfully.
* @return false if the stack is empty.Otherwise true.
*/
bool Calculator::extractOperandFromStack(int &_operand) {
	if (stack.isEmpty()) {
		return false;
	}
	_operand = stack.top();
	stack.pop();
	return true;
}

/**
 * evaluate two operands with an operator and push the result into stack.
 * @param [in] _op1 the first operand.
 * @param [in] _op2 the second operand.
 * @param [in] _oper the operator.
 */
void Calculator::compute(int _op1, int _op2, char _oper) {
	switch (_oper) {
	case '+':
		stack.push(_op1 + _op2);
		break;
	case '-':
		stack.push(_op2 - _op1);
		break;
	case '*':
		stack.push(_op1 * _op2);
		break;
	case '/':
		stack.push(_op2 / _op1);
		break;
	}
}
