/*
Copyright 2013 Michael Curran <mick@nvaccess.org>.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 2.1, as published by
    the Free Software Foundation.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
This license can be found at:
http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
*/

#ifndef SPEECHPLAYER_UTILS_H
#define SPEECHPLAYER_UTILS_H

#include <float.h>

inline double calculateValueAtFadePosition(double oldVal, double newVal, double curFadeRatio) {
	if(_isnan(newVal)) return oldVal;
	return oldVal+((newVal-oldVal)*curFadeRatio);
}

#endif
