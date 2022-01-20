//
// Created by john on 20/01/22.
//

#ifndef STCPREDETRANSPORTES_POSITION_H
#define STCPREDETRANSPORTES_POSITION_H


#include <cmath>

class Position {
private:
    const double PI = 3.141592653589793238463;
    double latitude, longitude;

public:
    Position(double latitude, double longitude): longitude(longitude), latitude(latitude){};

    double getDistance(Position p1) const;
};

double Position::getDistance(Position p1) const {
    auto earthRadiusKM = 6371;

    auto dLat = (this->latitude-p1.latitude) * PI /180;
    auto dLon = (this->longitude-p1.longitude) * PI /180;

    auto lat1 = this->latitude * PI / 180;
    auto lat2 = p1.latitude * PI / 180;

    auto a = sin(dLat/2) * sin(dLat/2) +
            sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
    auto c = 2 * atan2(sqrt(a), sqrt(1-a));
    return earthRadiusKM * c;
}

#endif //STCPREDETRANSPORTES_POSITION_H