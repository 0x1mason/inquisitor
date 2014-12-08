#ifndef SELENIUM_H
#define SELENIUM_H
#include <string>
#include <map>
#include "restio.hpp"
#include "utils.hpp"
#include "capabilities.hpp"
#include "session.hpp"
class WebDriver {
  private:
    std::string _endpoint_url;
  public:
    WebDriver(std::string,bool);
    Session* createSession(const map<string, string> *desiredCapabilities);

};

#endif
