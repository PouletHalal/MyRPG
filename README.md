# MyRPG 🎮

A fully customizable RPG game developed in C using CSFML - Our final CSFML project for the first year at EPITECH. The game is built with customization at its core, allowing you to modify virtually every aspect through configuration files without touching the source code.

## 🌟 Features

- **Completely written in C** using CSFML framework
- **Extensive Configuration System** - Every game element can be modified through external files without recompilation
- **Dynamic game elements** - All customizable through config files:
  - Maps and tilesets (CSV-based for easy editing)
  - Character animations and sprite sheets
  - Complete UI layout and styling
  - NPCs behavior patterns and dialog trees
  - Items, stats, and inventory system
  - Inter-map portals and travel system
  - Monster stats, behavior, and spawn patterns
  - Spell effects and combat mechanics
  - Particle systems and visual effects

## ⚙️ Configuration System

Our game is designed with maximum customization in mind. Everything is controlled through external configuration files:

### Map System
- **Map Format**: CSV files created with Tiled Map Editor
- **Layer System**: Multiple customizable layers including:
  - Decoration layer
  - Collision layer
  - Interaction layer
  - Custom layers for special mechanics
- Example of a decoration layer configuration:

![Decoration Layer Example](https://github.com/user-attachments/assets/39d09bad-f8e8-45b6-8eb8-8febeb9e387c)

### Visual Customization
#### Tilesets
- Fully modifiable tile mappings
- Custom collision properties
- Dynamic texture loading
![Tileset Example](https://github.com/user-attachments/assets/3f8a00e5-6b10-49e4-9d64-824f94813d7b)

### Gameplay Configuration
All of these elements can be modified through simple configuration files:
- **Customizable animations** Framerate, textures...
- **UI System**: Layout, style, and behavior of all interface elements
- **NPC System**: Custom behaviors, movement patterns, and interaction zones
- **Dialog System**: Branching conversations and conditional responses
- **Item System**: Custom properties, effects, and statistics
- **Portal System**: Custom transition points and destination mapping
- **Combat System**: Custom monster stats, attack patterns, and AI behavior
- **Spell System**: Custom effects, damage values, and visual feedback
- **Particle System**: Custom effects, colors, and behavior patterns

## 🎮 Game Preview

### Interface and Systems
Each of these systems is fully configurable through external files:
### Animations:
![Animation Config](https://github.com/user-attachments/assets/611d9e63-80a4-46c8-bedc-580832008d1b)
### NPC
![UI Preview 1](https://github.com/user-attachments/assets/712d77cd-8b46-4ebe-a37b-91fb6762bb41)
### Item
![UI Preview 2](https://github.com/user-attachments/assets/8839801c-1f07-4b67-894c-454884984e1b)
### Portal
![UI Preview 3](https://github.com/user-attachments/assets/bdb3cfec-7006-48ab-9f20-8e7de4934107)
### Monster
![Game Systems](https://github.com/user-attachments/assets/925dfa95-c202-4671-bfaa-9f33476f2d7d)
### Particle
![Gameplay Elements](https://github.com/user-attachments/assets/15031dce-7383-417f-a91d-031b3d7fb53a)
### Spell
![Combat System](https://github.com/user-attachments/assets/b3e41d0d-f0c3-4a30-b899-54470a51a0e8)
### UI
![Inventory System](https://github.com/user-attachments/assets/bf42f6b4-ec03-4aee-9e3a-e476f2ef3159)

### Gameplay Screenshots
![Gameplay 1](https://github.com/user-attachments/assets/4f50bd64-e226-4313-990b-d760247cca44)
![Gameplay 2](https://github.com/user-attachments/assets/59b89f07-3ecd-432a-8da8-c4b4b7ee30e8)
![Gameplay 3](https://github.com/user-attachments/assets/3aca1bc2-b977-45b8-b90e-fe0d597ee8ff)
![Gameplay 4](https://github.com/user-attachments/assets/98eb2199-9dd9-46ae-a91d-7831efd87bf3)

## 🎨 Assets
All game assets can be downloaded from [itch.io](https://itch.io). These assets can be easily swapped out by modifying the corresponding configuration files.

## 🚀 Installation
1. Install the CSFML Library
2. Run `make` to compile the game

## 💻 Usage
1. Run the game with `./my_rpg`
2. Customize any aspect by modifying the configuration files in the `config` directory
3. Changes take effect immediately upon restarting the game - no recompilation needed!
