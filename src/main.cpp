#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

vector<string> listSol;
bool valid = true;

int convertInput(string input){
    int num;
    if (input == "A"){
        return 1;
    } else if (input == "J"){
        return 11;
    } else if (input == "Q") {
        return 12;
    } else if (input == "K") {
        return 13;
    } else {
        stringstream ss;  
        ss << input;  
        ss >> num;
        if (num < 2 || num >10){
            valid = false;
        }
        return num;
    }
}


double operate(double num1, double num2, char op){
    if (op == '+'){
        return num1 + num2;
    } else if (op == '-'){
        return num1 - num2;
    } else if (op == 'x'){
        return num1 * num2;
    } else {
        return num1 / num2;
    }
}

string concat(string num1, string num2, char op){
    string res;
    string opStr;
    res = "("+ num1 +" " + opStr.append(1, op) + " " + num2 + ")";
    return res; 
}

string convert(double num){
    return to_string(int(num));
}

int numOfSol(double num1, double num2, double num3, double num4, char op1, char op2, char op3){
    int count = 0;
    string solution;
    // ((num1 op1 num2) op2 num3) op3 num4 
    if (operate(operate(operate(num1, num2, op1), num3, op2), num4, op3) == 24) {
        // solution  = "(((" + to_string(num1) + " " + to_string(op1) + " " + to_string(num2) + ") " + to_string(op2) + " " + to_string(num3) + ") " + to_string(op3) + " " + to_string(num4) + ")";
        solution = concat(concat(concat(convert(num1), convert(num2), op1), convert(num3), op2), convert(num4), op3);
        listSol.push_back(solution);
        count++;
    }
    // (num1 op1 (num2 op2 num3)) op3 num4
    if (operate(operate(num1, operate(num2, num3, op2), op1), num4, op3) ==  24){
        solution = concat(concat(convert(num1), concat(convert(num2), convert(num3), op2), op1), convert(num4), op3);
        listSol.push_back(solution);
        count++;
    }
    // num1 op1 (num2 op2 (num3 op3 num4))
    if (operate(num1, operate(num2, operate(num3, num4, op3), op2), op1) == 24){
        solution = concat(convert(num1), concat(convert(num2), concat(convert(num3), convert(num4), op3), op2), op1);
        listSol.push_back(solution);
        count++;
    }
    // num1 op1 ((num2 op2 num3) op3 num4)
    if (operate(num1, operate(operate(num2, num3, op2), num4, op3), op1) == 24){
        solution = concat(convert(num1), concat(concat(convert(num2), convert(num3), op2), convert(num4), op3), op1);
        listSol.push_back(solution);
        count++;
    }
    // (num1 op1 num2) op2 (num3 op3 num4)
    if (operate(operate(num1, num2, op1), operate(num3, num4, op3), op2) ==  24){
        solution = concat(concat(convert(num1), convert(num2), op1), concat(convert(num3), convert(num4), op3), op2);
        listSol.push_back(solution);
        count++;
    }
    return count;
}

vector<int> removeNum(vector<int> listNum, int num){
    int count = 0;
    while(listNum[count] != num){
        count++;
    }
    listNum.erase(listNum.begin()+count);
    return listNum;
}

int permut(vector<int> listNum, vector<char> listOp){
    int count = 0;
    int num = 0;
    for (auto num1: listNum){
        vector<int> listNum2 = removeNum(listNum, num1);
        for (auto num2: listNum2){
            vector<int> listNum3 = removeNum(listNum2, num2);
            for (auto num3: listNum3){
                vector<int> listNum4 = removeNum(listNum3, num3);
                for (auto num4: listNum4){
                    for(auto op1: listOp){
                        for(auto op2: listOp){
                            for(auto op3: listOp){
                                count += numOfSol(num1, num2, num3, num4, op1, op2, op3);
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}

vector<string> splitString(string str){
    string res = "";
    vector<string> splitRes;
    str = str + " ";
    for(auto word: str){
        if (word == ' '){
            splitRes.push_back(res);
            res ="";
        } else{
            res += word;
        }
    }

    if (splitRes.size() != 4){
        valid = false;
    }
    return splitRes;
} 

int main(){
    string input;
    cout << "Enter 4 Cards :";
    getline (cin, input);
    
    auto start = high_resolution_clock::now();
    
    vector<string> listInput = splitString(input);
    int a = convertInput(listInput[0]), b = convertInput(listInput[1]), c = convertInput(listInput[2]), d = convertInput(listInput[3]);

    if (!valid) {
        cout << "Incorrect input.";
    } else {
        vector<int> listNum{a,b,c,d};
        vector<char> listOp{'+','-','x','/'};

        int numOfSolution = permut(listNum, listOp);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        if (numOfSolution > 0){
            cout << numOfSolution << " Solutions found" << endl << endl;
            for(auto sol: listSol){
                cout << sol << endl;
            }

            string ans;
            cout << "Do you want to save the solution? [yes/no] : ";
            cin >> ans;
            if (ans == "yes"){
                string filesName;
                cout << "Enter file's name (.txt) : ";
                cin >> filesName;
                ofstream out("..\\test\\" + filesName);
                out << numOfSolution << " Solutions found" << endl;
                for (auto solution: listSol){
                    out << solution << endl;
                }
                out.close();
            } else if (ans != "no") {
                cout << "Incorrect Input";
            }
        } else {
            cout << "There Is No Solution." << endl;
        }
        cout << endl << "Time taken : " << duration.count() << " microseconds" << endl;
    }
}