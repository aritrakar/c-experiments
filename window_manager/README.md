# Simple Windows Window Manager

Simple Windows Window Manager (SWWM) is a lightweight, easy-to-use desktop window manager for Windows that automatically arranges your windows in a vertical tile layout. It responds to window creation and destruction events to keep your workspace organized without manual intervention.

## Features

- **Automatic Vertical Tiling**: Automatically tiles windows vertically across the desktop as they are opened or closed.
- **Low Resource Usage**: Designed to be lightweight and efficient, minimizing CPU and memory usage.
- **Easy to Use**: Runs in the background with no user input required to manage window layout.

## Getting Started

### Prerequisites

- Windows 10 or later.
- Visual Studio 2019 or later (for building from source).

### Building from Source

Execute the following using the Native Tools Command Prompt for VS (I used the 2022 edition):

```bash
cd %USERPROFILE%

# Navigate to where you downloaded the code

# Compile the main file. Be sure to include user32.lib because it contains core Windows library functions (in this case, we're only interested in the functions related to the GUI)
cl swwm.c user32.lib

# Compile the DLL ("\c" for compile only)
cl /c wm_dll.c

# Link the DLL
link wm_dll.obj user32.lib /dll

# Run the window manager!
swwm.exe
```

## Usage
Once started, SWWM will automatically manage the layout of your windows. There are no additional steps required for basic usage. **To quit, press Ctrl + C.**

## Configuration (Optional)
SWWM currently runs with a default configuration that tiles windows vertically. Future versions may include customizable settings.

## Acknowledgments

The base code was obtained from this [video](https://www.youtube.com/watch?v=cuPirXZ6AWo).
