/*
 * Copyright (C) 2023 Jean-Pierre Miceli <jean-pierre.miceli@heig-vd.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <iostream>
#include <cstdlib>

#include "container.hpp"

#define EMISO_IMAGE_PATH     "/mnt/ME/"

namespace emiso {
namespace daemon {

Container::Container() {};

Container::~Container() {};


int Container::create(std::string imageName)
{
    char cmd[80];

    std::cout << "[EMISO] Creating container from '" << imageName << "'" << std::endl;

    sprintf(cmd, "/root/injector %s", imageName.c_str());

    std::cout << "[EMISO] injection cmd: " << cmd << std::endl;

    int rc = std::system(cmd);

    return 0;
}


} // daemon
} // emiso
