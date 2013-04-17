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

#include "debounce.h"

Debouncer::Debouncer():index(0) {
    for(int j=0; j<BUFFERSIZE; j++) {
        buffer[j]=0;
    }
}

int Debouncer::debounce(int input) {
    static int values[2];

    index=((index+1) % BUFFERSIZE);
    buffer[index]=input;

    values[0]=0;
    values[1]=0;
    // now count the buffer entries
    for(int j=0; j<BUFFERSIZE-1; j++) {
        values[ buffer[j]!=0?1:0 ]++;
    }

    return(values[0]>values[1]?0:1);
}
