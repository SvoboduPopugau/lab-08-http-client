// Copyright 2020 Your Name <your_email>

#include <SuggestClient.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>

SuggestClient::SuggestClient(std::string host, std::string port): host_(host),
                                                                  port_(port)
                                                                       {}
json SuggestClient::DoSession(std::string s_input) {
  boost::asio::io_context ioc{};

  boost::asio::ip::tcp::resolver resolver(ioc);
  boost::beast::tcp_stream stream(ioc);

  const auto result = resolver.resolve(host_, port_);

  stream.connect(result);

  boost::beast::http::request<boost::beast::http::string_body> req{
      boost::beast::http::verb::post, "/v1/api/suggest", 11};
  req.set(boost::beast::http::field::host, host_);
  req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(boost::beast::http::field::content_type, "application/json");
  req.body() = R"({"input": ")" + s_input + R"("})";

  req.prepare_payload();

  boost::beast::http::write(stream, req);

  boost::beast::flat_buffer buffer;
  boost::beast::http::response<boost::beast::http::string_body> res;

  boost::beast::http::read(stream, buffer, res);

  boost::beast::error_code ec;
  stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

  if (ec && ec != boost::beast::errc::not_connected) {
    throw boost::beast::system_error{ec};
  }

  return nlohmann::json::parse(res.body());
}
