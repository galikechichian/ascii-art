# ascii-art
This is a command line ascii art game written in C :) 

### Possible commands: 
```
GRID		  x y        -- grid size - 2 integers
CHAR		  c          -- pen - single character
RECTANGLE	a,b c,d    -- top left corner and bottom right cordner coords - 4 integers
LINE		  a,b c,d    -- endpoint coords - 4 integers
CIRCLE	  x,y r      -- center coords and radius - 3 integers
END                  -- exits the game
DISPLAY              -- displays the grid
```

### Example of simple game commands and outputs:
```
GRID 10 10
DISPLAY
9          
8          
7          
6          
5          
4          
3          
2          
1          
0          
 0123456789
LINE 0,0 4,5
CHAR ^
LINE 0,5 5,0
DISPLAY
9          
8          
7          
6          
5^         
4 ^  *     
3  ^*      
2  *^      
1 *  ^     
0*    ^    
 0123456789
END
```
