# MINDBEND-PATHFINDER-2024

In the Path Finder/Maze Runner project, the key components utilized include an Arduino Uno microcontroller, three ultrasonic sensors, and an L293D motor driver. The code provided offers an optimal solution for navigating mazes. Initially, the maze runner traverses the path until it reaches the final checkpoint, which is typically an open space.

Once the initial traversal is completed, the bot gathers data from the traversed path and stores it in an array. Subsequently, the algorithm modifies the path by identifying and eliminating instances of U-turns. By analyzing the previously traversed path, the bot learns to avoid U-turns, optimizing its subsequent movements. This iterative process involves replacing U-turns with appropriate turns, facilitating faster and more efficient navigation through the maze.

The maze runner's efficiency is enhanced through this iterative refinement process, which iteratively improves the path based on past experiences. With each iteration, the bot becomes increasingly adept at navigating the maze, ultimately achieving an optimal solution.

This project not only demonstrates the capabilities of the Arduino Uno and the L293D motor driver but also showcases the implementation of advanced algorithms for path optimization in maze-solving scenarios. The utilization of ultrasonic sensors adds another layer of sophistication, enabling the bot to perceive its environment and make informed navigational decisions. Overall, this project embodies the fusion of hardware and software components to create a functional and intelligent maze runner.
