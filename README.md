<h1 align="center">
    <b>The Talos Records</b>
</h1>

<p align="center">
  <img src="https://github.com/user-attachments/assets/02886080-ce39-4db7-b225-f66f619ed87d"/>
</p>

<p align="center">
    A small-scale prototype inspired by the 2014 game, The Talos Principle. It focuses on a recording mechanic and player interaction with the world, aiming to recapture the gameplay feel of the original game.
</p>

<br>

## Interaction System

<p align="center">
  <img src="https://github.com/user-attachments/assets/cde63b04-5b00-4a75-8cc7-0fd90a86d728" style="width: 48%; margin-right: 2%;" />
  <img src="https://github.com/user-attachments/assets/f2984eef-aab0-49ef-9937-c0a081e92a86" style="width: 48%;" />
</p>

>Player interaction with the world.  
>[Interaction.h](TalosRecords/Source/TalosRecords/Interaction.h)  
>[Interaction.cpp](TalosRecords/Source/TalosRecords/Interaction.cpp)

>Item interaction with world.  
>[ItemHandle.h](TalosRecords/Source/TalosRecords/ItemHandle.h)  
>[ItemHandle.cpp](TalosRecords/Source/TalosRecords/ItemHandle.cpp)

>An interface that implements basic interaction methods.  
>[IInteractable.h](TalosRecords/Source/TalosRecords/IInteractable.h)

<br>

## Game Objects

>Base class of an item that player can interact with and place into the world.  
>[Item.h](TalosRecords/Source/TalosRecords/Item.h)  
>[Item.cpp](TalosRecords/Source/TalosRecords/Item.cpp)

>Interactable object on which items can be placed, or taken from.  
>[ItemPad.h](TalosRecords/Source/TalosRecords/ItemPad.h)  
>[ItemPad.cpp](TalosRecords/Source/TalosRecords/Item.cpp)

>Computer from which you access terminal.  
>[Terminal.h](TalosRecords/Source/TalosRecords/Terminal.h)  
>[Terminal.cpp](TalosRecords/Source/TalosRecords/Terminal.cpp)

## Puzzle
>An interface that implements objective related methods..  
>[IObjective.h](TalosRecords/Source/TalosRecords/IObjective.h)  

>Script that references different components of a puzzle, tracking if objectives are completed.  
>[Puzzle.h](TalosRecords/Source/TalosRecords/Puzzle.h)  
>[Puzzle.cpp](TalosRecords/Source/TalosRecords/Puzzle.cpp)

## Recording



