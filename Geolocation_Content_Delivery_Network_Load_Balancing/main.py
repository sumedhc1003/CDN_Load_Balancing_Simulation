import requests
import random
import csv
import subprocess
def get_ip_location(ip_address):
    access_token = '9526e932f90c10'
    url = f'https://ipinfo.io/{ip_address}/json?token={access_token}'
    
    response = requests.get(url)
    
    if response.status_code == 200:
        data = response.json()
        
        # Check if 'loc' field is not None
        if data.get('loc') is not None:
            location_info = {
                'IP': data.get('ip'),
                'City': data.get('city'),
                'Region': data.get('region'),
                'Country': data.get('country'),
                'Latitude': data.get('loc').split(',')[0],
                'Longitude': data.get('loc').split(',')[1],
                'Org': data.get('org'),
                'Postal': data.get('postal')
            }
            return location_info
        else:
            return None
    else:
        return None

def generate_random_ips(n):
    available_ips = []
    while len(available_ips) < n:
        random_ip = f"{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}"
        if random_ip not in available_ips and get_ip_location(random_ip) is not None:
            available_ips.append(random_ip)
    return available_ips

def save_to_csv(data, filename='ip_locations.csv'):
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['IP', 'Latitude', 'Longitude'])
        for entry in data:
            writer.writerow([entry['IP'], entry['Latitude'], entry['Longitude']])

n = int(input("Enter number of servers: "))
user_ip=input("Enter your IP: ")
ip_addresses = generate_random_ips(n)
user_latitude=get_ip_location(user_ip)['Latitude']
user_longitude=get_ip_location(user_ip)['Longitude']
key=int(input("Enter key: "))
location_data = []
for ip in ip_addresses:
    location_info = get_ip_location(ip)
    if location_info:
        location_data.append(location_info)
        print(location_info)
    
save_to_csv(location_data)

integer_param = n  # Example integer value

# Run the C++ executable with the integer parameter
print("Running C++ code...")
result = subprocess.run(['./mycpp_program', str(n), str(user_latitude), str(user_longitude), str(key)], capture_output=True, text=True)

# Print the output from the C++ program
print("C++ program output:")
print(result.stdout)