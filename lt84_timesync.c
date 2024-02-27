/* Copyright (c) 2023 Danct12
 *
 * Based on HIDAPI sample program which is:
 *    Copyright (c) 2023 libusb/hidapi Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

#include <hidapi/hidapi.h>

#define MAX_STR 255

int main()
{
	unsigned char buf_send[65], buf_get[65];
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	time_t epoch = time(NULL);
	struct tm *timeinfo = localtime(&epoch);
	unsigned const int year = timeinfo->tm_year - 100,
		month = timeinfo->tm_mon + 1, 	// tm_mon range is 0-11
		day = timeinfo->tm_mday,
		hour = timeinfo->tm_hour,
		minutes = timeinfo->tm_min,
		seconds = timeinfo->tm_sec;
	int ret;

	hid_init();

	handle = hid_open(0x0c45, 0x8009, NULL);
	if (!handle) {
		printf("Unable to open device. Not plugged in or user does not have permissions.\n");
		hid_exit();
 		return 1;
	}

	hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer: %ls\n", wstr);

	hid_get_product_string(handle, wstr, MAX_STR);
	printf("Product: %ls\n", wstr);

	buf_send[0] = 0x04;
	buf_send[1] = 0x28;
	ret = hid_send_feature_report(handle, buf_send, 65);
	ret = hid_get_feature_report(handle, buf_get, 65);

	buf_send[2] = 0x5a;
	buf_send[3] = year; 	// Year (since 2000)
	buf_send[4] = month; 	// Month
	buf_send[5] = day; 	// Day
	buf_send[6] = hour; 	// Hour (24h format)
	buf_send[7] = minutes; 	// Minutes
	buf_send[8] = seconds; 	// Seconds
	ret = hid_send_feature_report(handle, buf_send, 65);
	ret = hid_get_feature_report(handle, buf_get, 65);

	hid_close(handle);
	hid_exit();

	if (ret < 0) {
		printf("Failed to set date and time.\n");
		return 1;
	}

	printf("Date/Time set to 20%02u-%02u-%02u %02u:%02u:%02u\n",
		year, month, day, hour, minutes, seconds);

	return 0;
}
