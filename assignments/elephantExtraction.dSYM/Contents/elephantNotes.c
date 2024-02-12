/*
    2D grid
        ex. int a[100][100]
            generally not advised because it takes a block of contigous memory
            increased chance to fail to allocate memory (stack overflow)

        instead use double pointer method to allocate the memory

    elephant will try to find location with the most food, in all 4 directions
        main problem if elephant is on the edge of the grid
            will try to access memory that is not allocated
            will cause a seg fault
            need to check if the elephant is on the edge of the grid
                if so, do not check that direction
        pad outside with 0's (additional frame) compare with do while
    
    if an elephant it currently on a watermelon, it will stay at that location.
    if not, look to find food.
    if no food "back off" -> previously where did it go (stacks) coordinate system
                                                            stack of chars
                                                            U, D, L, R
                                                            U r++ (up row)


    you need to handle the elephant movement first, THEN let them eat otherwise there will be problems.


*/