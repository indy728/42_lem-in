# 42_lem-in
## Pathfinding Function in C

#### Usage: ./lem-in [-1rc] < path-to-file
    - 1: One Path: Marches all ants down the first and shortest path.
    - r: Raw: Simple output as per requirements of the assignment.
    - c: Ignore Coordinates: In this program's vaildation process, duplicate coordinates naturally reset the name of the  original room of same coordinates. Ignore Coordinates will create new rooms regardless of coordinates.

The purpose of this project is to write a program that validates input and effectively implements a pathfinding algorithm to solve a problem efficiently.

The premise of Lem-in is that you are working with an ant farm and a given number of ants. The farm is comprised of rooms and tunnels (links), with one room designated as start and another uniquely designated as finish. You are to "march" all of the ants from the starting room to the ending room. All the ants are present in the starting room and until they reach the end room, no two ants can be in the same room on the same turn.

## The Project

This project can be dissected into distinct parts:

A) Parsing. You are given guidelines for the formatting of the ant farm as read in via STDIN. It is up to you to interpret the guidelines and effectively validate inputs in accordance with your interpretations. The largest albeit least interesting part of this project is parsing and validating input. While this is occurring, the farm information is being stored in an appropriate object and (hopefully) data structure.

B) Pathfinding algorithm. It is up to you to decide how to implement an effective pathfinding algorithm and which. For the literal "shortest-path", using <b>Dijkstra's algorithm</b> to determine distance between coordinates seems prudent. My argument, however, is that logically to have the shortest distance traveled by ants, they would all take the same first path discovered. I instead opted for implementing a <b>Breadth-First Search</b>, and continuing to look for paths until out of unique paths. In this way, my ants effect a "fewest turns" march. To be sure they did not march down very long paths that would have proven inefficient, I wrote a start-decision algorithm to ensure efficacy.
 
#### Autolemin Usage: sh autolemin.sh

To test multiple farms consecutively without returning to the command line, I've included <a href="https://github.com/nsampre">nsampre</a>'s bash script, modified to more effectively add maps and test all maps based on repo theme:

![](/screenshots/autolemin.png)

An example of a simple map solved:

![](/screenshots/maps/maps_cobmap.png)
![](/screenshots/maps/maps_cobmap_result.png)

If the path is only one link, then all ants may proceed in the same turn:

![](/screenshots/maps/maps_onestep.png)

If multiple paths are found, ants will walk separate paths until it is inefficient to do so:

![](/screenshots/maps/maps_diamond.png)

If errors are encountered in parsing and validation, the program returns an error:

![](/screenshots/maps/maps_error_illegal.png)
![](/screenshots/maps/maps_error_overflow.png)

Same thing if there is no path from the start room to the end room:

![](/screenshots/maps/maps_error_noroute.png)

## Project Bonuses

In addition to the efficacy of my attack algorithms, I also included a graphic visualizer for the game. At each turn, it outputs the current game board, with white spaces representing my own sprawl, black spaces representing my opponent, and a green, yellow and red heat map to indicate the attack value of different parts of the game board. 

![](/screenshots/heat_map0.png)
![](/screenshots/heat_map1.png)

This heat map is the best indication of the dynamic switching my program does on certain cues to prioritize different attack strategies.

![](/screenshots/heat_map2.png)
![](/screenshots/heat_map3.png)
![](/screenshots/heat_map4.png)
![](/screenshots/heat_map5.png)
![](/screenshots/heat_map6.png)
![](/screenshots/heat_map7.png)
![](/screenshots/heat_map8.png)
![](/screenshots/heat_map9.png)

## Project Improvements

The attack algorithms can always be improved. An optimal strategy, which I feel was unnecessary to fully complete the project, would include an algorithm that responds to the deviation of the opponent's sprawl to effectively figure out which direction the opponent is trying to head.

An obvious improvement would be to add a Makefile command that would allow me to compile with or without my heat map. It would be relatively simple—the only challenge would be norme compliance. As it is, I have to go into my code and manually add a line to print out the heat map array, which feels ugly.
