#include <ServerConfig.h>

ServerConfig::ServerConfig(rapidjson::Value& json_config)
    : _track_logins() {
    parseConfig(json_config);

    std::cout << "[ServerConfig]: tracked logins:" << std::endl;

    for (const int& login : _track_logins) {
        std::cout << " " << login << "," << std::endl;
    }
}

void ServerConfig::parseConfig(rapidjson::Value& json_config) {
    if (!json_config.HasMember("config") || !json_config["config"].IsObject()) {
        std::cerr << "[ServerConfig]: The 'config' field is missing or has invalid type" << std::endl;
        return;
    }

    const rapidjson::Value& config = json_config["config"];

    if (config.HasMember("track_logins") && config["track_logins"].IsArray()) {
        const rapidjson::Value& track_logins = config["track_logins"];

        bool allValuesAreInt = true;

        for (rapidjson::SizeType i = 0; i < track_logins.Size(); ++i) {
            const rapidjson::Value& track_login = track_logins[i];

            if (!track_login.IsInt()) {
                _track_logins.clear();
                allValuesAreInt = false;
                break;
            }

            _track_logins.push_back(track_login.GetInt());
        }

        if (allValuesAreInt) {
            std::ranges::sort(_track_logins);

            std::cout << "[ServerConfig]: Valid int array, size: "
                << _track_logins.size() << std::endl;
        } else {
            _track_logins.clear();
            std::cerr << "[ServerConfig]: Invalid int array, contains non-int values!" << std::endl;
        }
    }
}

const std::vector<int>& ServerConfig::GetTrackLogins() const {
    return _track_logins;
}
