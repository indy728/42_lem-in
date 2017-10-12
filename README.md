# 42_lem-in
## Pathfinding Algo in C

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

![autolemin](/screenshots/autolemin)

![vm_output](/screenshots/filler_vm_output.png?raw=true "vm_output")

A piece may look something like this:

![](/screenshots/simple_piece.png)

The asterisks represent the body of the piece. Placement rules only apply to the asterisked grid units. The empty (".") spaces are ignored. However, the coordinates of the placement correspont to the top left corner of the piece, whethe it is a filled space or an empty space. Negative integers are valid placement coordinates so long as is still allows all filled spaces on the piece to be placed according to the game rules. Here's another example of a bigger piece with lots of empty space:

![](/screenshots/large_piece1.png)
![](/screenshots/large_piece2.png)
![](/screenshots/large_piece3.png)

The bulk of the project is reading the VM input and writing an algorithm to place a piece according to the rules. The basic strategy is to interpret the map into a 2D char array and iterate from negative coordinates all the way until the end of the array or until the the program finds a valid spot to place the piece. Once this basic algortithm has been written, implementing an "attack" strategy becomes an easy fine tuning and tinkering project.

My attack strategy dynamically changes depending on where my starting position is, which walls I've already touched (and therefore halted the opponent in that direction, and the relative position of the opponent's sprawl to my own. I created macros to be able to give more weight to certain strategy (ie do I want to sprint at the opposite wall or do I favor choking out my opponent, how much breathing room do I give my opponent, etc). Once the strategies were weighted in such a manner that I always win on large and medium maps and lose less than 40% of the time on small maps in a disadvantaged starting position, I considered the project complete.

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
