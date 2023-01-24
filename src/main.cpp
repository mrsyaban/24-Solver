#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

/* variabel global*/
vector<string> listSol; // list yang menampung string solusi
bool valid = true; // false berarti masukan user salah

/***
 * Mengembalikan angka berdasarkan masukan input 
 */
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

/***
 * Mengembalikan hasil operasi dari : num1 op num2
 */
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

/***
 * Mengembalikan string yang merupakan hasil konkatenasi : (num1 op num2)
 */
string concat(string num1, string num2, char op){
    string res;
    string opStr;
    res = "("+ num1 +" " + opStr.append(1, op) + " " + num2 + ")";
    return res; 
}

/***
 * Mengembalikan string hasil konversi num
 */
string convert(double num){
    return to_string(int(num));
}

/**
 * Menambahkan solution pada listSol jika solution belum ada di listSol
 */
void addSolution(string solution){
    bool ada = false;
    for (auto sol: listSol){
        if (solution == sol){
            ada= true;
        }
    }
    if (!ada){
        listSol.push_back(solution);
    }
}

/***
 * menambahkan semua solusi yang memenuhi dari 1 kombinasi masukan dan urutan operasi
 */
void findSol(double num1, double num2, double num3, double num4, char op1, char op2, char op3){
    string solution;
    // ((num1 op1 num2) op2 num3) op3 num4 
    if (operate(operate(operate(num1, num2, op1), num3, op2), num4, op3) == 24) {
        solution = concat(concat(concat(convert(num1), convert(num2), op1), convert(num3), op2), convert(num4), op3);
        addSolution(solution);
    }
    // (num1 op1 (num2 op2 num3)) op3 num4
    if (operate(operate(num1, operate(num2, num3, op2), op1), num4, op3) ==  24){
        solution = concat(concat(convert(num1), concat(convert(num2), convert(num3), op2), op1), convert(num4), op3);
        addSolution(solution);
    }
    // num1 op1 (num2 op2 (num3 op3 num4))
    if (operate(num1, operate(num2, operate(num3, num4, op3), op2), op1) == 24){
        solution = concat(convert(num1), concat(convert(num2), concat(convert(num3), convert(num4), op3), op2), op1);
        addSolution(solution);
    }
    // num1 op1 ((num2 op2 num3) op3 num4)
    if (operate(num1, operate(operate(num2, num3, op2), num4, op3), op1) == 24){
        solution = concat(convert(num1), concat(concat(convert(num2), convert(num3), op2), convert(num4), op3), op1);
        addSolution(solution);
    }
    // (num1 op1 num2) op2 (num3 op3 num4)
    if (operate(operate(num1, num2, op1), operate(num3, num4, op3), op2) ==  24){
        solution = concat(concat(convert(num1), convert(num2), op1), concat(convert(num3), convert(num4), op3), op2);
        addSolution(solution);
    }
}

/***
 * Menghapus num pada listNum, num pasti ada di listNum
 */
vector<int> removeNum(vector<int> listNum, int num){
    int count = 0;
    while(listNum[count] != num){
        count++;
    }
    listNum.erase(listNum.begin()+count);
    return listNum;
}

/***
 * Mengembalikan jumlah semua kemungkinan yang memenuhi dari 4 angka masukan dengan 
 * melakukan permutasi pada 4 angka masukan dan 4 operasi yang menghasilkan (4!)*(4^3)*5
 * urutan angka-operasi yang berbeda
 */
void permut(vector<int> listNum, vector<char> listOp){
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
                                findSol(num1, num2, num3, num4, op1, op2, op3);
                            }
                        }
                    }
                }
            }
        }
    }
}

/***
 * Mengembalikan list of string yang berisi hasil split str by space
 */
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

/* *** MAIN PROGRAM *** */
int main(){
    string input;
    cout << R"(
                                            __                                               
                                        _..-''--'----_.                                        
                                    ,''.-''| .---/ _`-._                                     
                                    ,' \ \  ;| | ,/ / `-._`-.                                  
                                ,' ,',\ \( | |// /,-._  / /                                  
                                ;.`. `,\ \`| |/ / |   )/ /                                   
                                / /`_`.\_\ \| /_.-.'-''/ /                                    
                                / /_|_:.`. \ |;'`..')  / /                                     
                                `-._`-._`.`.;`.\  ,'  / /                                      
                                    `-._`.`/    ,'-._/ /                                       
                                    : `-/     \`-.._/                                        
                                    |  :      ;._ (                                          
                                    :  |      \  `\.                                         
                                    \         \   |                                         
                                        :        :   ;                                         
                                        |           /                                          
                                        ;         ,'                                           
                                    /         /                                             
                                    /         /                                              
                                            /                                                                       
 _ _ _       _                          _           ___  ___       _____       _                
| | | | ___ | | ___  ___  _____  ___   | |_  ___   |_  || | | ___ |   __| ___ | | _ _  ___  ___ 
| | | || -_|| ||  _|| . ||     || -_|  |  _|| . |  |  _||_  ||___||__   || . || || | || -_||  _|
|_____||___||_||___||___||_|_|_||___|  |_|  |___|  |___|  |_|     |_____||___||_| \_/ |___||_|  
                                                                                                
               )" << endl; 
    cout << endl << "Enter 4 Cards [separated by space] : ";
    getline (cin, input);
    auto start = high_resolution_clock::now();
    
    vector<string> listInput = splitString(input);
    int a = convertInput(listInput[0]), b = convertInput(listInput[1]), c = convertInput(listInput[2]), d = convertInput(listInput[3]);

    if (!valid) {
        cout << "Incorrect input." << "\n\n";
    } else {
        vector<int> listNum{a,b,c,d};
        vector<char> listOp{'+','-','x','/'};
        permut(listNum, listOp);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        int numOfSolution = listSol.size();
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
        cout << endl << "Time taken : " << duration.count() << " microseconds" << "\n\n";
    }
}