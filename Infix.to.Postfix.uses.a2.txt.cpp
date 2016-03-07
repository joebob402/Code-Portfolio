#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

//Infix to Postfix Algorithm with Homemade Stack System (including PUSH and POP)
//Written by Benjamin Malinowski
//
//This console application is an implementation of an infix to postfix conversion.
//A user-made STACK class with POP and PUSH systems has also been created.
//The equations are initially given in typical infix format in the text file (i.e. a-n*m).
//The program will convert them to typical postfix format (i.e. anm*-).
//The program then solves each given equation, using the ASCII value of each letter as number values.
//

using namespace std;
template <class New>            //Creates class template
class STACK{                    //Creates Stack Class
	private:
		int Top_of_Stack;       //Initializes top of Stack variable
		char Stack_Data[20];    //Sets Stack size
		float Stack_Data2[20];  //Sets evaluation Stack size

	public:
		STACK(){
			Top_of_Stack = 0;                       //Sets initial top of Stack
		}
		void PUSH(char number){                     //PUSHes Data onto the stack
			Top_of_Stack++;                         //Increments stack
			Stack_Data[Top_of_Stack] = number;      //Data on top of stack becomes input char
		}
        void PUSH2(float number){                   //PUSH for evaluation function
			Top_of_Stack++;                         //Increments stack
			Stack_Data2[Top_of_Stack] = number;     //Data on top of stack becomes input char
		}
		char POP(){                                 //POPs Data from the top of the Stack
			char temp = Stack_Data[Top_of_Stack];
			Top_of_Stack--;
			return temp;                            //Returns top of Stack
		}
		float POP2(){                               //POPs Data from the top of the Evaluation Stack
			float temp = Stack_Data2[Top_of_Stack]; //POP for evaluation function
			Top_of_Stack--;
			return temp;                            //Returns top of Stack
		}
		char Return_Top_of_Stack(){                 //Returns Data from the top of the stack
			return Stack_Data[Top_of_Stack];
		}
		float Return_Top_of_Stack2(){               //Returns Data from the top of the stack
			return Stack_Data2[Top_of_Stack];       //Return Top for evaluation function
		}
		bool isEmpty(){                             //Checks if stack is empty
			if(Top_of_Stack == 0)                   //If top is initial start
				return true;                        //Return true
			return false;
		}
};

int operatorPriority(char operators) {              //Sets operator priority
    int temp = 0;                                   //Placeholder
    if (operators == '^')                           //If ^
        temp = 1;                                   //Priority 1
    else  if (operators == '*' || operators == '/') //If * or /
        temp = 2;                                   //Priority 2
    else  if (operators == '+' || operators == '-') //If + or -
        temp = 3;                                   //Priority 3
    return temp;                                    //Return priority
}

int INFIX_TO_POSTFIX(string infix, char* postfix_return)      //Conversion function
{
    STACK<char> STACK;
	int i = 0, z = 0;
	char postfix_array[25];
	string postfix;
	cout << "Postfix Equation: ";
	for (int pos = 0; pos < infix.size() ; pos++)  //For the length of the infix string until end of string:
    {

		if (infix[pos] == '+' || infix[pos] == '-' || infix[pos] == '/' || infix[pos] == '*' || infix[pos] == '^')        //If is operator:
		{
			//Checks if stack is empty, if top of stack is parentheses, and the priority of each operator on the stack
			while(!STACK.isEmpty() && operatorPriority(STACK.Return_Top_of_Stack()) <= operatorPriority(infix[pos]) && STACK.Return_Top_of_Stack() != '(' && STACK.Return_Top_of_Stack() != ')')
			{
				postfix_array[i] = STACK.Return_Top_of_Stack();
				i++;
				cout << STACK.POP();  //POPs stack                                                                                            
			}                                                                                                                                
            STACK.PUSH(infix[pos]);   //PUSHes operator to stack
        }
		else if (infix[pos] == '('){  //If char is '('
             STACK.PUSH(infix[pos]);  //PUSHes to operator stack
        }
		else if (infix[pos] == ')'){  //If char is ')'
			while (STACK.Return_Top_of_Stack() != '(') {        //Return top of stack until '('
				postfix_array[i] = STACK.Return_Top_of_Stack(); //Stores top of stack into postfix string
				i++;
				cout << STACK.POP();                            //Print POP'd operator
            }
			STACK.POP();                                        //POPs the '('
        }
		else {
            postfix_array[i] = infix[pos];   
            i++;
            cout << infix[pos];
        }
    }
	while (!STACK.isEmpty()) {								   //Dumps the stack
		postfix_array[i] = STACK.Return_Top_of_Stack();		   //Stores contents of stack into postfix array
		i++;
		cout << STACK.POP();
    }
    for (z = 0; z < i; z++)
    {
        postfix_return[z] = postfix_array[z];				   //Stores postfix array into Main
    }
    cout << endl;
    int length = i;											   //Length of postfix array
    return length;
}

float solve(char op, float operand1, float operand2)
{
    float solution = 0;
    if (op=='+')                               //If operator is +
        solution = (operand1+operand2);        //Return sum
    else if (op=='-')                          //If operator is -
        solution = (operand1-operand2);        //Return difference
    else if (op=='*')                          //If operator is *
        solution = (operand1*operand2);        //Return product
    else if (op=='/')                          //If operator is /
        solution = (operand1/operand2);        //Return quotient
    else if (op=='^')                          //If operator is ^
        solution = (pow(operand1,operand2));   //Return exponential
    return solution;
}

float POSTFIX_EVALUATION(char* postfix_arr, int lengthofpostfix)
{

    STACK<float> STACK;                                                 //Initializes evaluation float stack
    float answer = 0, temp = 0, operandx = 0, operandy = 0;             //Final evaluated answer variable
    int i = 0, c = 0;                                                   //Counters and operand variables
    char op, check;                                                     //Operator variable
    for (c = 0; c < lengthofpostfix; c++)                               //For postfix equation
    {
        (char)postfix_arr[i];
        if (postfix_arr[i] >= 'a' && postfix_arr[i] <= 'z'){       //If operand
            STACK.PUSH2((float)postfix_arr[i]);                    //PUSHes operand to stack
            i++;                                                   //Increments postfix array
        }
        else if(postfix_arr[i] == '+' || postfix_arr[i] == '-' || postfix_arr[i] == '/' || postfix_arr[i] == '*'|| postfix_arr[i] == '^'){  //If Operator
            op = postfix_arr[i];                      //Sets operator to postfix array slot
            operandx = STACK.POP2();                  //Retrieves operand 1 from stack
            operandy = STACK.POP2();                  //Retrieves operand 2 from stack
            answer = solve(op,operandy,operandx);     //Solves the postfix
            STACK.PUSH2(answer);                      //Pushes the answer onto the stack
            i++;                                      //Moves to next value in postfix array
        }
    }
    answer = STACK.Return_Top_of_Stack2();			  //Returns final answer from stack
    STACK.POP2();
    return answer;
}

int main()
{
    cout << "Infix to Postfix Converter and Solver v1.0" << endl;
    cout << "NOTE: Each letter in equations has its value assigned " << endl;
    cout << " based on its ASCII value." << endl;
    cout << "i.e. a = 97, b = 98, c = 99, etc." << endl << endl;
    cout << "Values that exceed a certain exponential threshold will be assigned inf or -inf." << endl;

    char postfix[25];                                                        //Postfix char array
    string line, equation[10], input;                                        //Initializes string variables
    int length = 0,EqCount = 0, i = 0, y = 0;                                //Initializes counters and length array
    float total_sum = 0, equationAnswer = 0;                                 //Total sum variable
    ifstream EqnList("a2.txt");                                              //Opens file
    if (EqnList.is_open())                                                   //If file is open:
    {
        while (getline(EqnList,line))                                        //Reads in the data from the text and writes to an array
        {
            equation[i]=line;                                                //Stores each line as an array string
            cout << "Original Equation: " << equation[i] << endl;            //Prints original equation
            length = INFIX_TO_POSTFIX(equation[i], postfix);                 //Calls conversion function
            equationAnswer = POSTFIX_EVALUATION(postfix, length);
            cout << "Solution: " << equationAnswer << endl;                  // Solves and prints postfix evaluation
            cout << endl;
            total_sum = total_sum + equationAnswer;                          //Adds solution to total sum of all equations
            i = i++;                                                         //Counts the number of lines entered
        }
     EqnList.close();                                                        //Closes the file
    }
	else
	{
    cout << "File is not being read" << endl;
	}
    cout << "The sum of all solved equations: " << total_sum << endl;        //Prints the total sum
    return 0;
}
