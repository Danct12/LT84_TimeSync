# Copyright (c) 2023 Danct12
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

CC=gcc

lt84_timesync: lt84_timesync.o
	$(CC) -o lt84_timesync lt84_timesync.o -lhidapi-hidraw

all: lt84_timesync
clean:
	rm *.o lt84_timesync

.PHONY: all clean
