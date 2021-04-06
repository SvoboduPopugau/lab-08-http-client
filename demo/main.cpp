#include <SuggestClient.hpp>
#include <iomanip>
#include <iostream>

const std::string str_stop = ":stop";

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error! Usage: " << std::endl
              << "     demo <hostname> <port>" << std::endl
              << "Example:" << std::endl
              << "     demo localhost 3000" << std::endl;
    return 1;
  }

  SuggestClient client(argv[1], argv[2]);

  std::cout << "Input \':stop\' to quit" << std::endl;

  std::string str_input{};
  while(str_input != str_stop){
    str_input.clear();
    std::cout << "Enter your word:";
    std::cin >> str_input;

    std::cout << "Response" << std::endl;
    std::cout << client.DoSession(str_input).dump(4) << std::endl << std::endl;
  }


}