#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class PhoneNumber {
  std::string number;
  public:
    PhoneNumber(const std::string& num){
        if ((num.size()!=12 || num.substr(0,2)!="+7")||
            !std::all_of(num.begin()+2,num.end(),::isdigit))
          throw std::invalid_argument("Invalid Number");
        number = num;
    }
    std::string getNumber() const {return number;}
};

class Contact {
public:
  std::string name;
  PhoneNumber number;
  Contact(const std::string& name, const PhoneNumber& num) : name(name), number(num) {}
};

class Phone {
  std::vector<Contact> contacts;
public:
  void addContact(const std::string& name, const std::string& num) {
    try {
      contacts.emplace_back(name, PhoneNumber(num));
      std::cout << "Contact added.\n";
    } catch (...) {
      std::cout << "Invalid number.\n";
    }
  }

  void call(const std::string& input) {
    std::string num;
    if (input[0] == '+') {
      try {
        PhoneNumber test(input);
        num = input;
      } catch (...) {
        std::cout << "Invalid number.\n";
        return;
      }
    } else {
      for (const auto& c : contacts) {
        if (c.name == input) {
          num = c.number.getNumber();
          break;
        }
      }
      if (num.empty()) {
        std::cout << "Contact not found.\n";
        return;
      }
    }
    std::cout << "CALL " << num << "\n";
  }

  void sms(const std::string& input) {
    std::string num;
    // Аналогично методу call
    std::cout << "Enter message: ";
    std::string msg;
    std::getline(std::cin, msg);
    std::cout << "SMS to " << num << ": " << msg << "\n";
  }
};

int main(){
  Phone phone;
  std::string command;
  while (true) {
    std::cout<<"Enter command add/call/sms/exit: ";
    std::getline(std::cin, command);
    if (command == "add") {
      std::string name, num;
      std::cout<<"Name: ";
      std::getline(std::cin, name);
      std::cout<<"Number: ";
      std::getline(std::cin, num);
      phone.addContact(name, num);
    }else if (command == "call"){
      std::cout<<"Enter name/number: ";
      std::string input;
      std::getline(std::cin, input);
      phone.call(input);
    }else if (command == "sms"){
      std::cout<<"Enter name/number: ";
      std::string input;
      std::getline(std::cin, input);
      phone.sms(input);
    }else if (command == "exit"){
      break;
    }
  }
}