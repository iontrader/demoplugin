#pragma once

#include <vector>
#include <algorithm>
#include <ranges>
#include <rapidjson/document.h>
#include <Structures.h>


// Parses and stores server configuration parameters from a JSON object
class ServerConfig {
public:
    explicit ServerConfig(rapidjson::Value& json_config);

    // Getters
    [[nodiscard]] const std::vector<int>& GetTrackLogins() const;

private:
    std::vector<int> _track_logins;

    void ParseConfig(rapidjson::Value& json_config);
};
