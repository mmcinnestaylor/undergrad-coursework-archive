#include "passserver.h"

PassServer::PassServer(size_t size): passTable(size){}

PassServer::~PassServer(){}

bool PassServer::load(const char* filename){
  return passTable.load(filename);
}

bool PassServer::addUser(std::pair<std::string, std::string>& kv){
  std::pair <std::string, std::string> encrypKV;
  std::string encrypPass = encrypt(kv.second);
  encrypKV = std::make_pair(kv.first, encrypPass);
  return passTable.insert(encrypKV);
}

bool PassServer::addUser(std::pair<std::string, std::string>&& kv){
  std::pair <std::string, std::string> encrypKV;
  std::string encrypPass = encrypt(kv.second);
  encrypKV = std::make_pair(std::move(kv.first), encrypPass);
  return passTable.insert(encrypKV);
}

bool PassServer::removeUser(const std::string& k){
  return passTable.remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword){
  std::pair <std::string, std::string> encrypKV;
  std::string encrypPass = encrypt(p.second);
  encrypKV = std::make_pair(p.first, encrypPass);
  if(!passTable.contains(p.first))
    return false;
  else if(!passTable.match(encrypKV))
    return false;
  else if (p.second == newpassword)
    return false;
  else{
    encrypPass = encrypt(newpassword);
    encrypKV = std::make_pair(p.first, encrypPass);
    return passTable.insert(encrypKV);
  }
}

bool PassServer::find(const std::string& user) const{
  return passTable.contains(user);
}

void PassServer::dump() const{
  passTable.dump();
}

size_t PassServer::size() const{
  return passTable.getSize();
}

bool PassServer::write_to_file(const char* filename) const{
  return passTable.write_to_file(filename);
}

std::string PassServer::encrypt(const std::string& str) const{
  std::string salt = "$1$########";
  std::string encrypPass = crypt(str.c_str(), salt.c_str());
  return encrypPass.substr(12);
}
