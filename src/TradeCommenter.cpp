#include <TradeCommenter.h>

TradeCommenter::TradeCommenter(rapidjson::Value& params,
               rapidjson::Value& data,
               rapidjson::Document::AllocatorType& allocator,
               CServerInterface* server)
    : _server(server),
      _config(params),
      _is_running(false) {
    try {
        std::cout << "[TradeCommenter]: Plugin initialized." << std::endl;
        _is_running = true;
    } catch (const std::exception& e) {
        std::cerr << "[TradeCommenter]: Plugin initialization failed. " << e.what() << std::endl;
    }
}

TradeCommenter::~TradeCommenter() {
    _is_running = false;
}

int TradeCommenter::HookTradeRequestOpen(const TradeRecord& trade,
                                 const GroupRecord& group,
                                 const SymbolRecord& symbol,
                                 const AccountRecord& account,
                                 const MarginLevel& margin,
                                 TradeDiffRecord& diff) {

    try {
        if (IsTradeCommentUpdateRequired(account, _config.GetTrackLogins())) {
            BuildComment(diff.comment, trade, symbol);
            return RET_OK_CHANGE;
        }
        return RET_OK;
    } catch (const std::exception& e) {
        std::cerr << "[TradeCommenter]: Failed to build comment: " << e.what() << std::endl;
        return RET_OK;
    }

}

bool TradeCommenter::IsTradeCommentUpdateRequired(const AccountRecord& account,
                                                  const std::vector<int>& track_logins) {
    if (track_logins.empty()) return false;
    return std::ranges::binary_search(track_logins, account.login);
}

void TradeCommenter::BuildComment(std::string& comment,
                                  const TradeRecord& trade,
                                  const SymbolRecord& symbol) {
    std::ostringstream oss;
    char timeBuf[64];

    std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", std::localtime(&trade.open_time));

    oss << "⚡ TRADE SNAPSHOT ⚡\n";
    oss << "──────────────────\n";
    oss << "• Time: " << timeBuf << "\n";
    oss << "• Bid/Ask: "
        << symbol.bid << "/" << symbol.ask << "\n";
    oss << "• Contract: " << symbol.contract_size << " " << symbol.currency << "\n";
    oss << "• Margin: " << std::fixed << std::setprecision(2)
        << trade.margin_initial << " " << symbol.margin_currency << "\n";
    oss << "──────────────────\n";
    oss << "Snapshot captured at open";

    comment = oss.str();
}

// C-compatible factory functions
extern "C" PluginInterface* CreatePlugin(rapidjson::Value& params,
                                         rapidjson::Value& data,
                                         rapidjson::Document::AllocatorType& allocator,
                                         CServerInterface* server) {
    return new TradeCommenter(params, data, allocator, server);
}

extern "C" void DestroyPlugin(PluginInterface* plugin) {
    delete static_cast<TradeCommenter*>(plugin);
}
