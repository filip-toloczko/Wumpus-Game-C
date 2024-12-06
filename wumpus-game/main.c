/*

Author: Filip Toloczko

*/

#include <stdio.h>
#include <stdlib.h>		// for srand

//Function to display a map of the cave the game takes place in
void displayCave(){
  printf( "\n       ______18______             \n"
          "      /      |       \\           \n"
          "     /      _9__      \\          \n"
          "    /      /    \\      \\        \n"
          "   /      /      \\      \\       \n"
          "  17     8        10     19       \n"
          "  | \\   / \\      /  \\   / |    \n"
          "  |  \\ /   \\    /    \\ /  |    \n"
          "  |   7     1---2     11  |       \n"
          "  |   |    /     \\    |   |      \n"
          "  |   6----5     3---12   |       \n"
          "  |   |     \\   /     |   |      \n"
          "  |   \\       4      /    |      \n"
          "  |    \\      |     /     |      \n"
          "  \\     15---14---13     /       \n"
          "   \\   /            \\   /       \n"
          "    \\ /              \\ /        \n"
          "    16---------------20           \n"
          "\n");
}

//Function that displays game instructions to the user
void displayInstructions(){
  displayCave();

  printf( "Hunt the Wumpus:                                             \n"
          "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
          "room has 3 tunnels leading to other rooms.                   \n"
          "                                                             \n"
          "Hazards:                                                     \n"
          "1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
          "2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
          "   fly you to some random room, which could be troublesome.  Then those bats go \n"
          "   to a new room different from where they came from and from the other bats.   \n"
          "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
          "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
          "    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
          "    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
          "    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
          "    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
          "    room, he snaps your neck and you die!                                       \n"
          "                                                                                \n"
          "Moves:                                                                          \n"
          "On each move you can do the following, where input can be upper or lower-case:  \n"
          "1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
          "   then a room number.                                                          \n"
          "2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
          "   you specify.  Your arrow ends up in the final room.                          \n"
          "   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
          "   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
          "   by spaces. If an arrow can't go a direction because there is no connecting   \n"
          "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
          "   continues doing this until it has traveled the designated number of rooms.   \n"
          "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
          "   automatically pick up the arrow if you go through a room with the arrow in   \n"
          "   it.                                                                          \n"
          "3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
          "4. Enter 'C' to cheat and display current board positions.                      \n"
          "5. Enter 'D' to display this set of instructions.                               \n"
          "6. Enter 'P' to print the maze room layout.                                     \n"
          "7. Enter 'X' to exit the game.                                                  \n"
          "                                                                                \n"
          "Good luck!                                                                      \n"
          " \n\n");
}

//Function that handles the player traveling to an odd numbered room containing the wumpus
void wumpusOdd(int *player, int **moves, int *wumpus){
  printf( "You hear a slithering sound, as the Wumpus slips away. \n"
          "Whew, that was close! \n");
  printf("You are in room %d. ", *player);
  int newWumpus = 20;
  //loop that moves wumpus to lowest numbered adjacent room
  for(int i = 0; i<3; i++){
    if(newWumpus > moves[*wumpus-1][i]){
      newWumpus = moves[*wumpus-1][i];
    }
  }
  *wumpus = newWumpus;
}

//Function that handles the player traveling to an even numbered room containing the wumpus
void wumpusEven(){
  printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
          "It is over.\n");
  printf("\nExiting Program ...\n");
}

//Function that moves the wumpus to the lowest adjacent room if an arrow is shot
void wumpusArrow(int **moves, int *wumpus){
  int newWumpus = 20;
  //loop that moves wumpus to lowest numbered adjacent room
  for(int i = 0; i<3; i++){
    if(newWumpus > moves[*wumpus-1][i]){
      newWumpus = moves[*wumpus-1][i];
    }
  }
  *wumpus = newWumpus;
}

//Function that handles the player traveling to a room containing a pit
void enterPit(){
  printf("Aaaaaaaaahhhhhh....   \n");
  printf("    You fall into a pit and die. \n");
  printf("\nExiting Program ...\n");
}

//Function that handles the user guessing what room the wumpus is in
void guessRoom(int *wumpus){
  int guess = 0;
  printf("Enter room (1..20) you think Wumpus is in: ");
  scanf("%d", &guess);
  //If the users guess is equal to the wumpus then the game is won
  if(guess == *wumpus){
    printf("You won!\n");
  }
  //If the users guess is not equal to the wumpus then the game is lost
  if(guess != *wumpus){
    printf("You lost.\n");
  }
  printf("\nExiting Program ...\n");
}

//Function that handles the user moving the player
void makeMove(int *player, int *moveNumber, int **moves){
  int newPlayer = 0;
  int valid = 0;
  scanf(" %d", &newPlayer);
  //Loop checks if the player is moving to an adjacent room
  for(int i = 0; i<3; i++){
    if((moves[*player-1][i]) == newPlayer){
      valid = 1;
      break;
    }
  }
  //If the move is valid then make the move and increase move number
  if(valid == 1){
    *player = newPlayer;
    *moveNumber += 1;
  }
  //If the move is not valid then display error message
  else{
    printf("Invalid move.  Please retry. \n");
  }
}

//Function that gets the user's desired menu option
void menuOption(int *moveNumber, char *option){
  printf("\n\n");
  printf("%d. Enter your move (or 'D' for directions): ", *moveNumber);
  scanf(" %c", &*option);
}

//Function that populates the moves array
void createRooms(int **moves){
  moves[0][0] = 2;
  moves[0][1] = 5;
  moves[0][2] = 8;
  moves[1][0] = 1;
  moves[1][1] = 3;
  moves[1][2] = 10;
  moves[2][0] = 2;
  moves[2][1] = 4;
  moves[2][2] = 12;
  moves[3][0] = 5;
  moves[3][1] = 3;
  moves[3][2] = 14;
  moves[4][0] = 1;
  moves[4][1] = 4;
  moves[4][2] = 6;
  moves[5][0] = 5;
  moves[5][1] = 7;
  moves[5][2] = 15;
  moves[6][0] = 6;
  moves[6][1] = 8;
  moves[6][2] = 17;
  moves[7][0] = 1;
  moves[7][1] = 7;
  moves[7][2] = 9;
  moves[8][0] = 8;
  moves[8][1] = 10;
  moves[8][2] = 18;
  moves[9][0] = 2;
  moves[9][1] = 9;
  moves[9][2] = 11;
  moves[10][0] = 10;
  moves[10][1] = 12;
  moves[10][2] = 19;
  moves[11][0] = 3;
  moves[11][1] = 11;
  moves[11][2] = 13;
  moves[12][0] = 12;
  moves[12][1] = 14;
  moves[12][2] = 20;
  moves[13][0] = 4;
  moves[13][1] = 13;
  moves[13][2] = 15;
  moves[14][0] = 6;
  moves[14][1] = 14;
  moves[14][2] = 16;
  moves[15][0] = 15;
  moves[15][1] = 17;
  moves[15][2] = 20;
  moves[16][0] = 7;
  moves[16][1] = 16;
  moves[16][2] = 18;
  moves[17][0] = 9;
  moves[17][1] = 17;
  moves[17][2] = 19;
  moves[18][0] = 11;
  moves[18][1] = 18;
  moves[18][2] = 20;
  moves[19][0] = 13;
  moves[19][1] = 16;
  moves[19][2] = 19; 
}

//Function to assign game objects with values
void createGamObjects(int *player, int *wumpus, int *pit1, int *pit2, int *bat1, int *bat2, int *arrow){
  //Assign game objects with random values
  *player = rand() % 20 + 1;
  *wumpus = rand() % 20 + 1;
  *pit1 = rand() % 20 + 1;
  *pit2 = rand() % 20 + 1;
  *bat1 = rand() % 20 + 1;
  *bat2 = rand() % 20 + 1;
  *arrow = rand() % 20 + 1;

  //Conditionals that make sure that every object is set to a unique value
  if(*wumpus == *player){
    *wumpus = rand() % 20 + 1;
  }
  if(*pit1 == *player || *pit1 == *wumpus){
    *pit1 = rand() % 20 + 1;
  }
  if(*pit2 == *pit1 || *pit2 == *wumpus || *pit2 == *player){
    *pit2 = rand() % 20 + 1;
  }
  if(*bat1 == *pit2 || *bat1 == *pit1 || *bat1 == *wumpus || *bat1 == *player){
    *bat1 = rand() % 20 + 1;
  }
  if(*bat2 == *bat1 || *bat2 == *pit2 || *bat2 == *pit1 || *bat2 == *wumpus || *bat2 == *player){
    *bat2 = rand() % 20 + 1;
  }
  if(*arrow == *bat2 || *arrow == *bat1 || *arrow == *pit2 || *arrow == *pit1 || *arrow == *wumpus ||*arrow == *player){
    *arrow = rand() % 20 + 1;
  }
}

//Function that checks if the player entered a room with bat1
void checkForBat1(int *player, int *bat1, int bat2){
  if(*player == *bat1){
    int movedBat;
    int movedPlayer = rand() % 20 + 1;
    //Move the player to a new random position unique from the other bat and the current bat
    //If the position is equal to the other or current bat, assign to a new random position
    while(1) {
      if (movedPlayer != *bat1 && movedPlayer != bat2 && movedPlayer != *player) {
        *player = movedPlayer;
        printf("Woah... you're flying! \n");
        printf("You've just been transported by bats to room %d.\n", *player);
        printf("You are in room %d. ", *player);
        break;
      }
      else{
        movedPlayer = rand() % 20 + 1;
        printf("Woah... you're flying! \n");
        printf("You've just been transported by bats to room %d.\n", *player);
        printf("You are in room %d. ", *player);
      }
    }
    //Assign the bat a new random value 
    movedBat = rand() % 20 + 1;
    //If the new value of the bat is equal to the other bat, the current bat, or the player,
    //select a new random value for the bat
    while(1){
      if(movedBat != *bat1 && movedBat != *player && movedBat != bat2){
        *bat1 = movedBat;
        break;
      }
      else{
        movedBat = rand() % 20 + 1;
      }
    }
  }
}

//Function that checks if the player entered a room with bat2
void checkForBat2(int *player, int bat1, int *bat2){
  if(*player == *bat2){
    int movedBat;
    int movedPlayer = rand() % 20 + 1;
    //Move the player to a new random position unique from the other bat and the current bat
    //If the position is equal to the other or current bat, assign to a new random position
    while(1) {
      if (movedPlayer != bat1 && movedPlayer != *bat2 && movedPlayer != *player) {
        *player = movedPlayer;
        printf("Woah... you're flying! \n");
        printf("You've just been transported by bats to room %d.\n", *player);
        printf("You are in room %d. ", *player);
        break;
      }
      else{
        movedPlayer = rand() % 20 + 1;
        printf("Woah... you're flying! \n");
        printf("You've just been transported by bats to room %d.\n", *player);
        printf("You are in room %d. ", *player);
      }
    }
    //Assign the bat a new random value 
    movedBat = rand() % 20 + 1;
    //If the new value of the bat is equal to the other bat, the current bat, or the player,
    //select a new random value for the bat
    while(1){
      if(movedBat != bat1 && movedBat != *player && movedBat != *bat2){
        *bat2 = movedBat;
        break;
      }
      else{
        movedBat = rand() % 20 + 1;
      }
    }
  }
}

//Function that shoots the arrow through the first room
void arrowRoom1(int room1, int player, int *arrow, int **moves, int wumpus, int *killedWumpus, int *killedPlayer, int *hasArrow, int *shotSomeone){
  int valid = 0;
  *killedWumpus = 0;
  *killedPlayer = 0;
  scanf("%d", &room1);
  //Check if the move is valid, if so set the valid variable equal to 1
  if(room1 == player){
    valid = 1;
  }
  else{
    for(int i = 0; i<3; i++){
      if((moves[player-1][i]) == room1){
        valid = 1;
        break;
      }
    }
  }
  //If the move is valid, shoot the arrow to the selected room and check if the player or the wumpus have been killed
  if(valid == 1){
    *arrow = room1;
    if (*arrow == wumpus){
      *killedWumpus = 1;
      printf( "Wumpus has just been pierced by your deadly arrow! \n"
            "Congratulations on your victory, you awesome hunter you.\n");
      printf("\nExiting Program ...\n");
    }
    if(*arrow == player){
      *killedPlayer = 1;
      printf( "You just shot yourself.  \n"
            "Maybe Darwin was right.  You're dead.\n");
      printf("\nExiting Program ...\n");
    }
  }
  //If the move is not valid then move the arrow to the lowest adjacent room to the player
  else if(valid!=1){
    printf("Room %d is not adjacent.  Arrow ricochets...\n", room1);
    int newArrow = 20;
    //loop that moves arrow to lowest numbered adjacent room
    for(int i = 0; i<3; i++){
      if(newArrow > moves[player-1][i]){
        newArrow = moves[player-1][i];
      }
    }
    *arrow = newArrow;
    //Check if the arrow ricocheted into the wumpus, killing it
    if (*arrow == wumpus){
      *killedWumpus = 1;
      printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
            "Accidental victory, but still you win!\n");
      printf("\nExiting Program ...\n");
    }
  }
  //Check if someone died and the game should end
  if(*arrow == wumpus || *arrow == player){
    *shotSomeone = 1;
  }
  *hasArrow = 0;
}

//Function that shoots the arrow through the second and third rooms
void arrowRoom2(int room1, int player, int *arrow, int **moves, int wumpus, int *killedWumpus, int *killedPlayer, int *hasArrow, int *shotSomeone){
  int valid = 0;
  *killedWumpus = 0;
  *killedPlayer = 0;
  scanf("%d", &room1);
  //Check if the move is valid, if so set the valid variable equal to 1
  if(room1 == player){
    valid = 1;
  }
  else{
    for(int i = 0; i<3; i++){
      if((moves[*arrow-1][i]) == room1){
        valid = 1;
        break;
      }
    }
  }
  //If the move is valid, shoot the arrow to the selected room and check if the player or the wumpus have been killed
  if(valid == 1){
    *arrow = room1;
    if(*arrow == wumpus){
      *killedWumpus = 1;
      printf( "Wumpus has just been pierced by your deadly arrow! \n"
            "Congratulations on your victory, you awesome hunter you.\n");
      printf("\nExiting Program ...\n");
    }
    if(*arrow == player){
      *killedPlayer = 1;
      printf( "You just shot yourself.  \n"
            "Maybe Darwin was right.  You're dead.\n");
      printf("\nExiting Program ...\n");
    }
  }
  //If the move is not valid then move the arrow to the lowest adjacent room to the previous room
  else{
    printf("Room %d is not adjacent.  Arrow ricochets...\n", room1);
    int newArrow = 20;
    //loop that moves arrow to lowest numbered adjacent room
    for(int i = 0; i<3; i++){
      if(newArrow > moves[*arrow-1][i]){
        newArrow = moves[*arrow-1][i];
      }
    }
   *arrow = newArrow;
    //Check if the arrow ricocheted into the wumpus, killing it
    if (*arrow == wumpus){
      *killedWumpus = 1;
      printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
            "Accidental victory, but still you win!\n");
      printf("\nExiting Program ...\n");
    }
    //Check if the arrow ricocheted into the player, killing it
    if(*arrow == player){
      *killedPlayer = 1;
      printf( "You just shot yourself, and are dying.\n"
            "It didn't take long, you're dead.\n");
      printf("\nExiting Program ...\n");
    }
  }
  //Check if someone died and the game should end
  if(*arrow == wumpus || *arrow == player){
    *shotSomeone = 1;
  }
  *hasArrow = 0;
}

//Check if either the player or the wumpus died, if so end the game
void gameOver(int shotSomeone){
  if(shotSomeone == 1){
    exit(0);
  }
}

//Handle the player picking up and carrying the arrow
void pickedUpArrow(int player, int *arrow, int *hasArrow){
  if(player == *arrow){
    printf("Congratulations, you found the arrow and can once again shoot.\n");
    *hasArrow = 1;
    *arrow = -1;
  }  
  if(*arrow == -1){
    *hasArrow = 1;
  }
}

//Display the room number the player is in
void displayRoom(int player, int wumpus, int pit1, int pit2, int bat1, int bat2){
  if((player != wumpus) && (player != pit1) && (player != pit2) && (player!=bat1) && (player!=bat2)){
    printf("You are in room %d. ", player);
  }
}

//Check if the player and wumpus are equal and odd, calls the wumpusOdd function
void checkWumpusOdd(int *player, int *wumpus, int **moves){
  if((*player == *wumpus) && (*wumpus%2!=0)){
    wumpusOdd(&*player, moves, &*wumpus);
  }
}

//Check if the player and wumpus are equal and evem, calls the wumpusEven function, ends the game
void checkWumpusEven(int *player, int *wumpus){
  if((*player == *wumpus) && (*wumpus%2==0)){
    wumpusEven();
    exit(0);
  } 
}

//Checks if the player is equal to a pit, calls enterPit function, ends the game
void checkPits(int *player, int *pit1, int *pit2){
  if(*player == *pit1 || *player == *pit2){
    enterPit();
    exit(0);
  }
}

//Checks if the player is adjacent to the wumpus
void adjacentToWumpus(int *player, int *wumpus, int **moves){
  for(int i = 0; i<3; i++){
    if(*player == moves[*wumpus-1][i] && *player != *wumpus){
      printf("You smell a stench. ");
      break;
    }
  }
}

//Checks if the player is adjacent to the pits
void adjacentToPits(int *player, int *pit1, int *pit2, int **moves){
  for(int i = 0; i<3; i++){
    if(*player == moves[*pit1-1][i] || *player == moves[*pit2-1][i]){
      printf("You feel a draft. ");
      break;
    }
  }
}

//Checks if the player is adjacent to the bats
void adjacentToBats(int *player, int *bat1, int *bat2, int **moves){
  for(int i = 0; i<3; i++){
    if(*player == moves[*bat1-1][i] || *player == moves[*bat2-1][i]){
      printf("You hear rustling of bat wings. ");
      break;
    }
  }
}

//Function that handles the player shooting the arrow
void shootArrow(int *numRooms, int *room1, int *player, int *arrow, int **moves, int *wumpus, int *killedWumpus,
                int *killedPlayer, int *hasArrow, int *shotSomeone){
  printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
  //Get the amount of rooms you need to shoot through, if greater than three set to three
  scanf( "%d", &*numRooms);
  if(*numRooms > 3){
    printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
    *numRooms = 3;
  }
  //Handles the scenario where arrow is fired through one room
  if(*numRooms == 1){
    arrowRoom1(*room1, *player, &*arrow, moves, *wumpus, &*killedWumpus, &*killedPlayer, &*hasArrow, &*shotSomeone);
    gameOver(*shotSomeone);
  }
  //Handles the scenario where arrow is fired through two rooms
  if(*numRooms == 2){
    arrowRoom1(*room1, *player, &*arrow, moves, *wumpus, &*killedWumpus, &*killedPlayer, &*hasArrow, &*shotSomeone);
    gameOver(*shotSomeone);
    arrowRoom2(*room1, *player, &*arrow, moves, *wumpus, &*killedWumpus, &*killedPlayer, &*hasArrow, &*shotSomeone);
    gameOver(*shotSomeone);
  }
  //Handles the scenario where arrow is fired through three rooms
  if(*numRooms == 3){
    arrowRoom1(*room1, *player, &*arrow, moves, *wumpus, &*killedWumpus, &*killedPlayer, &*hasArrow, &*shotSomeone);
    gameOver(*shotSomeone);
    arrowRoom2(*room1, *player, &*arrow, moves, *wumpus, &*killedWumpus, &*killedPlayer, &*hasArrow, &*shotSomeone);
    gameOver(*shotSomeone);
    arrowRoom2(*room1, *player, &*arrow, moves, *wumpus, &*killedWumpus, &*killedPlayer, &*hasArrow, &*shotSomeone);
    gameOver(*shotSomeone);
  } 
  //If the wumpus isn't killed, it moves to the lowest adjacent room to itself
  wumpusArrow(moves, &*wumpus);
}

//Main function
int main(void) {
  //Radom number generator seeded with 1
  srand(1);

  //Dynamic memory allocation for 2d array of possible moves
  int **moves = malloc(20*sizeof(int*));
  for(int i = 0; i < 20; i++){
    moves[i] = malloc(3*sizeof(int));
  }

  //This function populates the moves array with all possible moves
  createRooms(moves);

  //Variable declarations for the program
  int player, wumpus, pit1, pit2, bat1, bat2, arrow;
  int moveNumber = 1;
  int hasArrow = 0;
  char option;

  //This function assigns values to the game objects
  createGamObjects(&player, &wumpus, &pit1, &pit2, &bat1, &bat2, &arrow);

  //Loop that runs the game
  while(1){
    //Check if the player has obtained an arrow
    pickedUpArrow(player, &arrow, &hasArrow);  
    
    //display room number if the player is not in a room with the wumpus or a pit
    displayRoom(player, wumpus, pit1, pit2, bat1, bat2);
    
    //Calls wumpusOdd function if player == wumpus and wumpus%2 is not 0
    checkWumpusOdd(&player, &wumpus, moves);
    
    //Calls wumpusEven function if player == wumpus and wumpus%2 is 0 and ends the game
    checkWumpusEven(&player, &wumpus);
    
    //Calls enterPit function if player == pit1 or pit 2 and ends the game
    checkPits(&player, &pit1, &pit2);

    //Checks if the player enters a room with a bat, if so moves the player
    checkForBat1(&player, &bat1, bat2);
    checkForBat2(&player, bat1, &bat2);
    
    //Prints message if the player is in a room adjacent to the wumpus
    adjacentToWumpus(&player, &wumpus, moves);
    
    //Prints message if the player is in a room adjacent to a pit
    adjacentToPits(&player, &pit1, &pit2, moves);
    
    //Prints message if the player is in a room adjacent to a bat
    adjacentToBats(&player, &bat1, &bat2, moves);
    
    //Calls menuOption() function to get user input for the menu option
    menuOption(&moveNumber, &option);

    //If the menuOption is equal to S or s and the player has an arrow then call the shootArrow function
    //Otherwise print the error message
    if(option == 's' || option == 'S'){
      //Variable declarations specific to this function
      int numRooms = 0;
      int killedWumpus;
      int killedPlayer;
      int shotSomeone = 0;
      int room1;
      //Increase moveNumber by 1
      moveNumber += 1;
      //If the player doesn't have an arrow, show an error message
      if(hasArrow != 1){
        printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
      }
      //If the player has an arrow then execute the shootArrow functiion
      else{
        shootArrow(&numRooms, &room1, &player, &arrow, moves, &wumpus, &killedWumpus, &killedPlayer, &hasArrow,           
                   &shotSomeone);
      }
    }

    //If the option is equal to P or p then call the displayCave() function
    if(option == 'p' || option == 'P'){
      displayCave();
    }
    //If the option is X or x then exit the program and display the exiting message
    if(option == 'x' || option == 'X'){
      printf("\nExiting Program ...\n");
      break;
    }
    //If option is R or r then prompt user to insert values for game variables
    if(option == 'r' || option == 'R'){
      printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
      scanf(" %d %d %d %d %d %d %d", &player, &wumpus, &pit1, &pit2, &bat1, &bat2, &arrow);
    }
    //If option is D or d then call the displayIntrusctions() function
    if(option == 'd' || option == 'D'){
      displayInstructions();
    }
    //If option is C or c then display values of game variables
    if(option == 'c' || option == 'C'){
      printf(  "Cheating! Game elements are in the following rooms: \n"
               "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
               "%4d %5d %6d %5d %5d %5d %5d \n\n",player,wumpus,pit1,pit2,bat1,bat2,arrow);
    }
    //If option is M or m then call the makeMove() function
    if(option == 'm' || option == 'M'){
      makeMove(&player, &moveNumber, moves);
    }
    //If option is G or g then call the guessRoom function and end the program
    if(option == 'g' || option == 'G'){
      guessRoom(&wumpus);
      return 1;
    }
    continue;
  }
  return 0;
}