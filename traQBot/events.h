#ifndef TRAQBOT_EVENT_H
#define TRAQBOT_EVENT_H

#include <string>
#include <vector>
#include <functional>
#include <traQBot/models.h>

namespace traQBot {

struct PingEvent {
  std::string eventTime;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    return *this;
  }
};

struct JoinedEvent {
  std::string eventTime;
  Channel channel;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->channel = Channel().fromJson(_json["channel"]);
    return *this;
  }
};

struct LeftEvent {
  std::string eventTime;
  Channel channel;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->channel = Channel().fromJson(_json["channel"]);
    return *this;
  }
};

struct MessageCreatedEvent {
  std::string eventTime;
  Message message;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = Message().fromJson(_json["message"]);
    return *this;
  }
};

struct MessageDeletedEvent {
  std::string eventTime;
  struct {
    std::string id;
    std::string channelId;
    auto& fromJson(const Json::Value& _json) {
      this->id = _json["id"].asString();
      this->channelId = _json["channelId"].asString();
      return *this;
    }
  } message;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = decltype(this->message)().fromJson(_json["message"]);
    return *this;
  }
};

struct MessageUpdatedEvent {
  std::string eventTime;
  Message message;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = Message().fromJson(_json["message"]);
    return *this;
  }
};

struct DirectMessageCreatedEvent {
  std::string eventTime;
  Message message;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = Message().fromJson(_json["message"]);
    return *this;
  }
};

struct DirectMessageDeletedEvent {
  std::string eventTime;
  struct {
    std::string id;
    std::string userId;
    std::string channelId;
    auto& fromJson(const Json::Value& _json) {
      this->id = _json["id"].asString();
      this->userId = _json["userId"].asString();
      this->channelId = _json["channelId"].asString();
      return *this;
    }
  } message;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = decltype(this->message)().fromJson(_json["message"]);
    return *this;
  }
};

struct DirectMessageUpdatedEvent {
  std::string eventTime;
  Message message;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = Message().fromJson(_json["message"]);
    return *this;
  }
};

struct BotMessageStampsUpdatedEvent {
  std::string eventTime;
  std::string messageId;
  std::vector<StampCount> stamps;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->messageId = _json["messageId"].asString();
    for(const auto& _subitem : _json["stamps"]) {
      this->stamps.push_back(StampCount().fromJson(_subitem));
    }
    return *this;
  }
};

struct ChannelCreatedEvent {
  std::string eventTime;
  Channel message;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = Channel().fromJson(_json["message"]);
    return *this;
  }
};

struct ChannelTopicChangedEvent {
  std::string eventTime;
  Channel message;
  std::string topic;
  User updater;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->message = Channel().fromJson(_json["message"]);
    this->topic = _json["topic"].asString();
    this->updater = User().fromJson(_json["updater"]);
    return *this;
  }
};

struct UserCreatedEvent {
  std::string eventTime;
  User user;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->user = User().fromJson(_json["user"]);
    return *this;
  }
};

struct UserActivatedEvent {
  std::string eventTime;
  User user;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->user = User().fromJson(_json["user"]);
    return *this;
  }
};

struct StampCreatedEvent {
  std::string eventTime;
  std::string id;
  std::string name;
  std::string fileId;
  User creator;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->id = _json["id"].asString();
    this->name = _json["name"].asString();
    this->fileId = _json["fileId"].asString();
    this->creator = User().fromJson(_json["creator"]);
    return *this;
  }
};

struct TagAddedEvent {
  std::string eventTime;
  std::string tagId;
  std::string tag;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->tagId = _json["tagId"].asString();
    this->tag = _json["tag"].asString();
    return *this;
  }
};

struct TagRemovedEvent {
  std::string eventTime;
  std::string tagId;
  std::string tag;
  auto& fromJson(const Json::Value& _json) {
    this->eventTime = _json["eventTime"].asString();
    this->tagId = _json["tagId"].asString();
    this->tag = _json["tag"].asString();
    return *this;
  }
};

struct UnknownEvent {};

class Bot {
    const std::string verification_token, access_token;
    std::string path = "/";
    uint16_t port = 80;
    std::function<void(PingEvent)> on_ping_callback;
    std::function<void(JoinedEvent)> on_joined_callback;
    std::function<void(LeftEvent)> on_left_callback;
    std::function<void(MessageCreatedEvent)> on_message_created_callback;
    std::function<void(MessageDeletedEvent)> on_message_deleted_callback;
    std::function<void(MessageUpdatedEvent)> on_message_updated_callback;
    std::function<void(DirectMessageCreatedEvent)> on_direct_message_created_callback;
    std::function<void(DirectMessageDeletedEvent)> on_direct_message_deleted_callback;
    std::function<void(DirectMessageUpdatedEvent)> on_direct_message_updated_callback;
    std::function<void(BotMessageStampsUpdatedEvent)> on_bot_message_stamps_updated_callback;
    std::function<void(ChannelCreatedEvent)> on_channel_created_callback;
    std::function<void(ChannelTopicChangedEvent)> on_channel_topic_changed_callback;
    std::function<void(UserCreatedEvent)> on_user_created_callback;
    std::function<void(UserActivatedEvent)> on_user_activated_callback;
    std::function<void(StampCreatedEvent)> on_stamp_created_callback;
    std::function<void(TagAddedEvent)> on_tag_added_callback;
    std::function<void(TagRemovedEvent)> on_tag_removed_callback;
    std::function<void()> on_launched_callback;
public:
    std::string get_token() { return access_token; }
    Bot(std::string _verification_token, std::string _access_token);
    template<class F>
    void on_ping(F callback) { on_ping_callback = callback; }
    template<class F>
    void on_joined(F callback) { on_joined_callback = callback; }
    template<class F>
    void on_left(F callback) { on_left_callback = callback; }
    template<class F>
    void on_message_created(F callback) { on_message_created_callback = callback; }
    template<class F>
    void on_message_deleted(F callback) { on_message_deleted_callback = callback; }
    template<class F>
    void on_message_updated(F callback) { on_message_updated_callback = callback; }
    template<class F>
    void on_direct_message_created(F callback) { on_direct_message_created_callback = callback; }
    template<class F>
    void on_direct_message_deleted(F callback) { on_direct_message_deleted_callback = callback; }
    template<class F>
    void on_direct_message_updated(F callback) { on_direct_message_updated_callback = callback; }
    template<class F>
    void on_bot_message_stamps_updated(F callback) { on_bot_message_stamps_updated_callback = callback; }
    template<class F>
    void on_channel_created(F callback) { on_channel_created_callback = callback; }
    template<class F>
    void on_channel_topic_changed(F callback) { on_channel_topic_changed_callback = callback; }
    template<class F>
    void on_user_created(F callback) { on_user_created_callback = callback; }
    template<class F>
    void on_user_activated(F callback) { on_user_activated_callback = callback; }
    template<class F>
    void on_stamp_created(F callback) { on_stamp_created_callback = callback; }
    template<class F>
    void on_tag_added(F callback) { on_tag_added_callback = callback; }
    template<class F>
    void on_tag_removed(F callback) { on_tag_removed_callback = callback; }
    template<class F>
    void on_launched(F callback) { on_launched_callback = callback; }
    void set_path(std::string _path) { path = _path; }
    void set_port(uint16_t _port) { port = _port; }

    void enable_mysql_ns();
    void start();
};

}

#endif
