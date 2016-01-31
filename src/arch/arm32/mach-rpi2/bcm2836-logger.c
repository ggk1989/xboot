/*
 * bcm2836-logger.c
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
#include <bcm2836/reg-uart.h>

struct logger_pdata_t {
	physical_addr_t phys;
	virtual_addr_t  virt;
};

static void logger_init(struct logger_t * logger)
{
	struct logger_pdata_t * pdat = (struct logger_pdata_t *)logger->priv;
	write32(pdat->virt + 0x30, (1 << 0) | (1 << 8) | (1 << 9));
}

static void logger_output(struct logger_t * logger, const char * buf, int count)
{
	struct logger_pdata_t * pdat = (struct logger_pdata_t *)logger->priv;
	int i;

	for(i = 0; i < count; i++)
	{
		while(read8(pdat->virt + 0x18) & (0x1 << 5));
		write8(pdat->virt + 0x00, buf[i]);
	}
}

static struct logger_pdata_t pdata = {
	.phys	= BCM2836_UART0_BASE,
};

static struct logger_t logger = {
	.name	= "logger-pl110-uart.0",
	.init	= logger_init,
	.output	= logger_output,
	.priv	= &pdata,
};

static __init void bcm2836_logger_init(void)
{
	pdata.virt = phys_to_virt(pdata.phys);
	register_logger(&logger);
}
core_initcall(bcm2836_logger_init);