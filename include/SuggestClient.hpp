// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_SUGGESTCLIENT_HPP_
#define INCLUDE_SUGGESTCLIENT_HPP_

#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
namespace http = boost::beast::http;

class SuggestClient{
 public:
  SuggestClient(std::string host, std::string port);
  ~SuggestClient() = default;
  json DoSession(std::string s_input);

 private:
  std::string const host_;
  std::string const port_;
};

#endif // INCLUDE_SUGGESTCLIENT_HPP_
