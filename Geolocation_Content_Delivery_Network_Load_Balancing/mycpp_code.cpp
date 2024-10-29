#include "optimisation.cpp"
#include <cstdlib>

int main(int argc, char *argv[]) {
    int param = std::atoi(argv[1]); // Convert the string argument to an integer
    double user_latitude = std::atof(argv[2]);
    double user_longitude = std::atof(argv[3]);
    int key=std::atoi(argv[4]);
    std::cout << "Received integer parameter: " << param << std::endl;
    vector<Server>server(param);

    std::ifstream file("ip_locations.csv"); // Replace "ip_locations.csv" with your file name
    std::vector<std::string> ipColumn;
    std::vector<double> latitudeColumn;
    std::vector<double> longitudeColumn;
    std::string line;
    std::string cell;

    // Indices for the columns we want to extract
    size_t ipColumnIndex = 0;    // Index of IP column
    size_t latitudeColumnIndex = 1; // Index of Latitude column
    size_t longitudeColumnIndex = 2; // Index of Longitude column

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Read the header line to get the column names
    std::getline(file, line);
    std::stringstream headerStream(line);
    size_t currentIndex = 0;

    // Parse the header to get the column names (optional)
    while (std::getline(headerStream, cell, ',')) {
        if (currentIndex == ipColumnIndex) {
            std::cout << "Extracting IP column: " << cell << std::endl;
        } else if (currentIndex == latitudeColumnIndex) {
            std::cout << "Extracting Latitude column: " << cell << std::endl;
        } else if (currentIndex == longitudeColumnIndex) {
            std::cout << "Extracting Longitude column: " << cell << std::endl;
        }
        ++currentIndex;
    }

    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        currentIndex = 0;

        // Extract the column data
        while (std::getline(lineStream, cell, ',')) {
            if (currentIndex == ipColumnIndex) {
                ipColumn.push_back(cell);
            } else if (currentIndex == latitudeColumnIndex) {
                try {
                    latitudeColumn.push_back(std::stod(cell));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid latitude value: " << cell << std::endl;
                }
            } else if (currentIndex == longitudeColumnIndex) {
                try {
                    longitudeColumn.push_back(std::stod(cell));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid longitude value: " << cell << std::endl;
                }
            }
            ++currentIndex;
        }
    }

    file.close();

    for(int i=0;i<param;i++)
    {
        server[i].ipAddress=ipColumn[i];
        server[i].latitude=latitudeColumn[i];
        server[i].longitude=longitudeColumn[i];
    }
    Server optimalServer=findOptimalServer(server,user_latitude,user_longitude);
    int value=optimalServer.get(key);
    if(value!=-1)
    {
        std::cout<<"The Value is "<<value<<std::endl;
        optimalServer.printDetails();        
    }
    else
    {
        std::cout<<"Please enter valid key"<<std::endl;
    }
    return 0;
}