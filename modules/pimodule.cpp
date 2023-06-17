#include "pimodule.h"
#include "jsonutils.h"
#include "StringUtils.h"
#include "messagehandler.h"

/*
potd_start - Start POTD for this chat
potd_addme - Add you to participants list
potd_select - Run election for todays pidor
potd_get - Get todays pidor
potd_getall - Get pidors leaderboard
*/

namespace config {
    constexpr std::string_view fileFmt = "POTD_{}";
    constexpr std::string_view folder = "./POTD/data/";
}

// ================================================================================================================================
PiModule::PiModule(MessageHandler* newBot)
{
    mBot = newBot;
}
// ===============================================================================================================================
PiModule::~PiModule()
{
    mChats.clear();
}
// ===============================================================================================================================
void PiModule::handleMessage(TgBot::Message::Ptr message)
{
    std::string mText = message->text;
    int64_t chatId = message->chat->id;
    bool isInited = mChats.contains(chatId);


    if (stringUtils::isContains(mText, "/potd_start")) {
        // contains
        if (isInited) {
            mBot->reply(chatId, "Пидор Дня уже запущен в этом чате!");
        } else {
            mBot->reply(chatId, "Запускаю Пидор Дня!");
            mChats.emplace(chatId, JsonUtils::create());
        }

        return;
    }

    //
    if (stringUtils::isContains(mText, "/potd_addme")) {
        if (isInited) {

        }
    }


}
// ===============================================================================================================================
void PiModule::openForChat(int64_t chat_id)
{
    std::string filename = fmt::format(config::fileFmt, chat_id);
    SLog()->logCL(filename);
}
// ================================================================================================================================
