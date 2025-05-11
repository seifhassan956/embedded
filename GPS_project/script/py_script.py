import serial
import os
import folium
import time

# python -m serial.tools.list_ports

script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, 'embedded_coordinates')
coordinates = []
mymap = None
map_path = os.path.join(script_dir, 'map.html')

ZOOM = 15
SAVE_EVERY = 20

# Clear the file
if os.path.exists(file_path):
    with open(file_path, 'r+') as f:
        f.truncate(0)

ser = serial.Serial('COM5', baudrate= 9600)


while True:
    try:
        data = ser.readline()
        str_data = str(data , 'UTF-8')
        print(str_data)

        with open(file_path , 'a', encoding='utf-8') as f:
            f.write(str_data)

        if str_data.startswith('(') and str_data.endswith(')'):
            # Remove parentheses and split by comma
            coord_str = str_data[1:-1]
            lat, lon = coord_str.split(',')
            lat = float(lat.strip())
            lon = float(lon.strip())

            # Append coordinates to the list
            coordinates.append((lat, lon))

            # Print the data and append to the file
            print(f"Latitude: {lat}, Longitude: {lon}")

            if mymap is None:
                mymap = folium.Map(location=(lat, lon), zoom_start = ZOOM)

            # Add latest marker
            folium.Marker([lat, lon], popup=f"Lat: {lat}, Lon: {lon}").add_to(mymap)

            # Add a PolyLine to show the path
            if len(coordinates) >= 2:
                folium.PolyLine(locations=coordinates, color='blue').add_to(mymap)

            # Save map every 5 points
            if len(coordinates) % SAVE_EVERY:
                mymap.save(map_path)
                print(f"Map updated with {len(coordinates)} points at {map_path}")

    except:
        print("end...")
        break

# def test_script():
#     # Read coordinates from file
#     coordinates = []
#     mymap = None

#     with open(file_path, 'r', encoding='utf-8') as f:
#         for line in f:
#             line = line.strip()

#             if line.startswith('(') and line.endswith(')'):
#                 # Remove parentheses and split by comma
#                 coord_str = line[1:-1]
#                 lat, lon = coord_str.split(',')
#                 lat = float(lat.strip())
#                 lon = float(lon.strip())

#                 # Append coordinates to the list
#                 coordinates.append((lat, lon))

#                 # Print the data and append to the file
#                 print(f"Latitude: {lat}, Longitude: {lon}")


#             if mymap is None:
#                 mymap = folium.Map(location=(lat, lon), zoom_start= ZOOM)

#             # Add latest marker
#             folium.Marker([lat, lon], popup=f"Lat: {lat}, Lon: {lon}").add_to(mymap)

#             # Add a PolyLine to show the path
#             if len(coordinates) >= 2:
#                 folium.PolyLine(locations=coordinates, color='blue').add_to(mymap)

#             # Save map every 5 points
#             if len(coordinates) % SAVE_EVERY:
#                 mymap.save(map_path)
#                 print(f"Map updated with {len(coordinates)} points at {map_path}")

#             time.sleep(1)

# test_script()