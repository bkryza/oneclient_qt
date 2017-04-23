#include "oneclientmessagelistener.h"
#include "guimessage.h"
#include "hash.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/uuid/sha1.hpp>
#include <iostream>

OneclientMessageListener::OneclientMessageListener(const QString &mountpoint)
    : m_mountpoint(mountpoint) {}

void OneclientMessageListener::run() {

  boost::interprocess::message_queue mq(
      boost::interprocess::open_only,
      Hash::hash(m_mountpoint.toStdString()).c_str());
  boost::interprocess::message_queue::size_type recvd_size;
  unsigned int priority;

  std::string serialized_string;
  serialized_string.resize(1024);

  GUIMessage message;

  while (true) {
    try {
      std::stringstream iss;
      mq.receive(&serialized_string[0], 1024, recvd_size, priority);
      iss << serialized_string;

      boost::archive::text_iarchive ia(iss);
      ia >> message;

      std::cout << "Received oneclient message: " << message.messageText
                << std::endl;

      emit receivedNotification(message.messageCode,
                                message.messageText.c_str());

    } catch (boost::interprocess::interprocess_exception &e) {
      std::cout << "IPC exception: " << e.what() << std::endl;
    } catch (boost::archive::archive_exception &e) {
      std::cout << "Serialization exception: " << e.what() << std::endl;
    }
  }
}
