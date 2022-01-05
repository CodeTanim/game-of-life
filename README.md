# Conway's Game of Life
The Game of Life is also simply known as Life. It is a [cellular automaton](https://en.wikipedia.org/wiki/Cellular_automaton) created by a British mathmatecian named John Horton Conway in 1970. It is known as a zero-player game, which means that any evolution is dependent on its initial state. A game of life automaton can be triggered by reading some initial configuration and observing how the grid evolves. 


# Rules of The Game
Every cell on the grid will be interacting with its' eight neigbours. Each cell will either be dead or alive depending on the status of the neighbours. A live cell is indicated by the letter "O" and a dead cell is indicated by a dot. The four main rules are stated below:

1) If a live cell has fewer than 2 neighbors, it dies (underpopulation).
2) If a live cell has 2 or 3 neigbours, it stays alive for the nexr generation (preservation). 
3) If a live cell has more than 3 neighbors, it dies (overpopulation).
4) If a dead cell has exactly 3 neighbors, it becomes alive (reproduction).


# Running the Game

The best way to run this program is on a linux based system. As you can see in the videos below, I used the command-line on a arch-linux on a virtual machine to run this program.
The command line makes use of these arguments:

<div class="sourceCode" id="cb1"><pre class="sourceCode latex"><code class="sourceCode latex"><span id="cb1-1"><a href="#cb1-1" aria-hidden="true"></a>Usage: ./life [OPTIONS]...</span>
<span id="cb1-2"><a href="#cb1-2" aria-hidden="true"></a>Text-based version of Conway&#39;s game of life.</span>
<span id="cb1-3"><a href="#cb1-3" aria-hidden="true"></a></span>
<span id="cb1-4"><a href="#cb1-4" aria-hidden="true"></a>   --seed,-s     FILE     read start state from FILE.</span>
<span id="cb1-5"><a href="#cb1-5" aria-hidden="true"></a>   --world,-w    FILE     store current world in FILE.</span>
<span id="cb1-6"><a href="#cb1-6" aria-hidden="true"></a>   --fast-fw,-f  NUM      evolve system for NUM generations and quit.</span>
<span id="cb1-7"><a href="#cb1-7" aria-hidden="true"></a>   --help,-h              show this message and exit.</span></code></pre></div>


The game essentially has two modes; a fast-forward mode and a continous automated mode. 

* In the fast-forward mode, the program will simply take in a n number of generations from the command-line and then evolve and ONLY output the grid for that generation. So, for example lets say you want to evolve the glider grid for 7 generations, you can type and run the following in the command line terminal, to get the following output:
 
       ./life -f 7 -s res/glider-40x20 
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ...................O....................
       ....................OO..................
       ...................OO...................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................
       ........................................


* In the continous automated mode (the fun mode), the program will contiously evolve and output the grid until you decide to quit the program. 



    To use the glider grid as the initial grid, you can type the following in the command-line and observe the continous evolution in the video below:
    
    ```./life -s res/glider-40x20```
    
    

  https://user-images.githubusercontent.com/80434026/136458789-7240fcd6-8bc5-43db-b0ee-e4e5e472f2e3.mp4
  
  
  
    For the diehard grid:
    
     ```./life -s res/diehard-80x60```
     
     

  https://user-images.githubusercontent.com/80434026/136470110-e9c992e0-5816-4075-bede-2fb83d2bdbd7.mp4
  
  
  For the pentamino grid:
  
   ```./life -s res/pentamino-80x60```
   
   

  https://user-images.githubusercontent.com/80434026/136470749-8649ff5c-c8d0-4dd5-be43-947f240115ba.mp4


  
  
 
  
    For the acorn grid:
    
     ```./life -s res/acorn-110x60```
     
     

  https://user-images.githubusercontent.com/80434026/136470276-b1df1b11-a43d-49a9-9603-0090241654c7.mp4


    


    
  
  


