# Cube3D (42)

> A basic 3D raycasting engine written in C using **MiniLibX (Linux or macOS)**.  
> MiniLibX **is not included in this repository**, so you must install it on your system before compiling.

---

## ✨ Features

- Raycasting engine (vertical projection per screen column)  
- Directional wall textures (NO, SO, WE, EA)  
- Floor & ceiling colors (F/C)  
- Player movement & rotation  
- Collision detection  
- Map parsing & validation  
- `.cub` configuration format (textures, colors, map layout)  

---

## 🔧 Build

### 1) Install MiniLibX

#### **Linux (X11)**

```bash
sudo apt update
sudo apt install -y build-essential libx11-dev libxext-dev
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
```

Then in your Makefile, link with:
```
-Lminilibx-linux -lmlx -lXext -lX11 -lm
```

#### **macOS**

```bash
brew install minilibx
```

Or manually:

```bash
git clone https://github.com/42Paris/minilibx-mac.git
cd minilibx-mac
make
```

Then link with:
```
-framework OpenGL -framework AppKit -lmlx
```

---

### 2) Compile the project

```bash
make
```

Cleaning:

```bash
make clean
make fclean
make re
```

Executable: **`cub3D`**

---

## ▶️ Usage

```bash
./cub3D maps/good/<mapname>.cub
```

### Controls

| Key | Action |
|-----|--------|
| W / ↑ | Move forward |
| S / ↓ | Move backward |
| A | Strafe left |
| D | Strafe right |
| ← / → | Rotate view |
| ESC | Quit |

---

## 🗺️ Map Format

A valid `.cub` file contains:

```
NO path/to/north.xpm
SO path/to/south.xpm
WE path/to/west.xpm
EA path/to/east.xpm

F R,G,B
C R,G,B

<map>
```

### Map rules

- Must be rectangular  
- Must be surrounded by walls (`1`)  
- Allowed characters: `0`, `1`, `N`, `S`, `E`, `W`  
- Exactly one player start position  
- Valid RGB colors (0–255)  

---

## 🗂️ Project Structure

```
Cube3D/
├─ Makefile
├─ README.md
├─ headers/
│   ├─ cube3D.h
│   └─ libft.h
├─ maps/
│   ├─ bad/
│   ├─ good/
│   └─ perso.cub
├─ textures/
│   ├─ direction/
│   ├─ east.xpm
│   ├─ north.xpm
│   ├─ south.xpm
│   └─ west.xpm
└─ src/
    ├─ events/
    ├─ get_next_line/
    ├─ init/
    ├─ libft/
    ├─ parsing/
    ├─ render/
    ├─ utils/
    └─ main.c
```

---

## 🧠 Implementation Notes

- Raycasting per vertical stripe  
- Wall hit detection and texture mapping  
- Fisheye correction  
- Collision detection  
- Init → parse → load textures → render loop  
- Input handled through MiniLibX hooks  

---

## 👤 Author

- Swann — @xSwann
