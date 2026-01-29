| Module Code        | IY453                              |
| ------------------ | ---------------------------------- |
| Group              | A                                  |
| Module Title       | Software Design and Implementation |
| Assessment Type    | Coursework Stage 1                 |
| Module Tutor Name  | Mustafa Ghashim                    |
| Student ID Number  | P485902                            |
| Date of Submission | 29/01/2025                         |

☒ *I confirm that this assignment is my own work. Where I have referred to academic
sources, I have provided in-text citations and included the sources in the
final reference list.*

 ☒ *Where I have used AI, I have cited and
referenced appropriately.*

# **Introduction**

This project is a text-based "choose your own adventure" game where the player finds themselves at the centre of an interactive storyline. The game relies entirely on text descriptions and user choices to create an immersive experience, allowing the player to explore the world, make decisions and influence the storyline.
The adventure is built on branching storylines, where each choice has its own weight and leads to different consequences, paths, and endings. Instead of graphics, the focus of program is on atmosphere, storytelling, and the player's imagination, as the program is entirely text-based. The goal of this project is to create a simple but engaging game that demonstrates logical structure, decision-making, and narrative flow in a text-based environment.

## 

---

### Program Specification

---

## Core functionality

- The program should provide a text-based “choose your own adventure” game where the player navigates the story using text input and output only.

- The program should prompt the player to enter their name at the start of the game and use this name within game dialogue and messages to personalise the experience.

- The game should present the player with binary choices (two options) in each scenario, with each choice leading to different consequences.

- Some choices lead to the game ending, forcing the player to start over, while other choices allow the player to progress towards completing the game.

- The program should provide clear feedback of each player choice, describing the outcome.

- The game should maintain player statistics, including health, attack power, defence, inventory, and score, which are updated throughout gameplay.

- The program should include an inventory system that allows the player to collect, store, and manage items found during the adventure.

- Items such as weapons, clothing, food, potions, and keys should influence the rest of the game by unlocking or adding new choices and paths, as well as changing the player's stats.

- The game should include combat-based scenarios where the outcome of battles is influenced by player stats and collected items.

- The game shall include puzzle-based scenarios, such as riddles, anagrams, or logic-based challenges, which must be solved to progress.

- The program should allow the player to save their game progress to a file and load a saved game, restoring all relevant game state data (player name, current scene,
   inventory, stats, and score).

- The game should implement a scoring system that rewards the player for defeating enemies, solving puzzles, and completing challenges.

- The program shall display the current score at key points in the game and present a final score screen at the end of the game.

- The program should validate all user input to ensure reliability and prevent crashes, displaying clear error messages when invalid data is entered by user.

### System constraints

- System should compile and run in the CLion IDE using the C++17standard or later and must ensure cross-platform compatibility.

- The program should be a console-based application and must not use any graphical user interface.

- All interaction between the player and the game should be performed using text input and text output.

- Each game scenario should give the player exactly two choices, ensuring binary decision-making throughout the game.

- The game should have at least 30 binary choices across the full gameplay experience.

- The program should use either text files or binary files to store game data and give opportunity to resume game.

- The program should handle invalid input correctly and should not terminate unexpectedly due to incorrect user input.

#### 

---

### Input/Process/Output table

---

<style>
</style>

| *Feature/Task*        | *Inputs*                   | *Process*                                                                  | *Output*                                  |
| --------------------- | -------------------------- | -------------------------------------------------------------------------- | ----------------------------------------- |
| *Start game*          | *None (program launch)*    | *Initialise game variables, set default player stats, prepare first scene* | *Welcome message*                         |
| *Enter player name*   | *Player name (text input)* | *Validate name input and store player name*                                | *Personalised greeting with player*       |
| *Display scene*       | *None*                     | *Load scenario description and available choices*                          | *Scenario text and two choices displayed* |
| *Player choice*       | *Player choice (1 or 2)*   | Validate input and determine next scene based on choice                    | *Outcome description or next scenario*    |
| *Save game*           | *Save option*              | *Save player data, inventory, stats, score and current scene to file.*     | *Successful or error message*             |
| *Load game*           | *Load option*              | *Read saved data from file and resume the game.*                           | *Successful or error message*             |
| *Display score*       | *Results during the game*  | *Calculate and update score*                                               | *Current score*                           |
| *Combat encounter*    | *Player and enemy stats*   | *Calculate combat outcome*                                                 | *Victory, defeat, or game over message*   |
| *Update player stats* | *Choice result*            | *Update health, inventory, score, etc.*                                    | *Updated player stats*                    |
| *Use item*            | *Item stats*               | *Apply item effects (heal, boost stats, unlock path)*                      | *Updated stats or unlocked option.*       |
| *End game*            | *Final scene*              | *Calculate final score and end the game.*                                  | *Victory message and final score*         |
