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
    std::string verification_token, token, uuid, username, home_channel_id;
    std::function<void(Ping)> on_ping_callback;
    std::function<void(Joined)> on_joined_callback;
    std::function<void(Left)> on_left_callback;
    std::function<void(MessageCreated)> on_message_created_callback;
    std::function<void(MessageDeleted)> on_message_deleted_callback;
    std::function<void(MessageUpdated)> on_message_updated_callback;
    std::function<void(DirectMessageCreated)> on_direct_message_created_callback;
    std::function<void(DirectMessageDeleted)> on_direct_message_deleted_callback;
    std::function<void(DirectMessageUpdated)> on_direct_message_updated_callback;
    std::function<void(BotMessageStampsUpdated)> on_bot_message_stamps_updated_callback;
    std::function<void(ChannelCreated)> on_channel_created_callback;
    std::function<void(ChannelTopicChanged)> on_channel_topic_changed_callback;
    std::function<void(UserCreated)> on_user_created_callback;
    std::function<void(UserActivated)> on_user_activated_callback;
    std::function<void(StampCreated)> on_stamp_created_callback;
    std::function<void(TagAdded)> on_tag_added_callback;
    std::function<void(TagRemoved)> on_tag_removed_callback;
    auto loadEnv(const std::string& name) {
        auto tmp = std::getenv(name.c_str());
        if(tmp){
            return std::string(tmp);
        } else {
            throw std::runtime_error(name + " is not set");
        }
    }
public:
    std::string get_uuid() { return uuid; }
    std::string get_username() { return username; }
    std::string get_home_channel_id() { return home_channel_id; }
    traQBot(std::string _verification_token, std::string _token) :
        verification_token(_verification_token),
        token(_token)
    {
        drogon::app().registerHandler("/", [this](const drogon::HttpRequestPtr &req,
        std::function<void (const drogon::HttpResponsePtr &)> &&callback) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            callback(resp);

            if(eventData.token == verification_token){
                resp->setStatusCode(drogon::HttpStatusCode::k204NoContent);
            } else {
                resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
                return;
            }

            auto event = req.getHeader("X-TRAQ-BOT-EVENT");
            auto requestId = req.getHeader("X-TRAQ-BOT-REQUEST-ID");
            auto token = req.getHeader("X-TRAQ-BOT-TOKEN");
            auto json = req.getJsonObject();
            if (json) {
                if (event == "PING") {
                    const auto data = traQBot::PingEvent().fromJson(*json);
                    this->on_ping_callback(data);
                } else
                if (event == "JOINED") {
                    const auto data = traQBot::JoinedEvent().fromJson(*json);
                    this->on_joined_callback(data);
                } else
                if (event == "LEFT") {
                    const auto data = traQBot::LeftEvent().fromJson(*json);
                    this->on_left_callback(data);
                } else
                if (event == "MESSAGE_CREATED") {
                    const auto data = traQBot::MessageCreatedEvent().fromJson(*json);
                    this->on_message_created_callback(data);
                } else
                if (event == "MESSAGE_DELETED") {
                    const auto data = traQBot::MessageDeletedEvent().fromJson(*json);
                    this->on_message_deleted_callback(data);
                } else
                if (event == "MESSAGE_UPDATED") {
                    const auto data = traQBot::MessageUpdatedEvent().fromJson(*json);
                    this->on_message_updated_callback(data);
                } else
                if (event == "DIRECT_MESSAGE_CREATED") {
                    const auto data = traQBot::DirectMessageCreatedEvent().fromJson(*json);
                    this->on_direct_message_created_callback(data);
                } else
                if (event == "DIRECT_MESSAGE_DELETED") {
                    const auto data = traQBot::DirectMessageDeletedEvent().fromJson(*json);
                    this->on_direct_message_deleted_callback(data);
                } else
                if (event == "DIRECT_MESSAGE_UPDATED") {
                    const auto data = traQBot::DirectMessageUpdatedEvent().fromJson(*json);
                    this->on_direct_message_updated_callback(data);
                } else
                if (event == "BOT_MESSAGE_STAMPS_UPDATED") {
                    const auto data = traQBot::BotMessageStampsUpdatedEvent().fromJson(*json);
                    this->on_bot_message_stamps_updated_callback(data);
                } else
                if (event == "CHANNEL_CREATED") {
                    const auto data = traQBot::ChannelCreatedEvent().fromJson(*json);
                    this->on_channel_created_callback(data);
                } else
                if (event == "CHANNEL_TOPIC_CHANGED") {
                    const auto data = traQBot::ChannelTopicChangedEvent().fromJson(*json);
                    this->on_channel_topic_changed_callback(data);
                } else
                if (event == "USER_CREATED") {
                    const auto data = traQBot::UserCreatedEvent().fromJson(*json);
                    this->on_user_created_callback(data);
                } else
                if (event == "USER_ACTIVATED") {
                    const auto data = traQBot::UserActivatedEvent().fromJson(*json);
                    this->on_user_activated_callback(data);
                } else
                if (event == "STAMP_CREATED") {
                    const auto data = traQBot::StampCreatedEvent().fromJson(*json);
                    this->on_stamp_created_callback(data);
                } else
                if (event == "TAG_ADDED") {
                    const auto data = traQBot::TagAddedEvent().fromJson(*json);
                    this->on_tag_added_callback(data);
                } else
                if (event == "TAG_REMOVED") {
                    const auto data = traQBot::TagRemovedEvent().fromJson(*json);
                    this->on_tag_removed_callback(data);
                } else
                {
                    // Unknown event;
                }
            }
        });
        drogon::app().getLoop()->runAfter(std::chrono::seconds(0), [](){
            traQApi::MeApi cli("https://q.trap.jp", "/api/v3");
            const auto [_res, _resp, me] = cli.getMe();
            if(me) {
                uuid = me->id;
                username = me->name;
                home_channel_id = me->homeChannel;
            }
        });
    }
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

    void enable_mysql_ns() {
        auto mariadb_hostname = loadEnv("NS_MARIADB_HOSTNAME");
        auto mariadb_database = loadEnv("NS_MARIADB_DATABASE");
        auto mariadb_username = loadEnv("NS_MARIADB_USER");
        auto mariadb_password = loadEnv("NS_MARIADB_PASSWORD");
        drogon::app().createDbClient("mysql", mariadb_hostname, 3306, mariadb_database, mariadb_username, mariadb_password);
    }
    void start() {
        drogon::app().run();
    }
}

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
        if (event == "USER_ACTIVATED") {
            data.event = traQBot::EventType::UserActivated;
            data.payload = traQBot::UserActivatedEvent().fromJson(*json);
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
