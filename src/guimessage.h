#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class GUIMessage {
public:
  GUIMessage(){};
  GUIMessage(int code, std::string message)
      : messageCode(code), messageText(message) {}
  int messageCode;
  std::string messageText;

private:
  friend class boost::serialization::access;

  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &messageCode;
    ar &messageText;
  }
};