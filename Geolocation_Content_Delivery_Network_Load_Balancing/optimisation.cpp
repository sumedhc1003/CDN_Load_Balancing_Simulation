#include "distance.cpp"
double calculateScore(double userLat, double userLon,double server_lat, double server_lon,int numRequests)  {
        double distance = haversineDistance(userLat, userLon, server_lat, server_lon);
        // Using a simple formula: score = distance + (numRequests / 1000.0)
        // Modify the weight as needed
        return distance + (numRequests / 1000.0);
    }
Server findOptimalServer(const std::vector<Server>& servers, double userLat, double userLon) {
    double bestScore = std::numeric_limits<double>::max();
    const Server* optimalServer = nullptr;

    for (const auto& server : servers) {
        double score =calculateScore(userLat, userLon, server.latitude, server.longitude, server.numRequests);
        if (score < bestScore) {
            bestScore = score;
            optimalServer = &server;
        }
    }

    if (optimalServer != nullptr) {
        return *optimalServer;
    } else {
        throw std::runtime_error("No optimal server found.");
    }
}