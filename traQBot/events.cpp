#ifndef TRAQBOT_EVENT_H
#define TRAQBOT_EVENT_H

#include <drogon/drogon.h>
#include <traQBot/events.h>
#include <traQBot/models.h>
#include <traQ/apis/MeApi.h>

namespace traQBot {
   
auto loadEnv(const std::string& name) {
    auto tmp = std::getenv(name.c_str());
    if(tmp){
        return std::string(tmp);
    } else {
        throw std::runtime_error(name + " is not set");
    }
}

Bot::Bot(std::string _verification_token, std::string _access_token) :
    verification_token(_verification_token),
    access_token(_access_token)
{
    drogon::app().registerHandler("/", [*this](const drogon::HttpRequestPtr &req,
    std::function<void (const drogon::HttpResponsePtr &)> &&callback) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        callback(resp);

        auto event = req->getHeader("X-TRAQ-BOT-EVENT");
        auto requestId = req->getHeader("X-TRAQ-BOT-REQUEST-ID");
        auto header_token = req->getHeader("X-TRAQ-BOT-TOKEN");
        if(header_token == verification_token){
            resp->setStatusCode(drogon::HttpStatusCode::k204NoContent);
        } else {
            resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
            return;
        }

        auto json = req->getJsonObject();
        if (json) {
            if (event == "PING") {
                const auto data = traQBot::PingEvent().fromJson(*json);
                on_ping_callback(data);
            } else
            if (event == "JOINED") {
                const auto data = traQBot::JoinedEvent().fromJson(*json);
                on_joined_callback(data);
            } else
            if (event == "LEFT") {
                const auto data = traQBot::LeftEvent().fromJson(*json);
                on_left_callback(data);
            } else
            if (event == "MESSAGE_CREATED") {
                const auto data = traQBot::MessageCreatedEvent().fromJson(*json);
                on_message_created_callback(data);
            } else
            if (event == "MESSAGE_DELETED") {
                const auto data = traQBot::MessageDeletedEvent().fromJson(*json);
                on_message_deleted_callback(data);
            } else
            if (event == "MESSAGE_UPDATED") {
                const auto data = traQBot::MessageUpdatedEvent().fromJson(*json);
                on_message_updated_callback(data);
            } else
            if (event == "DIRECT_MESSAGE_CREATED") {
                const auto data = traQBot::DirectMessageCreatedEvent().fromJson(*json);
                on_direct_message_created_callback(data);
            } else
            if (event == "DIRECT_MESSAGE_DELETED") {
                const auto data = traQBot::DirectMessageDeletedEvent().fromJson(*json);
                on_direct_message_deleted_callback(data);
            } else
            if (event == "DIRECT_MESSAGE_UPDATED") {
                const auto data = traQBot::DirectMessageUpdatedEvent().fromJson(*json);
                on_direct_message_updated_callback(data);
            } else
            if (event == "BOT_MESSAGE_STAMPS_UPDATED") {
                const auto data = traQBot::BotMessageStampsUpdatedEvent().fromJson(*json);
                on_bot_message_stamps_updated_callback(data);
            } else
            if (event == "CHANNEL_CREATED") {
                const auto data = traQBot::ChannelCreatedEvent().fromJson(*json);
                on_channel_created_callback(data);
            } else
            if (event == "CHANNEL_TOPIC_CHANGED") {
                const auto data = traQBot::ChannelTopicChangedEvent().fromJson(*json);
                on_channel_topic_changed_callback(data);
            } else
            if (event == "USER_CREATED") {
                const auto data = traQBot::UserCreatedEvent().fromJson(*json);
                on_user_created_callback(data);
            } else
            if (event == "USER_ACTIVATED") {
                const auto data = traQBot::UserActivatedEvent().fromJson(*json);
                on_user_activated_callback(data);
            } else
            if (event == "STAMP_CREATED") {
                const auto data = traQBot::StampCreatedEvent().fromJson(*json);
                on_stamp_created_callback(data);
            } else
            if (event == "TAG_ADDED") {
                const auto data = traQBot::TagAddedEvent().fromJson(*json);
                on_tag_added_callback(data);
            } else
            if (event == "TAG_REMOVED") {
                const auto data = traQBot::TagRemovedEvent().fromJson(*json);
                on_tag_removed_callback(data);
            } else
            {
                // Unknown event;
            }
        }
    });
    drogon::app().getLoop()->runAfter(std::chrono::seconds(0), [*this](){
        traQApi::MeApi cli("https://q.trap.jp", "/api/v3");
        const auto [_res, _resp, me] = cli.getMe();
        if(me) {
            uuid = me->id;
            username = me->name;
            home_channel_id = me->homeChannel;
        }
    });
}

void Bot::enable_mysql_ns() {
    auto mariadb_hostname = loadEnv("NS_MARIADB_HOSTNAME");
    auto mariadb_database = loadEnv("NS_MARIADB_DATABASE");
    auto mariadb_username = loadEnv("NS_MARIADB_USER");
    auto mariadb_password = loadEnv("NS_MARIADB_PASSWORD");
    drogon::app().createDbClient("mysql", mariadb_hostname, 3306, mariadb_database, mariadb_username, mariadb_password);
}

void Bot::start() {
    drogon::app().run();
}

}

#endif
