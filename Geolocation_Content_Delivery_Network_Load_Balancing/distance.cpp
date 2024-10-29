#include "server.cpp"
const double EARTH_RADIUS_KM = 6371.0; // Earth's radius in kilometers

// Function to convert degrees to radians
double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

// Function to calculate the distance between two points on Earth
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    // Convert latitude and longitude from degrees to radians
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    // Differences in coordinates
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    // Haversine formula
    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1) * std::cos(lat2) * 
               std::sin(dLon / 2) * std::sin(dLon / 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    // Distance in kilometers
    double distance = EARTH_RADIUS_KM * c;
    return distance;
}