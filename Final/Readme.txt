
Indoor Navigation system: 
The current system for indoor navigation is carried out by high cost sensors and expensive
 technology.Hence commercialization of personal robots is an untapped market right now. 
We propose an easy to use IOT based indoor navigation robot that can arrive at the location a user intends it to, in an indoor
area. The user inputs a floorplan of the indoor area which assists the bot to navigate. 

dustyfinal.java - Creates grid for the floorplan image uploaded and transfers it to
 Rpi through sockets(Server side script).

Clientside.java - Client side code for dustyfinal.java on Rpi 

dustyfinal1.java - Receives destination input from the user through image
 and transfers it to Rpi through sockets(Server side script).

Clientside1.java - Client side code for dustyfinal1.java on Rpi

NavigationRpi- C program to navigate to the given destination in raspberry pi implementing 
A* algorithm to find optimum path. 

cognitivewastedet.py - Cognitive application to test the custom classifier trained to 
identify dry, wet and hazardous waste. It can be used with navigation for waste collection and 
seggregation in hospitals. 

 