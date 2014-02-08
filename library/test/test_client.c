/* Copyright (c) 2014 William Orr <will@worrbase.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "config.h"
#include <glib.h>
#include "client.h"
#include <stdlib.h>

static void get_bg_test_func(gchar* term, gchar* colorfgbg, gchar* result) {
	g_setenv("TERM", term, TRUE);
	g_setenv("COLORFGBG", colorfgbg, TRUE);
	gboolean result_bool = (gboolean)atoi(result);

	wsh_client_reset_dark_bg();
	g_assert(result_bool == wsh_client_get_dark_bg());
}

static void get_bg(void) {
	const gchar* old_term = g_getenv("TERM");
	const gchar* old_colorfgfg = g_getenv("COLORFGBG");
	const gsize matrix_len = 10;

	gchar* matrix[10][3] = {
		{ "xterm", "", "0" },
		{ "screen.linux", "", "1" },
		{ "screen.xterm", "", "0" },
		{ "linux", "", "1" },
		{ "rxvt-unicode", "15;0", "1" },
		{ "rxvt-unicode", "0;15", "0" },
		{ "rxvt-unicode", "0;6", "1" },
		{ "rxvt-unicode", "0;7", "0" },
		{ "rxvt-unicode", "0;8", "1" },
		{ "putty", "", "1" }
	};

	for (gsize i = 0; i < matrix_len; i++)
		get_bg_test_func(matrix[i][0], matrix[i][1], matrix[i][2]);

	if (old_term)
		g_setenv("TERM", old_term, TRUE);
	if (old_colorfgfg)
		g_setenv("COLORFGBG", old_colorfgfg, TRUE);
}

int main(int argc, char** argv) {
	g_test_init(&argc, &argv, NULL);

	g_test_add_func("/Library/Client/TestGetBg", get_bg);

	return g_test_run();
}

