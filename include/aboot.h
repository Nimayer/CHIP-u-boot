/*
 * Copyright 2014 Broadcom Corporation.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <part.h>
#include <sparse_format.h>

#define ROUNDUP(x, y)	(((x) + ((y) - 1)) & ~((y) - 1))

typedef struct sparse_buffer {
	void	*data;
	u32	length;
	u32	repeat;
	u16	type;
} sparse_buffer_t;

typedef struct sparse_storage {
	unsigned int	block_sz;
	unsigned int	start;
	unsigned int	size;
	char		*name;

	unsigned int	(*write)(struct sparse_storage *storage, void *priv,
				 unsigned int offset, unsigned int size,
				 char *data);
} sparse_storage_t;


void fastboot_fail(const char *s);
void fastboot_okay(const char *s);

static inline int is_sparse_image(void *buf)
{
	sparse_header_t *s_header = (sparse_header_t *)buf;

	if ((le32_to_cpu(s_header->magic) == SPARSE_HEADER_MAGIC) &&
	    (le16_to_cpu(s_header->major_version) == 1))
		return 1;

	return 0;
}

void write_sparse_image(block_dev_desc_t *dev_desc,
		disk_partition_t *info, const char *part_name,
		void *data, unsigned sz);

void store_sparse_image(sparse_storage_t *storage, void *storage_priv,
			void *data);
