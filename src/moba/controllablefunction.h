/*
 *  Project:    moba-connector
 *
 *  Copyright (C) 2022 Stefan Paproth <pappi-@gmx.de>
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
    } else if(s == "OPERATION_SOUNDS") {
        return ControllableFunction::OPERATION_SOUNDS;
    } else {
        throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}

inline std::string controllableFunctionEnumToString(ControllableFunction s) {
    switch(s) {
        case ControllableFunction::HEADLIGHTS:
            return "HEADLIGHTS";

        case ControllableFunction::OPERATION_SOUNDS:
            return "OPERATION_SOUNDS";

        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}
