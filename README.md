# PhysicsAnimatorByChart-1D
## What it is
This is a program designed to create 1D animations out of standard Physics variables.  
If you have unknowns, it will use math to calculate them (if it can)

## Variable Definitions
Di = Initial Distance, aka the distance the object is initially at the begining of the motion event. (m)  
Df = Final Distance, aka the distance the object is at the end of the motion event. (m)  
Vi = Initial Velocity, aka the velocity the object starts the motion event with. (m/s)  
Vf = Final Velocity, aka the veloity the object ends the motion event with. (m/s)  
a = Acceleration, aka how many m/s the object gains per second. (m/s/s)  
t = Time, aka how long the motion event takes in real time. (s)  

? = Unknown Value, aka have the program solve for this value if you dont know it

## Examples
#### Rolling a marble up a slanted surface until it stops
```
Di: 0
Df: ?
Vi: 3
Vf: 0
a: -0.2
t: ?
```

#### Dropping a ball from an airplane
```
Di: 1500
Df: 0
Vi: 0
Vf: ?
a: -9.8
t: ?
```
