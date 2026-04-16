#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <random>


using namespace std;

//Teller ID, Full Name, Password, Branch Code

class Teller{
    public:
        string id;
        string full_name;
        string password;
        string branch_code;
     
};

class Account{
    public:
        string account_number;
        string full_name;
        string sa_id;
        string contact;
        string email;
        string address;
        string dob;
        string account_type;
        double balance;
        string branch_code;
        string pin;

        virtual double get_min_deposit() = 0;

        virtual void display(){
            cout << "Account: " << account_number << "\n";
            cout << "Name: " << full_name << "\n";
            cout << "Balance: " << balance << "\n";
        }
};

class savings_acc : public Account{
    public:
        double get_min_deposit() override{
            return 100.0;
        }

};

class cheque_acc : public Account{
    public:
        double get_min_deposit() override{
            return 500.0;
        }

};

class fixed_deposit_acc : public Account{
    public:
        double get_min_deposit() override{
            return 1000.0;
        }

};

class student_acc : public Account{
    public:
        double get_min_deposit() override{
            return 50.0;
        }

};

int create_account(){

    ofstream out_file("data.dat");

    Teller my_obj;

    cout << "Enter Teller ID: " << "\n";

    cin >> my_obj.id;

    cout << "Enter Teller Full Name: " << "\n";

    cin.ignore();

    getline(cin, my_obj.full_name);

    cout << "Create Teller Password: " << "\n";

    cin >> my_obj.password;

    cout << "Enter Branch Code: " << "\n";

    cin >> my_obj.branch_code;

    string salt = "XyZ123";

    string salted = my_obj.password + salt;

    hash<string> pass_hash;    

    size_t hashed_password = pass_hash(salted);

    cout << hashed_password;

        if (out_file.is_open()){

            out_file << my_obj.id << "\n";

            out_file << my_obj.full_name << "\n";

            out_file << hashed_password << "\n";

            out_file << my_obj.branch_code << "\n";


        }

    return hashed_password;
}

string gen_acc_numb(string branch_code){
    static int counter = 1000;

    return "ACC-" + branch_code + "-" + to_string(counter++);
}

string gen_pin(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(10000, 99999);

    return to_string(dist(gen));
}

bool validate_said(string id){
    return id.length() == 13 && all_of(id.begin(), id.end(), ::isdigit);
}

bool validate_phone(string phone){
    return phone.length() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
}

bool validate_email(string email){
    return email.find("@") != string::npos &&
           email.find(".") != string::npos;
        }

void register_cust(string branch_code){
    Account * acc = nullptr;

    int type;
    cout << "Select Account Type: " << "\n";
    cout << "1. Savings" << "\n";
    cout << "2. Cheque" << "\n";
    cout << "3. Fixed Deposit" << "\n";

    cin >> type;

    if(type == 1) acc = new savings_acc();
    else if(type == 2) acc = new cheque_acc();
    else if(type == 3) acc = new fixed_deposit_acc();
    else if(type == 4) acc = new student_acc();

    cin.ignore();

    cout << "Full Name: " << "\n";
    getline(cin, acc -> full_name);

    do{
        cout << "SA ID (13 digits long): " << "\n";
        cin >> acc -> sa_id;
    }while(!validate_said(acc -> sa_id));

    do{
        cout << "SA ID (13 digits long): " << "\n";
        cin >> acc -> contact;
    }while(!validate_phone(acc -> contact));

    do{
        cout << "SA ID (13 digits long): " << "\n";
        cin >> acc -> email;
    }while(!validate_email(acc -> email));

    cin.ignore();
    cout << "Address: " << "\n";
    getline(cin, acc -> address);

    cout << "Date of Birth: " << "\n";
    cin >> acc -> dob;

    acc -> branch_code = branch_code;
    acc -> account_number = gen_acc_numb(branch_code);

    double min_deposit = acc -> get_min_deposit();

    do{cout << "Initial Deposit: (Min: " << min_deposit << "): " << "\n";
    }while(acc -> balance < min_deposit);

    acc -> pin = gen_pin();

    cout << "Generated Pin: " << acc -> pin << "\n";

    ofstream file("customers.dat", ios::app);

    file << acc -> account_number << "\n"
         << acc -> full_name << "\n"
         << acc -> sa_id << "\n"
         << acc -> contact << "\n"
         << acc -> email << "\n"
         << acc -> address<< "\n"
         << acc -> dob << "\n"
         << type << "\n"
         << acc -> balance << "\n"
         << acc -> branch_code << "\n"
         << acc -> pin << "\n";

    delete acc;


}

int main(){


    bool run = true;

    while (run == true){

        int choice;

        cout << "Enter Choice: " << "\n";

        cout << "1. Create Teller Account" << "\n";

        cout << "2. Login As Teller" << "\n";

        cout << "4. Exit" << "\n";

        cin >> choice;

        if (choice == 1){

           
            create_account();
           

        }else if(choice == 2){

            string identify;
            string pass_word;

            cout << "Please Enter ID & Password Below: " << "\n";

            cout << "ID Number:" << "\n";

            cin >> identify;

            cout << "Password:" << "\n";

            cin >> pass_word;

            string salt = "XyZ123";

            string salted = pass_word + salt;

            hash<string> hash_pass;
            size_t hashed_password = hash_pass(salted);

            string pass = to_string(hashed_password);

            ifstream file("data.dat");

            bool found = false;

            string file_id, file_name, file_password, file_branch;

            while (getline(file, file_id) && 
                   getline(file, file_name) && 
                   getline(file, file_password) &&
                   getline(file, file_branch)){

                if (file_id == identify && file_password == pass){
                    found = true;
                    cout << "Login Successful" << "\n";

                    int choices;

                    cout << "1. Register New Customer" << "\n";

                    cin >> choices;


                    if (choices == 1){

                        ofstream out_file("multiple.dat");

                        cout << "enter customer details" << "\n";



                    }
                    

                } 

                if (!found){

                    cout << "Invalid Id or Password" << "\n";
                }
            }


        }else if(choice == 4){

            run = false;

        }
        
    }
   
    return 0;
}
