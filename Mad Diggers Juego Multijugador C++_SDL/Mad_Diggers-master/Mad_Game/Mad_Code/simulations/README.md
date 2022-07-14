# Simulator
> Any question, ask ***dimateos***

This is the simulator input and output folder.

* as INPUT takes a **NAME**_data.sim file
* as OUTPUT writes a **NAME**_log.sim file
* Statistics calculated are stored in **NAME**_stats.sim

**NOTE:** The simulator methods need the **NAME** string. Not any of the following:
* NAME_data
* NAME_
* NAME_data.sim
* etc

## _data format (w/ example)

First 3 lines:

```c++
8  //_LAST_ROUND_ ending round
1  //_FIRST_ROUND_ starting round (0 or 1 usually)
10 //_ROLLS_PER_ROUND_ based on the "dices" values (4+3+2+1)
```

Afterwards comes each round players' dice picks
 * each round rolls have to add up to _ROLLS_PER_ROUND_
 * a total of _LAST_ROUND_ rounds will be player (more are ignored)

```c++
4 3 2 1 //p1 takes 4 rolls, p2 3, p3 2, p4 1
4 3 2 1 //and so on
4 3 2 1
4 3 2 1
3 2 1 4
2 1 3 4
1 2 3 4
1 2 3 4
```
