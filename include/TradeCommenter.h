#pragma once

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <PluginInterface.h>
#include <ServerConfig.h>
#include <TradeCommenter.h>
#include <rapidjson/document.h>

// Main plugin class that handles trade events and produces structured trade comments
class TradeCommenter final : public PluginInterface, public HookTrade {
public:
    TradeCommenter(rapidjson::Value& params,
           rapidjson::Value& data,
           rapidjson::Document::AllocatorType& allocator,
           CServerInterface* server);

    ~TradeCommenter() override;

    int HookTradeRequestOpen(const TradeRecord& trade,
                             const GroupRecord& group,
                             const SymbolRecord& symbol,
                             const AccountRecord& account,
                             const MarginLevel& margin,
                             TradeDiffRecord& diff) override;

    bool IsTradeCommentUpdateRequired(const AccountRecord& account, const std::vector<int>& track_logins);

    void BuildComment(std::string& comment,
                      const TradeRecord& trade,
                      const SymbolRecord& symbol);

private:
    CServerInterface* _server;
    ServerConfig _config;
    bool _is_running;
};
