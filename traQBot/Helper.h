#ifndef TRAQBOT_HELPER_H
#define TRAQBOT_HELPER_H

#include <traQBot/traQBot.h>
#include <string>
#include <memory>

template<class T, class Tcb>
class traQBotControllerBase : public drogon::HttpController<traQBotControllerBase<T, Tcb>, false> {
    std::string verification_token;
    std::shared_ptr<Tcb> bot_callback;
  public:
    traQBotControllerBase(const std::string& verification_token, const std::shared_ptr<Tcb>& bot_callback)
        : verification_token(verification_token), bot_callback(bot_callback) {}
    static void initPathRouting() {
        traQBotControllerBase<T, Tcb>::registerMethod(&T::proc, "/", { drogon::HttpMethod::Post }, false);
    }
    void proc(const drogon::HttpRequestPtr &req,
        std::function<void (const drogon::HttpResponsePtr &)> &&callback,
        traQBot::EventData &&eventData) const {
        auto resp = drogon::HttpResponse::newHttpResponse();
        callback(resp);

        if(eventData.token == verification_token){
            resp->setStatusCode(drogon::HttpStatusCode::k204NoContent);
        } else {
            resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
            return;
        }

        if(bot_callback)
            std::visit(*bot_callback, eventData.payload);
    }
};

template<class Tcb>
auto makeBot(const std::string& verificationToken, const std::shared_ptr<Tcb>& callback){
    class traQBotController : public traQBotControllerBase<traQBotController, Tcb> {
    public:
        traQBotController(const std::string& verification_token, const std::shared_ptr<Tcb>& bot_callback)
            : traQBotControllerBase<traQBotController, Tcb>(verification_token, bot_callback) {}
    };
    return std::make_shared<traQBotController>(verificationToken, callback);
}

auto loadEnv(const std::string& name) {
    auto tmp = std::getenv(name.c_str());
    if(tmp){
        return std::string(tmp);
    } else {
        throw std::runtime_error(name + "is not set");
    }
}

#endif
