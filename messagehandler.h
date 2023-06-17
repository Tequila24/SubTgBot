#pragma once

#include "tgbot/tgbot.h"

class PiModule;

class MessageHandler
{
public:
    MessageHandler(TgBot::Bot* bot, uint64_t masterId);
    ~MessageHandler();

    void reply(int64_t chatId, std::string message);
    void broadcast(TgBot::Message::Ptr origMessage);


protected:  // methods
    void handleMessage(TgBot::Message::Ptr message);

protected:  // vars
    std::unique_ptr<TgBot::Bot> mBot;
    uint64_t mMasterId = 0;

    PiModule* mPOTD = nullptr;
};
