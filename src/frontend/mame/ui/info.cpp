// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Aaron Giles, Nathan Woods
/***************************************************************************

    ui/info.cpp

    System and image info screens

***************************************************************************/

#include "emu.h"
#include "ui/menu.h"
#include "ui/info.h"
#include "ui/ui.h"
#include "softlist.h"

/*-------------------------------------------------
  menu_game_info - handle the game information
  menu
 -------------------------------------------------*/

ui_menu_game_info::ui_menu_game_info(mame_ui_manager &mui, render_container *container) : ui_menu(mui, container)
{
}

ui_menu_game_info::~ui_menu_game_info()
{
}

void ui_menu_game_info::populate()
{
	std::string tempstring;
	item_append(ui().game_info_astring(tempstring).c_str(), nullptr, MENU_FLAG_MULTILINE, nullptr);
}

void ui_menu_game_info::handle()
{
	// process the menu
	process(0);
}


/*-------------------------------------------------
  ui_menu_image_info - handle the image information
  menu
 -------------------------------------------------*/

ui_menu_image_info::ui_menu_image_info(mame_ui_manager &mui, render_container *container) : ui_menu(mui, container)
{
}

ui_menu_image_info::~ui_menu_image_info()
{
}

void ui_menu_image_info::populate()
{
	item_append(machine().system().description, nullptr, MENU_FLAG_DISABLE, nullptr);
	item_append("", nullptr, MENU_FLAG_DISABLE, nullptr);

	for (device_image_interface &image : image_interface_iterator(machine().root_device()))
		image_info(&image);
}

void ui_menu_image_info::handle()
{
	// process the menu
	process(0);
}


/*-------------------------------------------------
  image_info - display image info for a specific
  image interface device
-------------------------------------------------*/

void ui_menu_image_info::image_info(device_image_interface *image)
{
	if (image->exists())
	{
		// display device type and filename
		item_append(image->brief_instance_name(), image->basename(), 0, nullptr);

		// if image has been loaded through softlist, let's add some more info
		if (image->software_entry())
		{
			// display long filename
			item_append(image->longname(), "", MENU_FLAG_DISABLE, nullptr);

			// display manufacturer and year
			item_append(string_format("%s, %s", image->manufacturer(), image->year()).c_str(), "", MENU_FLAG_DISABLE, nullptr);

			// display supported information, if available
			switch (image->supported())
			{
				case SOFTWARE_SUPPORTED_NO:
					item_append(_("Not supported"), "", MENU_FLAG_DISABLE, nullptr);
					break;
				case SOFTWARE_SUPPORTED_PARTIAL:
					item_append(_("Partially supported"), "", MENU_FLAG_DISABLE, nullptr);
					break;
				default:
					break;
			}
		}
	}
	else
		item_append(image->brief_instance_name(), _("[empty]"), 0, nullptr);
	item_append("", nullptr, MENU_FLAG_DISABLE, nullptr);
}
