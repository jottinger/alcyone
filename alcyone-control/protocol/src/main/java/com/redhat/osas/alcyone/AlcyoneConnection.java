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

import java.io.IOException;

/**
 * User: jottinge
 * Date: 4/3/13
 * Time: 10:00 AM
 */
public interface AlcyoneConnection {
    void connect() throws IOException;

    void changeOctave(AlcyoneVector vector) throws IOException;

    void changeTransposition(AlcyoneVector vector) throws IOException;

    void changeChannel(AlcyoneVector vector) throws IOException;

    void midiReset() throws IOException;

    void reset() throws IOException;

    AlcyoneStatus getStatus() throws IOException;

    void disconnect();
}
