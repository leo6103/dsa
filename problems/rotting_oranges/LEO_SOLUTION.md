Naive approach:
Scan with On^2 to count total of each type
Store rotting to a datastructure (queue or vector)
Do bfs with each (pass grid to update status, count with each miniute, 1 min = 1 loop)