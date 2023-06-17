#include <iostream>
#include <exception>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <tgbot/tgbot.h>
#include "logging.h"
#include "messagehandler.h"
#include "StringUtils.h"
#include "jsonutils.h"

// ================================================================================================================================
int main()
{
    std::string tokenString = "";
    int64_t masterId = 0;

    if (JsonUtils* settingsJson = JsonUtils::create("settings.json")) {
        tokenString = settingsJson->getValue("token");
        masterId = std::strtoll(settingsJson->getValue("master_id").c_str(), 0, 10);
        delete settingsJson;
    }

    std::string token(tokenString);
    TgBot::Bot* myBot = new TgBot::Bot(token);

    std::unique_ptr<Log> Logger;
    Logger.reset(Log::getInstance());

    std::unique_ptr<MessageHandler> msgHandler;
    msgHandler.reset(new MessageHandler(myBot, masterId));

    try {
        Logger->logCL(fmt::format("{0} ready", myBot->getApi().getMe()->firstName));

        myBot->getApi().deleteWebhook();
        TgBot::TgLongPoll longPoll(*myBot);

        while (true) {
            longPoll.start();
        }
    } catch (std::exception& e) {
        Logger->logCL("ERROR:");
        Logger->logCL(fmt::format("\t {0}", e.what()));
    }

    Logger->logCL("QUITTING");

    return 0;
}
// ================================================================================================================================

