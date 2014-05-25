//-----------------------------------------------------------------------------
#include "Config.h"
#include <iostream>
//-----------------------------------------------------------------------------
bool Config::FullScreen = false;
bool Config::StartSlideShow = false;
QString Config::SessionDir = "";
//-----------------------------------------------------------------------------

bool Config::ParseArguments(int argc, char** argv)
{
	/*
	 *  ./cheesecake [--fullScreen] [--startSlideShow ] [--sessionDir DIR] [--help]
	 */
	QString help =  "\r\n";
			help += "Cheesecake :) - A simple tethering software for your photo booth.";
		    help += "\r\n";
			help += "(c) 2014 - Benjamin Grüdelbach";
		    help += "\r\n";
		    help += "\r\n";
			help += "This program is free software; you can redistribute it ";
		    help += "\r\n";
			help += "and/or modify it under the terms of the GNU General Public License";
		    help += "\r\n";
			help += "as published by the Free Software Foundation; either version 2 of the License,";
		    help += "\r\n";
			help += "or (at your option) any later version. This program is distributed in the hope that it will be useful,";
		    help += "\r\n";
			help += "but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.";
		    help += "\r\n";
			help += "See the GNU General Public License for more details. You should have received a copy of the ";
		    help += "\r\n";
			help += "GNU General Public License along with this program; if not, write to the ";
		    help += "\r\n";
			help += "Free Software Foundation, Inc.,51 Franklin Street, Fifth Floor; Boston, MA 02110-1301 USA.";
		    help += "\r\n";
		    help += "\r\n";
		    help += "USAGE:";
		    help += "\r\n";
			help += "./cheesecake [--fullScreen] [--startSlideShow ] [--sessionDir DIR] [--help]";
		    help += "\r\n";
		    help += "--fullscreen\t\t\tEnable fullscreen mode on startup";
		    help += "\r\n";
		    help += "--startSlideShow\t\tEnable slide show mode on startup";
		    help += "\r\n";
		    help += "--sessionDir\t\t\tStart a session in the specified directory";
		    help += "\r\n";
		    help += "--help\t\t\t\tPrints this text and terminates cheesecake";
		    help += "\r\n";
		    help += "";
	for(int i=1; i<argc; i++)
	{
		QString current(argv[i]);				
		if(current == "--help")
		{
			std::cout << help.toStdString() << std::endl;
			return false;
		}
		if(current == "--fullScreen")
		{
			std::cout << "Config: enable fullscreen mode" << std::endl;
			FullScreen = true;
		}

		if(current == "--startSlideShow")
		{
			std::cout << "Config: enable slide show" << std::endl;
			StartSlideShow = true;
		}

		//std::cout << argc << std::endl;
		//std::cout << i << std::endl;
		//std::cout << current.toStdString() << std::endl;
		if(current == "--sessionDir" && i+1 <= argc)
		{
			QString param = argv[i+1];	
			if(param != "" && 
			   !param.startsWith("--"))	
			{
				SessionDir = param;
				std::cout << "Config: setting session dir " 
					<< SessionDir.toStdString()
					<< std::endl;
			}
		}

		return true;
	}
}

//-----------------------------------------------------------------------------
//EOF
