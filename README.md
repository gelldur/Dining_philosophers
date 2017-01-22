Dining philosophers (QtBase)
----

Implementation of dining philosophers problem in Qt: “N philosophers sit at a round table with
bowls. Forks are placed between each pair of adjacent philosophers. Each philosopher must
alternately think and eat. However, a philosopher can only eat when he has both left and right
forks”. Find solution that avoids deadlock and will preserve all philosophers from starvation.
Requirements:
- Each philosopher is subclass of QThread
- Number of philosophers is variable (initially 5), algorithm should start automatically.
- Implement MVC model for philosopher class that will allow to add / remove philosophers after dinner algorithm is started
- Application GUI should represent dining philosophers in MVC based view
- Implement custom MVC delegate for philosopher that will present class as avatar (image), name and state (eating / thinking) and button to remove item from model

----

I'm using cmake for easy compile :)
