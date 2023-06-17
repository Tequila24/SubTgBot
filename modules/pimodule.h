#pragma once

#include "tgbot/tgbot.h"

class JsonUtils;
class MessageHandler;

class PiModule
{
public:
    PiModule(MessageHandler* newBot);
    ~PiModule();

    void handleMessage(TgBot::Message::Ptr message);

    void openForChat(int64_t chat_id);

protected:


protected: //
    MessageHandler* mBot = nullptr;
    std::map<int64_t, JsonUtils*> mChats;

};
