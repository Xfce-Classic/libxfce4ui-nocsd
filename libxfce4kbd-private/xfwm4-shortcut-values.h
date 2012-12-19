/*
 * Copyright (c) 2008 Stephan Arts <stephan@xfce.org>
 * Copyright (c) 2008 Jannis Pohlmann <jannis@xfce.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <glib.h>

typedef struct _ShortcutTemplate ShortcutTemplate;

struct _ShortcutTemplate
{
  const gchar *name;
  const gchar *feature;
  const gchar *shortcut;
};

const ShortcutTemplate xfwm4_shortcut_values[] = {
  { N_("Window operations menu"), "popup_menu_key", NULL },
  { N_("Up"), "up_key", NULL },
  { N_("Down"), "down_key", NULL },
  { N_("Left"), "left_key", NULL },
  { N_("Right"), "right_key", NULL },
  { N_("Cancel"), "cancel_key", NULL },
  { N_("Cycle windows"), "cycle_windows_key", NULL },
  { N_("Cycle windows (Reverse)"), "cycle_reverse_windows_key", NULL },
  { N_("Switch window for same application"), "switch_window_key", NULL },
  { N_("Switch application"), "switch_application_key", NULL },
  { N_("Close window"), "close_window_key", NULL },
  { N_("Maximize window horizontally"), "maximize_horiz_key", NULL },
  { N_("Maximize window vertically"), "maximize_vert_key", NULL },
  { N_("Maximize window"), "maximize_window_key", NULL },
  { N_("Hide window"), "hide_window_key", NULL },
  { N_("Move window"), "move_window_key", NULL },
  { N_("Resize window"), "resize_window_key", NULL },
  { N_("Shade window"), "shade_window_key", NULL },
  { N_("Stick window"), "stick_window_key", NULL },
  { N_("Raise window"), "raise_window_key", NULL },
  { N_("Lower window"), "lower_window_key", NULL },
  { N_("Raise or lower window"), "raiselower_window_key", NULL },
  { N_("Fill window"), "fill_window_key", NULL },
  { N_("Fill window horizontally"), "fill_horiz_key", NULL },
  { N_("Fill window vertically"), "fill_vert_key", NULL },
  { N_("Toggle above"), "above_key", NULL },
  { N_("Toggle fullscreen"), "fullscreen_key", NULL },
  { N_("Move window to upper workspace"), "move_window_up_workspace_key", NULL },
  { N_("Move window to bottom workspace"), "move_window_down_workspace_key", NULL },
  { N_("Move window to left workspace"), "move_window_left_workspace_key", NULL },
  { N_("Move window to right workspace"), "move_window_right_workspace_key", NULL },
  { N_("Move window to previous workspace"), "move_window_prev_workspace_key", NULL },
  { N_("Move window to next workspace"), "move_window_next_workspace_key", NULL },
  { N_("Move window to workspace 1"), "move_window_workspace_1_key", NULL, },
  { N_("Move window to workspace 2"), "move_window_workspace_2_key", NULL, },
  { N_("Move window to workspace 3"), "move_window_workspace_3_key", NULL, },
  { N_("Move window to workspace 4"), "move_window_workspace_4_key", NULL, },
  { N_("Move window to workspace 5"), "move_window_workspace_5_key", NULL, },
  { N_("Move window to workspace 6"), "move_window_workspace_6_key", NULL, },
  { N_("Move window to workspace 7"), "move_window_workspace_7_key", NULL, },
  { N_("Move window to workspace 8"), "move_window_workspace_8_key", NULL, },
  { N_("Move window to workspace 9"), "move_window_workspace_9_key", NULL, },
  { N_("Move window to workspace 10"), "move_window_workspace_10_key", NULL, },
  { N_("Move window to workspace 11"), "move_window_workspace_11_key", NULL, },
  { N_("Move window to workspace 12"), "move_window_workspace_12_key", NULL, },
  { N_("Tile window to the top"), "tile_up_key", NULL, },
  { N_("Tile window to the bottom"), "tile_down_key", NULL, },
  { N_("Tile window to the left"), "tile_left_key", NULL, },
  { N_("Tile window to the right"), "tile_right_key", NULL, },
  { N_("Show desktop"), "show_desktop_key", NULL },
  { N_("Upper workspace"), "up_workspace_key", NULL },
  { N_("Bottom workspace"), "down_workspace_key", NULL },
  { N_("Left workspace"), "left_workspace_key", NULL },
  { N_("Right workspace"), "right_workspace_key", NULL },
  { N_("Previous workspace"), "prev_workspace_key", NULL },
  { N_("Next workspace"), "next_workspace_key", NULL },
  { N_("Workspace 1"), "workspace_1_key", NULL, },
  { N_("Workspace 2"), "workspace_2_key", NULL, },
  { N_("Workspace 3"), "workspace_3_key", NULL, },
  { N_("Workspace 4"), "workspace_4_key", NULL, },
  { N_("Workspace 5"), "workspace_5_key", NULL, },
  { N_("Workspace 6"), "workspace_6_key", NULL, },
  { N_("Workspace 7"), "workspace_7_key", NULL, },
  { N_("Workspace 8"), "workspace_8_key", NULL, },
  { N_("Workspace 9"), "workspace_9_key", NULL, },
  { N_("Workspace 10"), "workspace_10_key", NULL, },
  { N_("Workspace 11"), "workspace_11_key", NULL, },
  { N_("Workspace 12"), "workspace_12_key", NULL, },
  { N_("Add workspace"), "add_workspace_key", NULL },
  { N_("Add adjacent workspace"), "add_adjacent_workspace_key", NULL },
  { N_("Delete last workspace"), "del_workspace_key", NULL },
  { N_("Delete active workspace"), "del_active_workspace_key", NULL },
  { NULL, NULL, NULL }
};
