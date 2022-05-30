#ifndef TRAQBOT_EVENT_H
#define TRAQBOT_EVENT_H

#include <string>
#include <vector>
#include <variant>
#include <drogon/drogon.h>
#include <json/json.h>
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

using EventPayload = std::variant<
  PingEvent,
  JoinedEvent,
  LeftEvent,
  MessageCreatedEvent,
  MessageDeletedEvent,
  MessageUpdatedEvent,
  DirectMessageCreatedEvent,
  DirectMessageDeletedEvent,
  DirectMessageUpdatedEvent,
  BotMessageStampsUpdatedEvent,
  ChannelCreatedEvent,
  ChannelTopicChangedEvent,
  UserCreatedEvent,
  StampCreatedEvent,
  TagAddedEvent,
  TagRemovedEvent
>;

enum class EventType {
  Ping,
  Joined,
  Left,
  MessageCreated,
  MessageDeleted,
  MessageUpdated,
  DirectMessageCreated,
  DirectMessageDeleted,
  DirectMessageUpdated,
  BotMessageStampsUpdated,
  ChannelCreated,
  ChannelTopicChanged,
  UserCreated,
  StampCreated,
  TagAdded,
  TagRemoved,
  Unknown,
};
struct EventData {
  EventType event;
  std::string requestId;
  std::string token;
  EventPayload payload;
};

}

namespace drogon {

template <>
inline traQBot::EventData fromRequest(const HttpRequest& req) {
  auto event = req.getHeader("X-TRAQ-BOT-EVENT");
  auto requestId = req.getHeader("X-TRAQ-BOT-REQUEST-ID");
  auto token = req.getHeader("X-TRAQ-BOT-TOKEN");
  auto json = req.getJsonObject();
  traQBot::EventData data;
  data.requestId = requestId;
  data.event = traQBot::EventType::Unknown;
  data.token = token;
  if (json) {
    if (event == "PING") {
      data.event = traQBot::EventType::Ping;
      data.payload = traQBot::PingEvent().fromJson(*json);
    } else
    if (event == "JOINED") {
      data.event = traQBot::EventType::Joined;
      data.payload = traQBot::JoinedEvent().fromJson(*json);
    } else
    if (event == "LEFT") {
      data.event = traQBot::EventType::Left;
      data.payload = traQBot::LeftEvent().fromJson(*json);
    } else
    if (event == "MESSAGE_CREATED") {
      data.event = traQBot::EventType::MessageCreated;
      data.payload = traQBot::MessageCreatedEvent().fromJson(*json);
    } else
    if (event == "MESSAGE_DELETED") {
      data.event = traQBot::EventType::MessageDeleted;
      data.payload = traQBot::MessageDeletedEvent().fromJson(*json);
    } else
    if (event == "MESSAGE_UPDATED") {
      data.event = traQBot::EventType::MessageUpdated;
      data.payload = traQBot::MessageUpdatedEvent().fromJson(*json);
    } else
    if (event == "DIRECT_MESSAGE_CREATED") {
      data.event = traQBot::EventType::DirectMessageCreated;
      data.payload = traQBot::DirectMessageCreatedEvent().fromJson(*json);
    } else
    if (event == "DIRECT_MESSAGE_DELETED") {
      data.event = traQBot::EventType::DirectMessageDeleted;
      data.payload = traQBot::DirectMessageDeletedEvent().fromJson(*json);
    } else
    if (event == "DIRECT_MESSAGE_UPDATED") {
      data.event = traQBot::EventType::DirectMessageUpdated;
      data.payload = traQBot::DirectMessageUpdatedEvent().fromJson(*json);
    } else
    if (event == "BOT_MESSAGE_STAMPS_UPDATED") {
      data.event = traQBot::EventType::BotMessageStampsUpdated;
      data.payload = traQBot::BotMessageStampsUpdatedEvent().fromJson(*json);
    } else
    if (event == "CHANNEL_CREATED") {
      data.event = traQBot::EventType::ChannelCreated;
      data.payload = traQBot::ChannelCreatedEvent().fromJson(*json);
    } else
    if (event == "CHANNEL_TOPIC_CHANGED") {
      data.event = traQBot::EventType::ChannelTopicChanged;
      data.payload = traQBot::ChannelTopicChangedEvent().fromJson(*json);
    } else
    if (event == "USER_CREATED") {
      data.event = traQBot::EventType::UserCreated;
      data.payload = traQBot::UserCreatedEvent().fromJson(*json);
    } else
    if (event == "STAMP_CREATED") {
      data.event = traQBot::EventType::StampCreated;
      data.payload = traQBot::StampCreatedEvent().fromJson(*json);
    } else
    if (event == "TAG_ADDED") {
      data.event = traQBot::EventType::TagAdded;
      data.payload = traQBot::TagAddedEvent().fromJson(*json);
    } else
    if (event == "TAG_REMOVED") {
      data.event = traQBot::EventType::TagRemoved;
      data.payload = traQBot::TagRemovedEvent().fromJson(*json);
    } else
    {
      data.event = traQBot::EventType::Unknown;
    }
  }
  return data;
}

}

#endif

