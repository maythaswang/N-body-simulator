#pragma once
inline constexpr char g_welcome_message[] =
    "+------------------------------------------------+\n"
    "| Welcome to Simple Real-Time N-body Simulator.  |\n"
    "+------------------------------------------------+\n";

inline constexpr char g_controls_help[] =
    "Window controls:\n"
    "   esc                             : exit simulation.\n"
    "   h                               : display controls on the console.\n"
    "   p                               : pause / continue the simulation.\n"
    "   i                               : display setup log.\n"
    "   o                               : toggle orbit / free-flying mode.\n"
    "   middle mouse drag + left shift  : pan the camera in the mouse drag direction.\n"
    "   middle mouse drag + left ctrl   : zoom in/out by dragging mouse forward and vice versa. (free-flying mode: move forward / backwards.)\n"
    "   middle mouse drag               : orbit the camera about the center in the mouse drag direction. (free-flying mode: rotate the center.)\n";
