#include <string>
#include <vector>
#include <json/json.h>

namespace traQBot {
struct User {
  std::string id;
  std::string name;
  std::string displayName;
  std::string iconId;
  bool bot;
  auto& fromJson(const Json::Value& _json) {
    this->id = _json["id"].asString();
    this->name = _json["name"].asString();
    this->displayName = _json["displayName"].asString();
    this->iconId = _json["iconId"].asString();
    this->bot = _json["bot"].asBool();
    return *this;
  }
};
struct Channel {
  std::string id;
  std::string name;
  std::string path;
  std::string parentId;
  User creator;
  std::string createdAt;
  std::string updatedAt;
  auto& fromJson(const Json::Value& _json) {
    this->id = _json["id"].asString();
    this->name = _json["name"].asString();
    this->path = _json["path"].asString();
    this->parentId = _json["parentId"].asString();
    this->creator = User().fromJson(_json["creator"]);
    this->createdAt = _json["createdAt"].asString();
    this->updatedAt = _json["updatedAt"].asString();
    return *this;
  }
};
struct MessageEmbedded {
  std::string raw;
  std::string type;
  std::string id;
  auto& fromJson(const Json::Value& _json) {
    this->raw = _json["raw"].asString();
    this->type = _json["type"].asString();
    this->id = _json["id"].asString();
    return *this;
  }
};
struct Message {
  std::string id;
  User user;
  std::string channelId;
  std::string text;
  std::string plainText;
  std::vector<MessageEmbedded> embedded;
  std::string createdAt;
  std::string updatedAt;
  auto& fromJson(const Json::Value& _json) {
    this->id = _json["id"].asString();
    this->user = User().fromJson(_json["user"]);
    this->channelId = _json["channelId"].asString();
    this->text = _json["text"].asString();
    this->plainText = _json["plainText"].asString();
    for(const auto& _subitem : _json["embedded"]) {
      this->embedded.push_back(MessageEmbedded().fromJson(_subitem));
    }
    this->createdAt = _json["createdAt"].asString();
    this->updatedAt = _json["updatedAt"].asString();
    return *this;
  }
};
struct MessageDeleted {
  std::string id;
  std::string channelId;
  auto& fromJson(const Json::Value& _json) {
    this->id = _json["id"].asString();
    this->channelId = _json["channelId"].asString();
    return *this;
  }
};
struct DirectMessageDeleted {
  std::string id;
  std::string userId;
  std::string channelId;
  auto& fromJson(const Json::Value& _json) {
    this->id = _json["id"].asString();
    this->userId = _json["userId"].asString();
    this->channelId = _json["channelId"].asString();
    return *this;
  }
};
struct StampCount {
  std::string stampId;
  std::string userId;
  int32_t count;
  std::string createdAt;
  std::string updatedAt;
  auto& fromJson(const Json::Value& _json) {
    this->stampId = _json["stampId"].asString();
    this->userId = _json["userId"].asString();
    this->count = _json["count"].asInt();
    this->createdAt = _json["createdAt"].asString();
    this->updatedAt = _json["updatedAt"].asString();
    return *this;
  }
};
}


