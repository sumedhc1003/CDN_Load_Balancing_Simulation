// main.cpp
#include "Trie.h"
int main() {
    // Create Servers
    Server server1(1, 37.7749, -122.4194); // Example: San Francisco
    Server server2(2, 40.7128, -74.0060);  // Example: New York
    Server server3(3, 51.5074, -0.1278);   // Example: London

    // server1.cache.cache = {1, 5, 6};
    // server2.cache.cache = {2, 8, 7};
    // server3.cache.cache = {3, 9, 4};

    // Display server info
    cout << "\nServer Information:" << endl;
    server1.displayInfo();
    cout << endl;
    server2.displayInfo();
    cout << endl;
    server3.displayInfo();

    // Create Trie for path-based routing
    Trie trie;
    trie.insert("/images/", &server1);
    trie.insert("/videos/", &server2);
    trie.insert("/static/", &server3);


    // // Simulate requests
    // string paths[] = {"/images/photo.jpg", "/videos/movie.mp4", "/static/js/app.js"};
    // int contentCodes[] = {1, 2, 3};
    unordered_map<string, int> pathToContentCode = {
        {"/images/first.jpg", 1},
        {"/images/second.jpg", 2},
        {"/images/third.jpg", 3},
        {"/videos/first.mp4", 4},
        {"/videos/second.mp4", 5},
        {"/videos/third.mp4", 6},
        {"/static/firstapp.js", 7},
        {"/static/secondapp.js", 8},
        {"/static/thirdapp.js", 9}
    };

    for (auto pair : pathToContentCode) {
        cout << "\nRequesting path: " << pair.first << endl;

        // Path-based routing to find the appropriate CDN endpoint
        Server* cdnEndpoint = trie.search(pair.first);
        if (cdnEndpoint != nullptr) {
            cout << "CDN endpoint for " << pair.first << ": " << cdnEndpoint->ipAddress << endl;
        } else {
            cout << "No CDN found for " << pair.first << endl;
            continue;
        }
        // Simulate fetching content from cache
        cout << "\nFetching content with code: " << pathToContentCode[pair.first] << endl;
        cdnEndpoint->lrucache.fetch(pathToContentCode[pair.first]);
        server1.displayInfo();
        server2.displayInfo();
        server3.displayInfo();

    }

    return 0;
}
