/*  
 *  This code checks for balanced brackets and 
 *  comment blocks in the code using Stack.
 * 
 *  Created at October 2021 by Zekeriya AY <zekeriya@zekeriyaay.com> for homework about the university class
 */

#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main() {
    ifstream test_file;
    stack<char> stack;
    char data;
    bool is_comment = false;
    bool unmatched = false;

    test_file.open("test_false.txt", ios::in);
    stack.push('X');
    if (test_file.is_open()) {
        while (test_file >> data) {
            /* [CHECK] In comment block? */
            if (is_comment && data == '*' && stack.top() == '*') {
               stack.pop();
               continue;
            } else if (is_comment && data == '/' && stack.top() == '/') {
                is_comment = false;
                stack.pop();
                continue;
            } else if (is_comment) {
                continue;
            }

            /* Open comment block */
            if (data == '/') {
                stack.push(data);
                continue;
            } else if (data == '*' && stack.top() == '/') {
                is_comment = true;
                stack.push(data);
                continue;
            } 
            /* False Positive Comment Block */
            else if(stack.top() == '/' && data != '*'){
                is_comment = false;
                stack.pop();
                continue;
            }


            /* [PUSH] Brackets */
            if (data == '(' || data == '[' || data == '{') {
                stack.push(data);
                continue;
            }

            /* [POP] Brackets */
            if (data == ')' && stack.top() == '(') {
                stack.pop();
                continue;
            } else if (data == ']' && stack.top() == '[') {
                stack.pop();
                continue;
            } else if (data == '}' && stack.top() == '{') {
                stack.pop();
                continue;
            }


            /* [CHECK] Non-closing Brackets  */
            if (data == ')' && stack.top() != '(') {
                cout << "[!]Unmatched ')' Exiting..." << endl;
                unmatched = true;
                break;
            } else if (data == ']' && stack.top() != '[') {
                cout << "[!]Unmatched ']' Exiting..." << endl;
                unmatched = true;
                break;
            } else if (data == '}' && stack.top() != '{') {
                cout << "[!]Unmatched '}' Exiting..." << endl;
                unmatched = true;
                break;
            }
        }
    }

    /* [CHECK] Is the Stack empty? */
    if (!stack.empty() && stack.top() != 'X') {
        cout << "[?]Stack is not empty" << endl << "[-]Stack-> ";
        while (!stack.empty()) {
            if (stack.top() != 'X') {
                if (stack.top() == '*') {
                    is_comment = true;
                } else if (is_comment == true && stack.top() == '/') {
                    is_comment = false;
                    cout << "[!]Unmatched '*/' in stack" << endl;
                }
                cout << stack.top();
            }
            stack.pop();
        }
        cout << endl;
    } else if (!unmatched) {
        cout << "[+]Compilation Successful!" << endl;
    } 
    
    test_file.close();

    return 0;
}
