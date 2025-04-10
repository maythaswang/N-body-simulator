#pragma once
inline constexpr char g_welcome_message[] =
    "+------------------------------------------------+\n"
    "| Welcome to Simple Real-Time N-body Simulator.  |\n"
    "+------------------------------------------------+\n";

inline constexpr char g_controls_help[] =
    "[HELP MENU]\n"
    "Enable GUI mode for some extra settings! (press N to toggle)\n"
    "   - Bloom intensity setting\n"
    "   - Gamma / Exposure settings\n"
    "   - Setup information page\n"
    "\n"
    "Window controls:\n"
    "   esc                             : exit simulation.\n"
    "   h                               : display controls on the console.\n"
    "   p                               : pause / continue the simulation.\n"
    "   o                               : toggle orbit / free-flying mode.\n"
    "   r                               : reset camera to origin.\n"
    "   k                               : toggle instancing.\n"
    "   f                               : toggle wireframe mode.\n"
    "   b                               : toggle bloom.\n"
    "   m                               : toggle mass-size.\n"
    "   c                               : toggle mass-color.\n"
    "   n                               : toggle GUI.\n"
    "\nps. mass-size and wireframe mode only shows when instancing is on\n"
    "\n"
    "Camera controls:\n"
    "   middle mouse drag + left shift  : pan the camera in the mouse drag direction.\n"
    "   middle mouse drag + left ctrl   : zoom in/out by dragging mouse forward and vice versa. (free-flying mode: move forward / backwards.)\n"
    "   middle mouse drag               : orbit the camera about the center in the mouse drag direction. (free-flying mode: rotate the center.)\n"
    ;

