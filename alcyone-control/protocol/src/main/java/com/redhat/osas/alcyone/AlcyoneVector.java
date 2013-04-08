/*
    Copyright 2012- by Joseph B. Ottinger.

    This file is part of Alcyone.

    Alcyone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Alcyone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Alcyone.  If not, see <http://www.gnu.org/licenses/>.
*/

package com.redhat.osas.alcyone;

/**
 * User: jottinge
 * Date: 4/1/13
 * Time: 10:13 AM
 */
public enum AlcyoneVector {
    UP(1),
    DOWN(-1);

    private final int vector;

    AlcyoneVector(int vector) {
        this.vector = vector;
    }

    public int getMask() {
        return vector == -1 ? 0 : 1;
    }
}
