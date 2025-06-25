Rigidbody physics engine in C

Begin with shape representations
Each shape needs
Shape Type (circle, line,)
Position
Velocity
Acceleration
Mass
Rotation
(what else, if any?)

Can use struct for each, with structs in a union when actually initialising a shape

Need another file, interactions.c or something, for physics algorithms

collision_detect() -> will i need separate ones for all the different combinations of shapes (line-line, line-circle, etc)?
gravity()?
rotate()?

rendering i can abstract for now and just use a library

more complex shapes can be built from dots or something - i can look up on wikipedia how they are usually made
