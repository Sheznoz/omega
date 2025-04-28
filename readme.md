# Technical Outline

### 1. Core Architecture

- Server

    <br>
    
- Networking

    <br>

- Model
    - Sectors consist of systems
    - Systems consist of planets
    - Planets consist of something. Unsure how to break up planets
    <br>
    - 

    <br>

- Command Parser

    <br>

- Game Loop
    - One single event loop for both in and out of operations
    - All actions occur simultaneously, maybe every 5 seconds
    - Each 'tick' will be evaluate both player and NPC commands at the same time, but the order in which they occur will have to do with some kind of 'speed' equation

    <br>

### 2. Data Structures

   - 'Rooms'
   - Players
   - Items/Gear
   - NPCS: friendly and hostile

<br>

### 3. Technologies

   - Programming language: probably c++ but can pivot later if this turns out to be too hard to work with
   - Libraries?

### 4. Game Flow/Loop

   - Real-time, but light enough on tickrate (16? maybe less? need to experiment)
   - Todo

<br>
