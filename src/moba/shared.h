/*
 *  Project:    moba-lib-msghandling
 *
 *  Copyright (C) 2019 Stefan Paproth <pappi-@gmx.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once

#include <memory>
#include <moba-common/version.h>
#include "groups.h"

struct AppData {
    AppData() {
    }

    AppData(
        const std::string &appName, const moba::common::Version &version, Groups groups
    ) : appName{appName}, version{version}, groups{groups} {
    }

    template <typename T>
    AppData(const T &d) {
        appName = d["appName"].GetString();
        version = d["version"].GetString();
    }

    std::string appName;
    moba::common::Version version;
    Groups groups;
};


struct EndpointData {
    EndpointData(
        const AppData &appInfo, long appId, const std::string &startTime, const std::string &addr, long port
    ) : appInfo{appInfo}, appId{appId}, startTime{startTime}, addr{addr} {
    }

    template <typename T>
    EndpointData(const T &d) {
        appId = d["appID"].GetInt();
        addr = d["addr"].GetString();
        port = d["port"].GetInt();
        startTime = d["startTime"].GetString();
        appInfo = AppData{d["appInfo"]};
    }

    AppData     appInfo;
    long        appId;
    std::string startTime;
    std::string addr;
    long        port;
};
/*
struct TrackLayoutData {
    TrackLayoutData(
        int id, const std::string &name, const std::string &description, const std::string &created, const std::string &modified, bool active, int locked
    ) : id{id}, name{name}, description{description}, created{created}, modified{modified}, active{active}, locked{locked} {

    }

    TrackLayoutData(
        const std::string &name, const std::string &description, bool active
    ) : name{name}, description{description}, active{active} {

    }

    TrackLayoutData(moba::JsonObjectPtr appData) {
        id = moba::castToInt(appData->at("id"));
        name = moba::castToString(appData->at("name"));
        description = moba::castToString(appData->at("description"));
        created = moba::castToString(appData->at("created"));
        modified = moba::castToString(appData->at("modified"));
        active = moba::castToBool(appData->at("active"));
        locked = moba::castToInt(appData->at("locked"));
    }

	int id;
    std::string name;
    std::string description;
    std::string created;
    std::string modified;
    bool active;
    int locked;
};

struct TrackLayoutSymbolData {
    TrackLayoutSymbolData(moba::JsonObjectPtr s) {
        id = moba::castToInt(s->at("id"));
        xPos = moba::castToInt(s->at("xPos"));
        yPos = moba::castToInt(s->at("yPos"));
        symbol = moba::castToInt(s->at("symbol"));
    }
	int id;
    int xPos;
    int yPos;
	int symbol;
};

struct SpecificLayoutData {
    SpecificLayoutData(moba::JsonObjectPtr appData) {
        id = moba::castToInt(appData->at("id"));
        auto v = std::dynamic_pointer_cast<moba::JsonArray>(appData->at("symbols"));
        for(auto iter = v->begin(); iter != v->end(); ++iter) {
            symbols.push_back(std::dynamic_pointer_cast<moba::JsonObject>(*iter));
        }


        //groups = appData->at("msgGroups"));

    }

    int id;
    std::vector<TrackLayoutSymbolData> symbols;
};
*/
struct Contact {
    Contact(int modulAddr = 0, int contactNb = 0) : modulAddr{modulAddr}, contactNb{contactNb} {
    }

    template <typename T>
    Contact(const T &d) {
        modulAddr = d["modulAddr"].GetInt();
        contactNb = d["contactNb"].GetInt();
    }

    int modulAddr;
    int contactNb;
};

struct ContactTrigger {
    ContactTrigger(
        int modulAddr, int contactNb, bool state, int time
    ) : contact{modulAddr, contactNb}, state{state}, time{time} {

    }

    Contact contact;
	bool state;
	int time;
};

struct BrakeVectorContact {
    template <typename T>
    BrakeVectorContact(const T &d) {
        contact = Contact{d["contact"]};
        locId = d["locId"].GetInt();
    }

    Contact contact;
    int locId;
};

namespace moba {

}

struct JsonSwitch {
    enum class Switch {
        ON,
        AUTO,
        UNSET,
        TRIGGER,
        OFF
    };

    JsonSwitch(const std::string &s) {
        if(s == "ON") {
            v = Switch::ON;
        } else if(s == "AUTO") {
            v = Switch::AUTO;
        } else if(s == "UNSET") {
            v = Switch::UNSET;
        } else if(s == "TRIGGER") {
            v = Switch::TRIGGER;
        } else if(s == "OFF") {
            v = Switch::OFF;
        } else {
          //  throw UnsupportedOperationException("IPC::Command is invalid");
        }
    }

    JsonSwitch(JsonSwitch::Switch v) : v{v} {
    }

    std::string getJsonString() const {
        switch(this->v) {
            case Switch::ON:
                return "ON";

            case Switch::OFF:
                return "OFF";

            case Switch::AUTO:
                return "AUTO";

            case Switch::UNSET:
                return "UNSET";

            case Switch::TRIGGER:
                return "TRIGGER";

            //default:
              //  throw UnsupportedOperationException("IPC::Command is invalid");
        }
    }

    Switch getVal() {
        return this->v;
    }

protected:
    Switch v;
};

struct JsonToggleState {
    enum class ToggleState {
        ON,
        OFF,
        UNSET
    };

    JsonToggleState(const std::string &s) {
        if(s == "ON") {
            v = ToggleState::ON;
        } else if(s == "UNSET") {
            v = ToggleState::UNSET;
        } else if(s == "OFF") {
            v = ToggleState::OFF;
        } else {
            //throw UnsupportedOperationException("IPC::Command is invalid");
        }
    }

    JsonToggleState(JsonToggleState::ToggleState v) : v{v} {
    }

    std::string getJsonString() const {
        switch(this->v) {
            case ToggleState::ON:
                return "ON";

            case ToggleState::OFF:
                return "OFF";

            case ToggleState::UNSET:
                return "UNSET";

           // default:
           //     throw UnsupportedOperationException("IPC::Command is invalid");
        }
    }

    ToggleState getVal() {
        return this->v;
    }

protected:
    ToggleState v;
};


struct JsonThreeState {
    enum class ThreeState {
        ON,
        OFF,
        AUTO,
        UNSET
    };

    JsonThreeState(const std::string &s) {
        if(s == "ON") {
            v = ThreeState::ON;
        } else if(s == "OFF") {
            v = ThreeState::OFF;
        } else if(s == "AUTO") {
            v = ThreeState::AUTO;
        } else if(s == "UNSET") {
            v = ThreeState::UNSET;
        } else {
           // throw UnsupportedOperationException("IPC::Command is invalid");
        }
    }

    JsonThreeState(JsonThreeState::ThreeState v) : v(v) {
    }

    std::string getJsonString() const {
        switch(this->v) {
            case ThreeState::ON:
                return "ON";

            case ThreeState::OFF:
                return "OFF";

            case ThreeState::AUTO:
                return "AUTO";

            case ThreeState::UNSET:
                return "UNSET";

           // default:
           //     throw UnsupportedOperationException("IPC::Command is invalid");
        }
    }

    ThreeState getVal() {
        return this->v;
    }

protected:
    ThreeState v;
};


/*
     enum class ErrorId {
        SAME_ORIGIN_NEEDED,
        INVALID_APP_ID,
        FAULTY_MESSAGE,
        INVALID_DATA_SEND,
        DATASET_NOT_LOCKED,
        DATASET_LOCKED,
        DATASET_MISSING,
        INVALID_STATUS_CHANGE,
        DATABASE_ERROR,
        UNKNOWN_ERROR,
        NO_DEFAULT_GIVEN
    };

    ClientError(const rapidjson::Document &d) {
        errorIdAsString = d["errorId"].GetString();
        if(errorIdAsString == "SAME_ORIGIN_NEEDED") {
            errorId = ErrorId::SAME_ORIGIN_NEEDED;
        } else if(errorIdAsString == "INVALID_APP_ID") {
            errorId = ErrorId::INVALID_APP_ID;
        } else if(errorIdAsString == "FAULTY_MESSAGE") {
            errorId = ErrorId::FAULTY_MESSAGE;
        } else if(errorIdAsString == "INVALID_DATA_SEND") {
            errorId = ErrorId::INVALID_DATA_SEND;
        } else if(errorIdAsString == "DATASET_NOT_LOCKED") {
            errorId = ErrorId::DATASET_NOT_LOCKED;
        } else if(errorIdAsString == "DATASET_LOCKED") {
            errorId = ErrorId::DATASET_LOCKED;
        } else if(errorIdAsString == "DATASET_MISSING") {
            errorId = ErrorId::DATASET_MISSING;
        } else if(errorIdAsString == "INVALID_STATUS_CHANGE") {
            errorId = ErrorId::INVALID_STATUS_CHANGE;
        } else if(errorIdAsString == "DATABASE_ERROR") {
            errorId = ErrorId::DATABASE_ERROR;
        } else if(errorIdAsString == "NO_DEFAULT_GIVEN") {
            errorId = ErrorId::NO_DEFAULT_GIVEN;
        } else {
            errorId = ErrorId::UNKNOWN_ERROR;
        }

        additionalMsg = d["additonalMsg"].GetString();
    }


 */