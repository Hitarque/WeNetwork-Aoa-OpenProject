# WeNetwork Aoa OpenProject
This project is a basic system of indoor geolocation by bluetooth AoA. It is based on the use of silicon labs locators (beacons) and assets to search.
On this project the Aoa_locator system is a test code proposed by SiliconLabs to provide a return of angle of arrival calculations through the Ethernet/USB (NCP) and to send it to a Mqtt broker.

We retrieve the data via the broker to perform our calculations, the data is then smoothed over ~100 values, then the intersection of lines are calculated to calculate the position of the asset.

# How is the project going?
The system works quite well in an empty space, or one that is not very full. Tracking of 1 asset has been done, but no testing with multy assets has been done.
Tests in industrial environments have been done but have not been conclusive.
The potential reasons for this problem are the following:
- Metal mesh,
- ESD zone,
- High voltage lines
- Too much distance between locators


# Licenses
This project is licensed under an open source license by We Network, it uses parts of Silicon labs open source code that are not intended for commercial use.
Please ask before using it for commercial purpose!

