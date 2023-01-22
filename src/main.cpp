#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

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

vector<int> removeNum(vector<int> listNum, int num){
    listNum.erase(remove(listNum.begin(), listNum.end(), num), listNum.end());
    return listNum;
}

double translOp(double num1, double num2, char op){
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

int numOfSol(double num1, double num2, double num3, double num4, char op1, char op2, char op3){
    int count = 0;
    if (translOp(translOp(translOp(num1, num2, op1), num3, op2), num4, op3) == 24) {
        // cout << "(((" << num1 << ' ' << op1 << ' ' << num2 << ") " << op2 << ' ' << num3 << ") " << op3 << ' ' << num4 << ')' << endl;    
        // string = "(((" + 
        // "(((" + to_string(num1) + ' ' + op1 + ' ' + num2 + ") " + op2 + ' ' + num3 + ") " + op3 + ' ' + num4 + ')';
        count++;
    }
    if (translOp(translOp(num1, translOp(num2, num3, op2), op1), num4, op3) ==  24){
        count++;
    }
    if (translOp(num1, translOp(num2, translOp(num3, num4, op3), op2), op1) == 24){
        count++;
    }
    if (translOp(num1, translOp(translOp(num2, num3, op2), num4, op3), op1) == 24){
        count++;
    }
    if (translOp(translOp(num1, num2, op1), translOp(num3, num4, op3), op2) ==  24){
        count++;
    }
    // if (count > 0){
    //     cout << count << endl;
    // }
    return count;
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
                                // cout << num1 << op1 << num2 << op2 << num3 << op3 << num4 << endl;
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
    cout << "Masukkan 4 Kartu : ";
    cin >> input;
    auto start = high_resolution_clock::now();
    
    vector<string> listInput = splitString(input);

    if (!valid) {
        cout << "Masukan tidak sesuai";
    } else {
        int a = convertInput(listInput[0]), b = convertInput(listInput[1]), c = convertInput(listInput[2]), d = convertInput(listInput[3]);
        vector<int> listNum{a,b,c,d};
        vector<char> listOp{'+','-','x','/'};
        vector<string> listRes;

        int numOfSolution = permut(listNum, listOp);
        cout << "Terdapat " << numOfSolution << " Solusi" << endl;
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken : " << duration.count() << " microseconds" << endl;
    }
}


