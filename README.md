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

![](/screenshots/maps/maps_copmap.png)
![](/screenshots/maps/maps_cobmap_result.png)

If the path is only one link, then all ants may proceed in the same turn:

![](/screenshots/maps/maps_simple_onestep.png)

If multiple paths are found, ants will walk separate paths until it is inefficient to do so:

![](/screenshots/maps/maps_simple_diamond.png)

If errors are encountered in parsing and validation, the program returns an error:

![](/screenshots/maps/maps_error_illegal.png)
![](/screenshots/maps/maps_error_overflow.png)

Same thing if there is no path from the start room to the end room:

![](/screenshots/maps/maps_error_noroute.png)

## Project Bonuses

Providing the user with flags for how to run the program was not required but I found it prudent to illustrate the efficacy of the program. Technically the raw output was a requirement, and thusly my standard output that includes error notification, includes path count, path illucidation, and turn count would be a cherry. The One Path option is there to illustrate the difference in efficiency between multiple paths and one path:

![](/screenshots/maps/mmkr_multipath.png)
![](/screenshots/maps/mmkr_multipath_paths.png)
![](/screenshots/maps/mmkr_multipath_turns.png)

###vs

![](/screenshots/maps/mmkr_singlepath.png)
![](/screenshots/maps/mmkr_singlepath_path.png)
![](/screenshots/maps/mmkr_singlepath_turns.png)

The Ignore Coordinates option is there for farm creators who may have mistakenly created rooms occupying the same space. The program will still be able to interpret the program as intended.

####Speed Bonus

In testing my Lem-in project against those others I could find on line, mine is effectively 2 to 150x faster for solving a single path amongst 10,000 rooms across which to march 1,000 ants. I attribute this to the use of binary search trees to validate input and verify no duplicate rooms.

My (kmurray's) Lem-in:
![](/screenshots/time/time_lemin_kmurray.png) 

Other Users:
***
![](/screenshots/time/time_lemin_kdavis.png)
![](/screenshots/time/time_lemin_raphael.png)
![](/screenshots/time/time_lemin_barong.png)
![](/screenshots/time/time_lemin_nsampre.png)
![](/screenshots/time/time_lemin_wouterbeets.png)
![](/screenshots/time/time_lemin_rschramm.png)

*** It should be noted that the comparison for User1's lem-in is not strictly valid, considering it uses Dijkstra's algorithm and therefore the number of rooms searched and traversed may be different. It also has a more verbose output than my own.

## Project Improvements

The attack algorithms can always be improved. An optimal strategy, which I feel was unnecessary to fully complete the project, would include an algorithm that responds to the deviation of the opponent's sprawl to effectively figure out which direction the opponent is trying to head.

An obvious improvement would be to add a Makefile command that would allow me to compile with or without my heat map. It would be relatively simple—the only challenge would be norme compliance. As it is, I have to go into my code and manually add a line to print out the heat map array, which feels ugly.
