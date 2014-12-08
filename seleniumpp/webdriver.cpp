#include "webdriver.hpp"

WebDriver::WebDriver(std::string surl,bool dbg) {

  extern std::string seleniumURL; 
  extern bool debug;

  _endpoint_url = surl;
  seleniumURL = surl;
  debug = dbg;
  
  restio* rio  = new restio();
  rio->get(_endpoint_url + "/status");
  
}

Session* WebDriver::createSession(const map<string, string>* desiredCapabilities) {

  std::string pdata = "{\"desiredCapabilities\":{" + map_to_json(desiredCapabilities) + "}}";

  restio* rio  = new restio();
  seleniumAnswer* ans = rio->post(_endpoint_url + "/session",pdata);
  
  if ( ans->status == restio::statusmap["Success"] ) {

     Session* s = new Session();
     s->id = ans->getSession();
     //s->id = resp.get<std::string>("sessionId");
     std::cout << s->id << std::endl;
     return s;
  }
  return NULL;
}
