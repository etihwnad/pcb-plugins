/*!
 * \file dxfout.c
 * \author Copyright (C) 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Plug-in for PCB to export specified elements to a dxf file as
 * XREFs.
 *
 * Compile like this:\n
 * \n
 * gcc -Ipath/to/pcb/src -Ipath/to/pcb -O2 -shared dxfout.c -o dxfout.so
 * \n\n
 * The resulting dxfout.so file should go in $HOME/.pcb/plugins/\n
 * \n
 * \warning Be very strict in compiling this plug-in against the exact pcb
 * sources you compiled/installed the pcb executable (i.e. src/pcb) with.\n
 *
 * Usage: DxfoutElement(Refdes)\n
 * Usage for lazy users: DxfoutE(Refdes)\n
 * Usage for spoiled and lazy users: DE(Refdes)\n
 * If no argument is passed, no action is carried out.\n
 * \n
 * <hr>
 * This program is free software; you can redistribute it and/or modify\n
 * it under the terms of the GNU General Public License as published by\n
 * the Free Software Foundation; either version 2 of the License, or\n
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,\n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License\n
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc.,\n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n
 */


#include <stdio.h>
#include <math.h>

#include "global.h"
#include "data.h"
#include "hid.h"
#include "misc.h"
#include "create.h"
#include "rtree.h"
#include "undo.h"
#include "set.h"
#include "error.h"


/*!
 * \brief Export the specified elements.
 *
 * Usage: DxfoutElement(Refdes)\n
 * Usage for lazy users: DxfoutE(Refdes)\n
 * Usage for spoiled and lazy users: DE(Refdes)\n
 * If no argument is passed, no action is carried out.
 */
static int
dxfout_element (int argc, char **argv, int x, int y)
{
        if (argc == 0 || strcasecmp (argv[0], "") == 0)
        {
                Message ("WARNING: in DxfoutElement the argument should be a non-empty string value.\n");
                return 0;
        }
        else
        {
                SET_FLAG (NAMEONPCBFLAG, PCB);
                ELEMENT_LOOP(PCB->Data);
                {
                        if (NAMEONPCB_NAME(element)
                                && strcmp (argv[0], NAMEONPCB_NAME(element)) == 0)
                        {
                                /*! \todo Add code here. */
                        }
                }
                END_LOOP;
                gui->invalidate_all ();
                IncrementUndoSerialNumber ();
                return 0;
        };
}


static HID_Action dxfout_action_list[] =
{
        {"DxfoutElement", NULL, dxfout_element, "Export the specified element", NULL},
        {"DxfoutE", NULL, dxfout_element, "Export the specified element", NULL},
        {"DE", NULL, dxfout_element, "Export the specified element", NULL}
};


REGISTER_ACTIONS (dxfout_action_list)


void
pcb_plugin_init()
{
        register_dxfout_action_list();
}


/* EOF */