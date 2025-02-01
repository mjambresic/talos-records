<h1 align="center">
    <b>🎞️ The Talos Records 🎞️</b>
</h1>

<p align="center">
  <img src="https://github.com/user-attachments/assets/0919ca1e-48fc-465e-8b9c-ece2a49295e1"/>
</p>


<p align="center">
    A small-scale prototype inspired by the 2014 game, The Talos Principle. It focuses on a recording mechanic and player interaction with the world, aiming to recapture the gameplay feel of the original game.
</p>

<br>

## Project Details
Author: Matija Jambresic <br>
Start Date: 20th January 2025 <br>
Duration: ~ 2 weeks <br>
Unreal Engine: v5.5.1  
[Gameplay video.](https://youtu.be/nRAnBNXDPjI)

<br>

## Interaction System
<p align="center">
  <img src="https://github.com/user-attachments/assets/cde63b04-5b00-4a75-8cc7-0fd90a86d728" style="width: 48%; margin-right: 2%;" />
  <img src="https://github.com/user-attachments/assets/f2984eef-aab0-49ef-9937-c0a081e92a86" style="width: 48%;" />
</p>

>[Interaction.h](TalosRecords/Source/TalosRecords/Interaction.h) ---
>[Interaction.cpp](TalosRecords/Source/TalosRecords/Interaction.cpp)  
>Handles basic player interaction with the world. Casts a line trace to detect objects available for interaction and manages interaction input.  

>[ItemHandle.h](TalosRecords/Source/TalosRecords/ItemHandle.h) ---
>[ItemHandle.cpp](TalosRecords/Source/TalosRecords/ItemHandle.cpp)  
>A scene component that picks up or puts down items. It handles interaction while items are in the player's hand and resolves placing or dropping them.

>[IInteractable.h](TalosRecords/Source/TalosRecords/IInteractable.h)  
>An interface that defines basic interaction methods. Objects implementing this interface can interact with the player in a specific way.

<br>

## Recording System 🎥
<p align="center">
  <img src="https://github.com/user-attachments/assets/88f9dbcb-4129-48c5-ae01-2597e9acf6cd" style="width: 48%; margin-right: 2%;" />
  <img src="https://github.com/user-attachments/assets/c3d62946-8992-4872-b585-3747a67a1226" style="width: 48%;" />
</p>

>[RecordingStation.h](TalosRecords/Source/TalosRecords/RecordingStation.h) ---
>[RecordingStation.cpp](TalosRecords/Source/TalosRecords/RecordingStation.cpp)  
>A game object with three states: idle, recording, and playing. Depending on its state, it either saves snapshots of the current referenced recordable objects or resimulates the previously snapshot ones.

>[IRecordable.h](TalosRecords/Source/TalosRecords/IRecordable.h)   
>An interface that allows objects to be referenced and participate in the recording system. It implements snapshotting and resimulation methods.

>[ItemSnapshot.h](TalosRecords/Source/TalosRecords/ItemSnapshot.h), 
>[PlayerCharacterSnapshot.h](TalosRecords/Source/TalosRecords/PlayerCharacterSnapshot.h), 
>[ItemPadSnapshot.h](TalosRecords/Source/TalosRecords/ItemPadSnapshot.h)  
>Data structures designed to snapshot specific recordable objects.

<br>

## Puzzle
>[Puzzle.h](TalosRecords/Source/TalosRecords/Puzzle.h) ---
>[Puzzle.cpp](TalosRecords/Source/TalosRecords/Puzzle.cpp)  
>An actor component that references different pieces of a puzzle, tracking the completion of objectives and ensuring objects behave as a cohesive whole.

>[PuzzleGate.h](TalosRecords/Source/TalosRecords/PuzzleGate.h) ---
>[PuzzleGate.cpp](TalosRecords/Source/TalosRecords/PuzzleGate.cpp)  
>A game object that obstructs the player's way out of a puzzle. It has two states: open and closed, set based on objective completion.

>[IObjective.h](TalosRecords/Source/TalosRecords/IObjective.h)  
>An interface that defines specific objectives for different puzzle objects.

<br>

## Other Game Objects & Player
>[Item.h](TalosRecords/Source/TalosRecords/Item.h) ---
>[Item.cpp](TalosRecords/Source/TalosRecords/Item.cpp)  
>Base class of an item that player can interact with and place into the world.  TODO rewrite


>[ItemPad.h](TalosRecords/Source/TalosRecords/ItemPad.h) --- 
>[ItemPad.cpp](TalosRecords/Source/TalosRecords/Item.cpp)  
>Interactable object on which items can be placed, or taken from.  TODO rewrite

>[Terminal.h](TalosRecords/Source/TalosRecords/Terminal.h) ---
>[Terminal.cpp](TalosRecords/Source/TalosRecords/Terminal.cpp)  
>Computer from which you access terminal.  TODO rewrite

>[PlayerCharacter.h](TalosRecords/Source/TalosRecords/PlayerCharacter.h) ---
>[PlayerCharacter.cpp](TalosRecords/Source/TalosRecords/PlayerCharacter.cpp)  
>Player functionality.  TODO rewrite

<br>

## Blueprint functionality
>The Blueprints functionality included in this project primarily enhances the prototype's appearance and completeness, but is not necessarily designed for extensibility.  
  
>One example is the typewriting effect for the Terminal widget. Since Blueprints don't support delays, I recommend rewriting this functionality in C++ for better compatibility and to reduce repetitive code.

<br>

## License
This project is licensed under the terms of the [MIT License](LICENSE).

Copyright © 2025 Matija Jambresic

For information about third-party assets used and their respective licenses, please see the [Third Party](THIRDPARTY.md) file.

In addition to the license file required by the MIT License, please include the Third Party file in all copies of this project.
