# pointCollision
test if a point collides other points

written in C++; [Scala version](https://github.com/dalvikus/pointCollisionInScala)

## Problem
> There are two dimensional array which contains 1 (true) or 0 (false). How do we tell if given a point is true or false **efficiently**?

## QuadTree
Here is one solution by QuadTree. Assume that **true** points are clustered

1. by themselves
2. by sort of image processing like **erode** and **dilate**; [Eroding and Dilating](http://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html#morphology-1)

See [Quadtree](https://en.wikipedia.org/wiki/Quadtree) for general concept of QuadTree, but this work does not follow its algorithm there.

## How to Compile
```
$ g++ -Wall -Wextra -g -c -o Interval.o Interval.cpp
$ g++ -Wall -Wextra -g -c -o Node.o Node.cpp
$ g++ -Wall -Wextra -g -o testNode testNode.cpp Interval.o Node.o
# -g for debugging

$ ./testNode
# or for debugging with valgrind; especially memory leak
$ valgrind --leak-check=full ./testNode
```

## How to Use
1. Create a root node with horizontal interval and vertical interval which defines a square covered by the root node
2. Add **positive** point to a root node, which find a smallest node that contains only the point
3. Add more points
4. Call `contains` to check whether a point is potitive or not
5. Call **simplify** to merge nodes to boost `contains` by `contains2`

## Why Collision
In a 2d game map, QuadTree is a efficient way to check if an object collides other ones.
