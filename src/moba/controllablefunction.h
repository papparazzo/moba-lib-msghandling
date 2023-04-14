/*
 *  Project:    moba-lib-msghandling
 * 
 *  Copyright (C) 2023 Stefan Paproth <pappi-@gmx.de>
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

#include <moba-common/exception.h>

enum class ControllableFunction {
    HEADLIGHTS                  = 1,   // Stirnbeleuchtung
    INTERIOR_LIGHT              = 2,   // Innenbeleuchtung
    EXTERIOR_LIGHT              = 3,   // Rücklicht
    LONG_DISTANCE_LIGHTS        = 4,   // Fernlicht
    SOUND                       = 5,   // Geräusch nicht näher spezifiziert
    PANTO                       = 6,   // Pantograf
    SMOKE_UNIT                  = 7,   // Rauchgenerator
    SWITCHING_RANGE_ON          = 8,   // Rangiergang
    TELEX                       = 9,   // Telexkupplung beidseitig
    HORN                        = 10,  // Horn
    CONDUCTOR_WHISTLE           = 11,  // Schaffnerpfiff
    WHISTLE_LONG                = 12,  // Lockpfeife lang
    BELL                        = 13,  // Glocke
    ABV_OFF                     = 18,  // ABV aus
    AIRPUMP                     = 19,  // Luftpumpe
    BRAKE_SQUEALING             = 20,  // Bremsenquietschen (aus)
    GRATE_SHAKING               = 21,  // Schüttelrost Wie 36…
    GENERATOR                   = 22,  // Generator
    OPERATION_SOUNDS            = 23,  // Betriebsgeräusch
    SHOVELING_COAL              = 26,  // Kohle schaufeln Wie 31…
    DOORSCLOSING                = 28,  // Türenschließen Wie 156…
    BLOWERS                     = 29,  // Lüfter
    SHOVELING_COAL_2            = 31,  // Brennergeräusch Wie 26…
    CEILING_LIGHT               = 32,  // Deckenlicht
    TABLE_LIGHT_2               = 34,  // Tischlicht 2
    GRATE_SHAKING_2             = 36,  // Schüttelrost Wie 21…
    RAIL_JOINTS                 = 37,  // Schienenstoß
    REAR_LIGHT                  = 41,  // Führerstand hinten
    FRONT_LIGHT                 = 42,  // Führerstand vorne
    COUPLING_UNCOUPLING_SOUND   = 43,  // An-/Abkuppelngeräusch Wie 171…
    SPEECHOUTPUT                = 45,  // Umgebungsgeräusch: Bahnhof
    CAB_LIGHT                   = 48,  // Führerstandsbeleuchtung
    INJECTOR                    = 49,  // Injektor
    REAR_TELEX                  = 82,  // Telexkupplung hinten
    FRONT_TELEX                 = 83,  // Telexkupplung vorne
    REAR_PANTO                  = 84,  // Pantograf hinten
    FRONT_PANTO                 = 85,  // Pantograf vorne
    RUNNING_GEARLIGHT           = 90,  // Triebwerksbeleuchtung
    PANTO_SOUND_UP_DOWN         = 101, // Pantograph-Geräusch (hoch/nieder)
    STATION_ANNOUNCEMENT        = 107, // Bahnhofsdurchsage Wie 153…
    FEED_WATER_PUMP             = 111, // Wasserpumpe
    COMPRESSED_AIR              = 116, // Luftpresser
    // = 133,// Überdruckventil kein eigens Piktogramm!
    RELAYSTEPS                  = 133, // Schaltstufen kein eigens Piktogramm!
    // = 137,// Kupplungswalzer
    HORN_SHORT                  = 138, // Rangierhorn kurz
    WHISTLE_SHORT               = 140, // Rangierpfiff kurz
    STATION_ANNOUNCEMENT_2      = 153, // Bahnhofsdurchsage Wie 107…
    DOORS_CLOSING               = 156, // Türenschließen
    COUPLING_UNCOUPLING_SOUND_2 = 171, // An-/Abkuppelngeräusch Wie 43…
    BUFFERS_STRIKING            = 172, // Pufferstoß
    SPEECHOUTPUT_2              = 173, // Sprachausgabe
    CYLINDER_STEAM              = 219, // Zylinder / Dampf
    COMPRESSED_AIR_2            = 220, // Pressluft ablasssen
    RADIO_DIALOG                = 231, // Funkgespräch
    PLATFORM_ANNOUNCEMENT       = 232, // Bahnsteigdurchsage
    CAB_CONVERSATION            = 235, // Führerstandsgespräch
    SANDING                     = 236, // Sanden
};

inline ControllableFunction stringToControllableFunctionEnum(const std::string &s) {
    if(s == "HEADLIGHTS") {
        return ControllableFunction::HEADLIGHTS;
    }
    if(s == "INTERIOR_LIGHT") {
        return ControllableFunction::INTERIOR_LIGHT;
    }
    if(s == "EXTERIOR_LIGHT") {
        return ControllableFunction::EXTERIOR_LIGHT;
    }
    if(s == "LONG_DISTANCE_LIGHTS") {
        return ControllableFunction::LONG_DISTANCE_LIGHTS;
    }
    if(s == "SOUND") {
        return ControllableFunction::SOUND;
    }
    if(s == "PANTO") {
        return ControllableFunction::PANTO;
    }
    if(s == "SMOKE_UNIT") {
        return ControllableFunction::SMOKE_UNIT;
    }
    if(s == "SWITCHING_RANGE_ON") {
        return ControllableFunction::SWITCHING_RANGE_ON;
    }
    if(s == "TELEX") {
        return ControllableFunction::TELEX;
    }
    if(s == "HORN") {
        return ControllableFunction::HORN;
    }
    if(s == "CONDUCTOR_WHISTLE") {
        return ControllableFunction::CONDUCTOR_WHISTLE;
    }
    if(s == "WHISTLE_LONG") {
        return ControllableFunction::WHISTLE_LONG;
    }
    if(s == "BELL") {
        return ControllableFunction::BELL;
    }
    if(s == "ABV_OFF") {
        return ControllableFunction::ABV_OFF;
    }
    if(s == "AIRPUMP") {
        return ControllableFunction::AIRPUMP;
    }
    if(s == "BRAKE_SQUEALING") {
        return ControllableFunction::BRAKE_SQUEALING;
    }
    if(s == "GRATE_SHAKING") {
        return ControllableFunction::GRATE_SHAKING;
    }
    if(s == "GENERATOR") {
        return ControllableFunction::GENERATOR;
    }
    if(s == "OPERATION_SOUNDS") {
        return ControllableFunction::OPERATION_SOUNDS;
    }
    if(s == "SHOVELING_COAL") {
        return ControllableFunction::SHOVELING_COAL;
    }
    if(s == "DOORSCLOSING") {
        return ControllableFunction::DOORSCLOSING;
    }
    if(s == "BLOWERS") {
        return ControllableFunction::BLOWERS;
    }
    if(s == "SHOVELING_COAL_2") {
        return ControllableFunction::SHOVELING_COAL_2;
    }
    if(s == "CEILING_LIGHT") {
        return ControllableFunction::CEILING_LIGHT;
    }
    if(s == "TABLE_LIGHT_2") {
        return ControllableFunction::TABLE_LIGHT_2;
    }
    if(s == "GRATE_SHAKING_2") {
        return ControllableFunction::GRATE_SHAKING_2;
    }
    if(s == "RAIL_JOINTS") {
        return ControllableFunction::RAIL_JOINTS;
    }
    if(s == "REAR_LIGHT") {
        return ControllableFunction::REAR_LIGHT;
    }
    if(s == "FRONT_LIGHT") {
        return ControllableFunction::FRONT_LIGHT;
    }
    if(s == "COUPLING_UNCOUPLING_SOUND") {
        return ControllableFunction::COUPLING_UNCOUPLING_SOUND;
    }
    if(s == "SPEECHOUTPUT") {
        return ControllableFunction::SPEECHOUTPUT;
    }
    if(s == "CAB_LIGHT") {
        return ControllableFunction::CAB_LIGHT;
    }
    if(s == "INJECTOR") {
        return ControllableFunction::INJECTOR;
    }
    if(s == "REAR_TELEX") {
        return ControllableFunction::REAR_TELEX;
    }
    if(s == "FRONT_TELEX") {
        return ControllableFunction::FRONT_TELEX;
    }
    if(s == "REAR_PANTO") {
        return ControllableFunction::REAR_PANTO;
    }
    if(s == "FRONT_PANTO") {
        return ControllableFunction::FRONT_PANTO;
    }
    if(s == "RUNNING_GEARLIGHT") {
        return ControllableFunction::RUNNING_GEARLIGHT;
    }
    if(s == "PANTO_SOUND_UP_DOWN") {
        return ControllableFunction::PANTO_SOUND_UP_DOWN;
    }
    if(s == "STATION_ANNOUNCEMENT") {
        return ControllableFunction::STATION_ANNOUNCEMENT;
    }
    if(s == "FEED_WATER_PUMP") {
        return ControllableFunction::FEED_WATER_PUMP;
    }
    if(s == "COMPRESSED_AIR") {
        return ControllableFunction::COMPRESSED_AIR;
    }
    if(s == "RELAYSTEPS") {
        return ControllableFunction::RELAYSTEPS;
    }
    if(s == "HORN_SHORT") {
        return ControllableFunction::HORN_SHORT;
    }
    if(s == "WHISTLE_SHORT") {
        return ControllableFunction::WHISTLE_SHORT;
    }
    if(s == "STATION_ANNOUNCEMENT_2") {
        return ControllableFunction::STATION_ANNOUNCEMENT_2;
    }
    if(s == "DOORS_CLOSING") {
        return ControllableFunction::DOORS_CLOSING;
    }
    if(s == "COUPLING_UNCOUPLING_SOUND_2") {
        return ControllableFunction::COUPLING_UNCOUPLING_SOUND_2;
    }
    if(s == "BUFFERS_STRIKING") {
        return ControllableFunction::BUFFERS_STRIKING;
    }
    if(s == "SPEECHOUTPUT_2") {
        return ControllableFunction::SPEECHOUTPUT_2;
    }
    if(s == "CYLINDER_STEAM") {
        return ControllableFunction::CYLINDER_STEAM;
    }
    if(s == "COMPRESSED_AIR_2") {
        return ControllableFunction::COMPRESSED_AIR_2;
    }
    if(s == "RADIO_DIALOG") {
        return ControllableFunction::RADIO_DIALOG;
    }
    if(s == "PLATFORM_ANNOUNCEMENT") {
        return ControllableFunction::PLATFORM_ANNOUNCEMENT;
    }
    if(s == "CAB_CONVERSATION") {
        return ControllableFunction::CAB_CONVERSATION;
    }
    if(s == "SANDING") {
        return ControllableFunction::SANDING;
    }
    throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
}

inline std::string controllableFunctionEnumToString(ErrorId s) {
    switch(s) {
        case ControllableFunction::HEADLIGHTS:
            return "HEADLIGHTS";

        case ControllableFunction::INTERIOR_LIGHT:
            return "INTERIOR_LIGHT";

        case ControllableFunction::EXTERIOR_LIGHT:
            return "EXTERIOR_LIGHT";

        case ControllableFunction::LONG_DISTANCE_LIGHTS:
            return "LONG_DISTANCE_LIGHTS";

        case ControllableFunction::SOUND:
            return "SOUND";

        case ControllableFunction::PANTO:
            return "PANTO";

        case ControllableFunction::SMOKE_UNIT:
            return "SMOKE_UNIT";

        case ControllableFunction::SWITCHING_RANGE_ON:
            return "SWITCHING_RANGE_ON";

        case ControllableFunction::TELEX:
            return "TELEX";

        case ControllableFunction::HORN:
            return "HORN";

        case ControllableFunction::CONDUCTOR_WHISTLE:
            return "CONDUCTOR_WHISTLE";

        case ControllableFunction::WHISTLE_LONG:
            return "WHISTLE_LONG";

        case ControllableFunction::BELL:
            return "BELL";

        case ControllableFunction::ABV_OFF:
            return "ABV_OFF";

        case ControllableFunction::AIRPUMP:
            return "AIRPUMP";

        case ControllableFunction::BRAKE_SQUEALING:
            return "BRAKE_SQUEALING";

        case ControllableFunction::GRATE_SHAKING:
            return "GRATE_SHAKING";

        case ControllableFunction::GENERATOR:
            return "GENERATOR";

        case ControllableFunction::OPERATION_SOUNDS:
            return "OPERATION_SOUNDS";

        case ControllableFunction::SHOVELING_COAL:
            return "SHOVELING_COAL";

        case ControllableFunction::DOORSCLOSING:
            return "DOORSCLOSING";

        case ControllableFunction::BLOWERS:
            return "BLOWERS";

        case ControllableFunction::SHOVELING_COAL_2:
            return "SHOVELING_COAL_2";

        case ControllableFunction::CEILING_LIGHT:
            return "CEILING_LIGHT";

        case ControllableFunction::TABLE_LIGHT_2:
            return "TABLE_LIGHT_2";

        case ControllableFunction::GRATE_SHAKING_2:
            return "GRATE_SHAKING_";

        case ControllableFunction::RAIL_JOINTS:
            return "RAIL_JOINTS";

        case ControllableFunction::REAR_LIGHT:
            return "REAR_LIGHT";

        case ControllableFunction::FRONT_LIGHT:
            return "FRONT_LIGHT";

        case ControllableFunction::COUPLING_UNCOUPLING_SOUND:
            return "COUPLING_UNCOUPLING_SOUND";

        case ControllableFunction::SPEECHOUTPUT:
            return "SPEECHOUTPUT";

        case ControllableFunction::CAB_LIGHT:
            return "CAB_LIGHT";

        case ControllableFunction::INJECTOR:
            return "INJECTOR";

        case ControllableFunction::REAR_TELEX:
            return "REAR_TELEX";

        case ControllableFunction::FRONT_TELEX:
            return "FRONT_TELEX";

        case ControllableFunction::REAR_PANTO:
            return "REAR_PANTO";

        case ControllableFunction::FRONT_PANTO:
            return "FRONT_PANTO";

        case ControllableFunction::RUNNING_GEARLIGHT:
            return "RUNNING_GEARLIGHT";

        case ControllableFunction::PANTO_SOUND_UP_DOWN:
            return "PANTO_SOUND_UP_DOWN";

        case ControllableFunction::STATION_ANNOUNCEMENT:
            return "STATION_ANNOUNCEMENT";

        case ControllableFunction::FEED_WATER_PUMP:
            return "FEED_WATER_PUMP";

        case ControllableFunction::COMPRESSED_AIR:
            return "COMPRESSED_AIR";

        case ControllableFunction::RELAYSTEPS:
            return "RELAYSTEPS";

        case ControllableFunction::HORN_SHORT:
            return "HORN_SHORT";

        case ControllableFunction::WHISTLE_SHORT:
            return "WHISTLE_SHORT";

        case ControllableFunction::STATION_ANNOUNCEMENT_2:
            return "STATION_ANNOUNCEMENT_2";

        case ControllableFunction::DOORS_CLOSING:
            return "DOORS_CLOSING";

        case ControllableFunction::COUPLING_UNCOUPLING_SOUND_2:
            return "COUPLING_UNCOUPLING_SOUND_2";

        case ControllableFunction::BUFFERS_STRIKING:
            return "BUFFERS_STRIKING";

        case ControllableFunction::SPEECHOUTPUT_2:
            return "SPEECHOUTPUT_2";

        case ControllableFunction::CYLINDER_STEAM:
            return "CYLINDER_STEAM";

        case ControllableFunction::COMPRESSED_AIR_2:
            return "COMPRESSED_AIR_2";

        case ControllableFunction::RADIO_DIALOG:
            return "RADIO_DIALOG";

        case ControllableFunction::PLATFORM_ANNOUNCEMENT:
            return "PLATFORM_ANNOUNCEMENT";

        case ControllableFunction::CAB_CONVERSATION:
            return "CAB_CONVERSATION";

        case ControllableFunction::SANDING:
            return "SANDING";

        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}
