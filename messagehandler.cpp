#include "messagehandler.h"
#include "StringUtils.h"
#include "logging.h"
#include "pimodule.h"

// ================================================================================================================================
MessageHandler::MessageHandler(TgBot::Bot* bot, uint64_t masterId)
{
    mBot.reset(bot);
    mBot->getEvents().onAnyMessage([this](TgBot::Message::Ptr message){ handleMessage(message);} );

    mMasterId = masterId;

    mPOTD = new PiModule(this);
}
// ================================================================================================================================
MessageHandler::~MessageHandler()
{
    delete mPOTD;
}
// ================================================================================================================================
void MessageHandler::reply(int64_t chatId, std::string message)
{
    mBot->getApi().sendMessage(chatId, message);
}
// ===============================================================================================================================
void MessageHandler::broadcast(TgBot::Message::Ptr origMessage)
{
    std::string restOfMsg = origMessage->text.substr(9, origMessage->text.size());
    std::string pattern("-chat (-?\\d*) -text (.*)");
    std::vector<std::string> args = stringUtils::splitArgs(restOfMsg, pattern);

    if (args.size() != 2)
        return;

    reply(std::strtoll(args.at(0).c_str(), NULL, 10), args.at(1));
}
// ===============================================================================================================================
void MessageHandler::handleMessage(TgBot::Message::Ptr message)
{
    SLog()->logCL(  fmt::format( "Message:\r\n"
                                "  id: {}\r\n"
                                "  text: {}\r\n",
                                message->chat->id,
                                message->text)
                    );

    if (stringUtils::isContains("ping", message->text)) {
        reply(message->chat->id, "pong");
    }

    // admin commands
    if (message->chat->id == mMasterId) {
        // broadcast commands
        if (message->text.starts_with("broadcast")) {
            broadcast(message);
        }
    }

    if (stringUtils::isContains("cat", message->text)) {
        TgBot::InputFile::Ptr catImage = TgBot::InputFile::fromFile("./cat.jpg", "image/jpeg");
        mBot->getApi().sendPhoto(message->chat->id, catImage);
    }

    // POTD mdolu
    if (stringUtils::isContains("/potd", message->text) &&
         (message->chat->id < 0)) {
       mPOTD->handleMessage(message);
    }
}
// ================================================================================================================================
