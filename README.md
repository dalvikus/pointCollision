# pointCollision
test if a point collides other points

## Problem
> There are two dimensional array which contains 1 (true) or 0 (false). How do we tell if given a point is true or false **efficiently**?

## QuadTree
Here is one solution by QuadTree. Assume that **true** points are clustered

1. by themselves
2. by sort of image processing like **erode** and **dilate**; [Eroding and Dilating](http://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html#morphology-1)

See [Quadtree](https://en.wikipedia.org/wiki/Quadtree) for general concept of QuadTree, but this work does not follow its algorithm there.

## Why collision
In a 2d map in a game, QuadTree is a efficient way to check if an object collides other ones.
