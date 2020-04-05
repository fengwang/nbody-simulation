## Introduction

This is a 3D simulation of a dynamical system of particles, under the influence of gravity. 

Consider n point masses m_1, ... ,m_n in three-dimensional space. 
Suppose that the force of attraction experienced between each pair of particles is Newtonian. 
Then, if the initial positions in space and initial velocities are specified for every particle at some present instant t_0, 
determine the position of each particle at every future (or past) moment of time.

### Configuration

N particles are generated randomly within a sphere. For each particle generated, its coordinate P(p_x, p_y, p_z) 
$$p_x^2 + p_y^2 + p_z^2 < 1 m$$, it mass m $$10^5 kg < m < 10^6 kg $$. The elapse time interval is set to $$0.1 s$$.
Also Opengl is employed to visualize the simulation result.

## Algorithms

### Integration Algorithm 
Using classic Runge-Kutta method.

http://math.fullerton.edu/mathews/n2003/RungeKuttaMod.html

### Simulation Algorithm
Barnes-Hut simulation

J. Barnes and P. Hut (December 1986). "A hierarchical O(N log N) force-calculation algorithm". Nature 324 (4): 446-449. doi:10.1038/324446a0.

The volume is divided up into cubic cells in an octree, so that only particles from nearby cells need to be treated individually, and particles in distant cells can be treated as a single large particle centered at its center of mass.
                                                                                                               
                                                                                                               
### Parallel
Using c++0x thread provided by pthread.

## Simulation Result

* N = 3    ------- file  video/nbody_3.mkv  
* N = 30   ------- file  video/nbody_30.mkv  
* N = 300  ------- file  video/nbody_300.mkv  
* N = 1000 ------- file  video/nbody_3000.mkv  

## Discussion

## Author
**Wang Feng** wang_feng@live.com

## License
Licensed under the GPLv3.
