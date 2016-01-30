/*
 * s5p6818-logger.c
 *
 * Copyright(c) 2007-2016 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <xboot.h>
#include <s5p6818/reg-uart.h>

static void logger_uart_init(void)
{
}

static void logger_uart_exit(void)
{
}

static ssize_t logger_uart_output(const char * buf, size_t count)
{
	ssize_t i;

	for(i = 0; i < count; i++)
	{
		while( !(read32(S5P6818_UART0_BASE + UART_UTRSTAT) & UART_UTRSTAT_TXFE) );
		write8(S5P6818_UART0_BASE + UART_UTXH, buf[i]);
	}
	return i;
}

static struct logger_t s5p6818_logger = {
	.name	= "logger-uart.0",
	.init	= logger_uart_init,
	.exit	= logger_uart_exit,
	.output	= logger_uart_output,
};

static __init void s5p6818_logger_init(void)
{
	register_logger(&s5p6818_logger);
}
core_initcall(s5p6818_logger_init);
