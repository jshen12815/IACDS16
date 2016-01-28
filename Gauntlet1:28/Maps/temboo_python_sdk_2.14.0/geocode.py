from temboo.Library.Google.Geocoding import GeocodeByAddress
from temboo.core.session import TembooSession
import csv


with open('the-counted.csv','r') as csvinput:
    with open('the-counted-longLat.csv','w') as csvoutput:
    	writer = csv.writer(csvoutput)
    	reader = csv.reader(csvinput)
    	session = TembooSession("golanlevin", "myFirstApp", "8b6465211573423d9e330d2a0c053c3d")
    	geocodeByAddressChoreo = GeocodeByAddress(session)
    	all = []
    	row = reader.next()
    	row.append('Latitude')
    	row.append('Longitude')
    	writer.writerow(row)

        for row in reader:
            print(row[8])
            geocodeByAddressInputs = geocodeByAddressChoreo.new_input_set()
            geocodeByAddressInputs.set_Address(row[8] + ' ' + row[9] + ' ' + row[10])
            geocodeByAddressResults = geocodeByAddressChoreo.execute_with_results(geocodeByAddressInputs)
            print(geocodeByAddressResults.get_Latitude())
            print(geocodeByAddressResults.get_Longitude())
            row.append(geocodeByAddressResults.get_Latitude())
            row.append(geocodeByAddressResults.get_Longitude())
            all.append(row)
            writer.writerow(row)

        print('done')

    #	for row in reader:
   # 	        	    row.append(geocodeByAddressResults.get_Latitude())
   # 	    row.append(geocodeByAddressResults.get_Longitude())
    #	    all.append(row)
   # 	    writer.writerow(row)




    	#print(row[8])


# Create a session with your Temboo account details
#session = TembooSession("jshen1", "myFirstApp", "RmedKJ13aIf3wZJqwXS8EdNBmgU098Gl")

# Instantiate the Choreo
#geocodeByAddressChoreo = GeocodeByAddress(session)

# Get an InputSet object for the Choreo
#geocodeByAddressInputs = geocodeByAddressChoreo.new_input_set()

# Set the Choreo inputs
#geocodeByAddressInputs.set_Address("2838 Gainsborough Dr. San Marino, CA")

#geocodeByAddressInputs.set_Address("5000 Forbes Ave. Pittsburgh, PA")

# Execute the Choreo
#geocodeByAddressResults = geocodeByAddressChoreo.execute_with_results(geocodeByAddressInputs)

 #Print the Choreo outputs
#print("Latitude: " + geocodeByAddressResults.get_Latitude())
#print("Longitude: " + geocodeByAddressResults.get_Longitude())
#print("Response: " + geocodeByAddressResults.get_Response())