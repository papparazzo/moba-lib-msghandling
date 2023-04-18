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

enum class Function {
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
    DOORS_CLOSING               = 28,  // Türenschließen Wie 156…
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
    DOORS_CLOSING_2             = 156, // Türenschließen Wie 28
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

inline Function stringToControllableFunctionEnum(const std::string &s) {
    if(s == "HEADLIGHTS") {
        return Function::HEADLIGHTS;
    }
    if(s == "INTERIOR_LIGHT") {
        return Function::INTERIOR_LIGHT;
    }
    if(s == "EXTERIOR_LIGHT") {
        return Function::EXTERIOR_LIGHT;
    }
    if(s == "LONG_DISTANCE_LIGHTS") {
        return Function::LONG_DISTANCE_LIGHTS;
    }
    if(s == "SOUND") {
        return Function::SOUND;
    }
    if(s == "PANTO") {
        return Function::PANTO;
    }
    if(s == "SMOKE_UNIT") {
        return Function::SMOKE_UNIT;
    }
    if(s == "SWITCHING_RANGE_ON") {
        return Function::SWITCHING_RANGE_ON;
    }
    if(s == "TELEX") {
        return Function::TELEX;
    }
    if(s == "HORN") {
        return Function::HORN;
    }
    if(s == "CONDUCTOR_WHISTLE") {
        return Function::CONDUCTOR_WHISTLE;
    }
    if(s == "WHISTLE_LONG") {
        return Function::WHISTLE_LONG;
    }
    if(s == "BELL") {
        return Function::BELL;
    }
    if(s == "ABV_OFF") {
        return Function::ABV_OFF;
    }
    if(s == "AIRPUMP") {
        return Function::AIRPUMP;
    }
    if(s == "BRAKE_SQUEALING") {
        return Function::BRAKE_SQUEALING;
    }
    if(s == "GRATE_SHAKING") {
        return Function::GRATE_SHAKING;
    }
    if(s == "GENERATOR") {
        return Function::GENERATOR;
    }
    if(s == "OPERATION_SOUNDS") {
        return Function::OPERATION_SOUNDS;
    }
    if(s == "SHOVELING_COAL") {
        return Function::SHOVELING_COAL;
    }
    if(s == "DOORSCLOSING") {
        return Function::DOORS_CLOSING;
    }
    if(s == "BLOWERS") {
        return Function::BLOWERS;
    }
    if(s == "SHOVELING_COAL_2") {
        return Function::SHOVELING_COAL_2;
    }
    if(s == "CEILING_LIGHT") {
        return Function::CEILING_LIGHT;
    }
    if(s == "TABLE_LIGHT_2") {
        return Function::TABLE_LIGHT_2;
    }
    if(s == "GRATE_SHAKING_2") {
        return Function::GRATE_SHAKING_2;
    }
    if(s == "RAIL_JOINTS") {
        return Function::RAIL_JOINTS;
    }
    if(s == "REAR_LIGHT") {
        return Function::REAR_LIGHT;
    }
    if(s == "FRONT_LIGHT") {
        return Function::FRONT_LIGHT;
    }
    if(s == "COUPLING_UNCOUPLING_SOUND") {
        return Function::COUPLING_UNCOUPLING_SOUND;
    }
    if(s == "SPEECHOUTPUT") {
        return Function::SPEECHOUTPUT;
    }
    if(s == "CAB_LIGHT") {
        return Function::CAB_LIGHT;
    }
    if(s == "INJECTOR") {
        return Function::INJECTOR;
    }
    if(s == "REAR_TELEX") {
        return Function::REAR_TELEX;
    }
    if(s == "FRONT_TELEX") {
        return Function::FRONT_TELEX;
    }
    if(s == "REAR_PANTO") {
        return Function::REAR_PANTO;
    }
    if(s == "FRONT_PANTO") {
        return Function::FRONT_PANTO;
    }
    if(s == "RUNNING_GEARLIGHT") {
        return Function::RUNNING_GEARLIGHT;
    }
    if(s == "PANTO_SOUND_UP_DOWN") {
        return Function::PANTO_SOUND_UP_DOWN;
    }
    if(s == "STATION_ANNOUNCEMENT") {
        return Function::STATION_ANNOUNCEMENT;
    }
    if(s == "FEED_WATER_PUMP") {
        return Function::FEED_WATER_PUMP;
    }
    if(s == "COMPRESSED_AIR") {
        return Function::COMPRESSED_AIR;
    }
    if(s == "RELAYSTEPS") {
        return Function::RELAYSTEPS;
    }
    if(s == "HORN_SHORT") {
        return Function::HORN_SHORT;
    }
    if(s == "WHISTLE_SHORT") {
        return Function::WHISTLE_SHORT;
    }
    if(s == "STATION_ANNOUNCEMENT_2") {
        return Function::STATION_ANNOUNCEMENT_2;
    }
    if(s == "DOORS_CLOSING") {
        return Function::DOORS_CLOSING_2;
    }
    if(s == "COUPLING_UNCOUPLING_SOUND_2") {
        return Function::COUPLING_UNCOUPLING_SOUND_2;
    }
    if(s == "BUFFERS_STRIKING") {
        return Function::BUFFERS_STRIKING;
    }
    if(s == "SPEECHOUTPUT_2") {
        return Function::SPEECHOUTPUT_2;
    }
    if(s == "CYLINDER_STEAM") {
        return Function::CYLINDER_STEAM;
    }
    if(s == "COMPRESSED_AIR_2") {
        return Function::COMPRESSED_AIR_2;
    }
    if(s == "RADIO_DIALOG") {
        return Function::RADIO_DIALOG;
    }
    if(s == "PLATFORM_ANNOUNCEMENT") {
        return Function::PLATFORM_ANNOUNCEMENT;
    }
    if(s == "CAB_CONVERSATION") {
        return Function::CAB_CONVERSATION;
    }
    if(s == "SANDING") {
        return Function::SANDING;
    }
    throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
}

inline std::string controllableFunctionEnumToString(Function s) {
    switch(s) {
        case Function::HEADLIGHTS:
            return "HEADLIGHTS";

        case Function::INTERIOR_LIGHT:
            return "INTERIOR_LIGHT";

        case Function::EXTERIOR_LIGHT:
            return "EXTERIOR_LIGHT";

        case Function::LONG_DISTANCE_LIGHTS:
            return "LONG_DISTANCE_LIGHTS";

        case Function::SOUND:
            return "SOUND";

        case Function::PANTO:
            return "PANTO";

        case Function::SMOKE_UNIT:
            return "SMOKE_UNIT";

        case Function::SWITCHING_RANGE_ON:
            return "SWITCHING_RANGE_ON";

        case Function::TELEX:
            return "TELEX";

        case Function::HORN:
            return "HORN";

        case Function::CONDUCTOR_WHISTLE:
            return "CONDUCTOR_WHISTLE";

        case Function::WHISTLE_LONG:
            return "WHISTLE_LONG";

        case Function::BELL:
            return "BELL";

        case Function::ABV_OFF:
            return "ABV_OFF";

        case Function::AIRPUMP:
            return "AIRPUMP";

        case Function::BRAKE_SQUEALING:
            return "BRAKE_SQUEALING";

        case Function::GRATE_SHAKING:
            return "GRATE_SHAKING";

        case Function::GENERATOR:
            return "GENERATOR";

        case Function::OPERATION_SOUNDS:
            return "OPERATION_SOUNDS";

        case Function::SHOVELING_COAL:
            return "SHOVELING_COAL";

        case Function::DOORS_CLOSING:
            return "DOORSCLOSING";

        case Function::BLOWERS:
            return "BLOWERS";

        case Function::SHOVELING_COAL_2:
            return "SHOVELING_COAL_2";

        case Function::CEILING_LIGHT:
            return "CEILING_LIGHT";

        case Function::TABLE_LIGHT_2:
            return "TABLE_LIGHT_2";

        case Function::GRATE_SHAKING_2:
            return "GRATE_SHAKING_2";

        case Function::RAIL_JOINTS:
            return "RAIL_JOINTS";

        case Function::REAR_LIGHT:
            return "REAR_LIGHT";

        case Function::FRONT_LIGHT:
            return "FRONT_LIGHT";

        case Function::COUPLING_UNCOUPLING_SOUND:
            return "COUPLING_UNCOUPLING_SOUND";

        case Function::SPEECHOUTPUT:
            return "SPEECHOUTPUT";

        case Function::CAB_LIGHT:
            return "CAB_LIGHT";

        case Function::INJECTOR:
            return "INJECTOR";

        case Function::REAR_TELEX:
            return "REAR_TELEX";

        case Function::FRONT_TELEX:
            return "FRONT_TELEX";

        case Function::REAR_PANTO:
            return "REAR_PANTO";

        case Function::FRONT_PANTO:
            return "FRONT_PANTO";

        case Function::RUNNING_GEARLIGHT:
            return "RUNNING_GEARLIGHT";

        case Function::PANTO_SOUND_UP_DOWN:
            return "PANTO_SOUND_UP_DOWN";

        case Function::STATION_ANNOUNCEMENT:
            return "STATION_ANNOUNCEMENT";

        case Function::FEED_WATER_PUMP:
            return "FEED_WATER_PUMP";

        case Function::COMPRESSED_AIR:
            return "COMPRESSED_AIR";

        case Function::RELAYSTEPS:
            return "RELAYSTEPS";

        case Function::HORN_SHORT:
            return "HORN_SHORT";

        case Function::WHISTLE_SHORT:
            return "WHISTLE_SHORT";

        case Function::STATION_ANNOUNCEMENT_2:
            return "STATION_ANNOUNCEMENT_2";

        case Function::DOORS_CLOSING_2:
            return "DOORS_CLOSING";

        case Function::COUPLING_UNCOUPLING_SOUND_2:
            return "COUPLING_UNCOUPLING_SOUND_2";

        case Function::BUFFERS_STRIKING:
            return "BUFFERS_STRIKING";

        case Function::SPEECHOUTPUT_2:
            return "SPEECHOUTPUT_2";

        case Function::CYLINDER_STEAM:
            return "CYLINDER_STEAM";

        case Function::COMPRESSED_AIR_2:
            return "COMPRESSED_AIR_2";

        case Function::RADIO_DIALOG:
            return "RADIO_DIALOG";

        case Function::PLATFORM_ANNOUNCEMENT:
            return "PLATFORM_ANNOUNCEMENT";

        case Function::CAB_CONVERSATION:
            return "CAB_CONVERSATION";

        case Function::SANDING:
            return "SANDING";

        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}

inline Function getAlternativeFunction(Function s) {
    switch(s) {
/*
        case Function::HORN:
            return "HORN";

        case Function::WHISTLE_LONG:
            return "WHISTLE_LONG";

        case Function::BELL:
            return "BELL";

        case Function::CONDUCTOR_WHISTLE:
            return Function::DOORSCLOSING;

        case Function::SHOVELING_COAL:            
            return Function::SHOVELING_COAL_2;
            
        case Function::SHOVELING_COAL_2:
            return Function::SHOVELING_COAL;

        case Function::CEILING_LIGHT:
            return "CEILING_LIGHT";

        case Function::TABLE_LIGHT_2:
            return "TABLE_LIGHT_2";

        case Function::GRATE_SHAKING_2:
            return "GRATE_SHAKING_2";

        case Function::RAIL_JOINTS:
            return "RAIL_JOINTS";

        case Function::REAR_LIGHT:
            return "REAR_LIGHT";

        case Function::FRONT_LIGHT:
            return "FRONT_LIGHT";

        case Function::COUPLING_UNCOUPLING_SOUND:
            return "COUPLING_UNCOUPLING_SOUND";

        case Function::SPEECHOUTPUT:
            return "SPEECHOUTPUT";

        case Function::CAB_LIGHT:
            return "CAB_LIGHT";

        case Function::INJECTOR:
            return "INJECTOR";

        case Function::REAR_TELEX:
            return "REAR_TELEX";

        case Function::FRONT_TELEX:
            return "FRONT_TELEX";

        case Function::REAR_PANTO:
            return "REAR_PANTO";

        case Function::FRONT_PANTO:
            return Function::PANTO_SOUND_UP_DOWN;

        case Function::RUNNING_GEARLIGHT:
            return "RUNNING_GEARLIGHT";

        case Function::PANTO_SOUND_UP_DOWN:
            return "PANTO_SOUND_UP_DOWN";

        case Function::STATION_ANNOUNCEMENT:
            return "STATION_ANNOUNCEMENT";

        case Function::FEED_WATER_PUMP:
            return "FEED_WATER_PUMP";

        case Function::COMPRESSED_AIR:
            return "COMPRESSED_AIR";

        case Function::RELAYSTEPS:
            return "RELAYSTEPS";

        case Function::HORN_SHORT:
            return "HORN_SHORT";

        case Function::WHISTLE_SHORT:
            return "WHISTLE_SHORT";

        case Function::STATION_ANNOUNCEMENT_2:
            return "STATION_ANNOUNCEMENT_2";

        case Function::DOORS_CLOSING:
            return Function::CONDUCTOR_WHISTLE;

        case Function::COUPLING_UNCOUPLING_SOUND_2:
            return "COUPLING_UNCOUPLING_SOUND_2";

        case Function::BUFFERS_STRIKING:
            return "BUFFERS_STRIKING";

        case Function::SPEECHOUTPUT_2:
            return "SPEECHOUTPUT_2";

        case Function::CYLINDER_STEAM:
            return "CYLINDER_STEAM";

        case Function::COMPRESSED_AIR_2:
            return "COMPRESSED_AIR_2";

        case Function::RADIO_DIALOG:
            return "RADIO_DIALOG";

        case Function::PLATFORM_ANNOUNCEMENT:
            return "PLATFORM_ANNOUNCEMENT";

        case Function::CAB_CONVERSATION:
            return "CAB_CONVERSATION";

        case Function::SANDING:
            return "SANDING";
            */
        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}

inline Function getFollowupFunction(Function f) {
    switch(f) {
        case Function::CONDUCTOR_WHISTLE:
            return Function::DOORS_CLOSING;
        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}
