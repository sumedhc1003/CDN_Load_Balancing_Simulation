
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <windows.h> // for transmission time (sleep)

using namespace std;

unordered_map<int, string> OriginServerContent = {
    {1, "Content 1"},
    {2, "Content 2"},
    {3, "Content 3"},
    {4, "Content 4"},
    {5, "Content 5"},
    {6, "Content 6"},
    {7, "Content 7"},
    {8, "Content 8"},
    {9, "Content 9"},
};

class LRUCache { // 1 cache object for each server
public:
    int capacity = 5; // Cache capacity of each server
    list<vector<string>> cache; // This doubly linked list stores content codes in LRU fashion
    //This linked list's vectors are in the format: {content code, content, transmission time}
    // unordered_map<int, int> map; // Unordered map which maps Content codes to transmission time

    void cacheHit(auto cacheit) {
        cache.erase(cacheit);
        cache.push_front(*cacheit);
        cout << "Content found in CDN Server. Now fetching content..." << endl;
        // int transmissionTime = map[contentCode];
        // Sleep(transmissionTime * 1000); // Sleep for transmission time
        cout << "Content fetched successfully from CDN Server." << endl;
    }

    void cacheMiss(int contentCode) {
        cout << "Content NOT found in CDN Server. Fetching from Origin Server..." << endl;
        if (cache.size() == capacity) {
            cache.pop_back();
        }
        vector<string> contentInfo = {to_string(contentCode), OriginServerContent[contentCode], to_string(20)};
        cache.push_front(contentInfo);
        // int origintax = 10; // This is the time the CDN Server takes to fetch content from origin server
        // int transmissionTime = origintax + map[contentCode];
        //Sleep(transmissionTime * 1000);
        cout << "Content fetched and cached successfully from Origin Server" << endl;
    }
    void fetch(int contentCode) {
        cout << "Trying to get content from CDN Server..." << endl;
        for (auto cacheit = cache.begin(); cacheit != cache.end(); ++cacheit) {
            if (contentCode == stoi((*cacheit)[0])){
                cacheHit(cacheit);
                return;
            }
        }
        cacheMiss(contentCode);
        // for (int val : cache){
        //     if(val == contentCode){
        //         cacheHit(contentCode);
        //     }
        // }
        // cacheMiss(contentCode);
    }
};

class Server {
public:
    int ipAddress;        // IP Address stored as an int
    double latitude;      // Latitude of the server
    double longitude;     // Longitude of the server
    int numRequests;      // Number of requests processed by the server
    LRUCache lrucache;

public:
    // Constructor to initialize the Server object
    Server(int ip, double lat, double lon) : ipAddress(ip), latitude(lat), longitude(lon), numRequests(0) {}

    // Method to display server information
    void displayInfo() {
        cout << "IP Address: " << ipAddress << endl;
        cout << "Latitude: " << latitude << endl;
        cout << "Longitude: " << longitude << endl;
        cout << "Number of Requests: " << numRequests << endl;
        cout << "Cached content is: ";
        for (auto cacheit = lrucache.cache.begin(); cacheit != lrucache.cache.end(); ++cacheit) {
            cout<<(*cacheit)[1]<<" ";
        }
        // for (int contentCode : lrucache.cache) {
        //     cout << contentCode << " ";
        // }
        cout << endl;
    }

    // Method to update the number of requests
    void incrementRequests() {
        numRequests++;
    }
};
