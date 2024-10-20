#ifndef EXT2_H
#define EXT2_H

#include <stdint.h>

typedef struct ext2_superblock {
  uint32_t inodes_count;
  uint32_t blocks_count;
  uint32_t r_blocks_count;
  uint32_t free_blocks_count;
  uint32_t free_inodes_count;
  uint32_t first_data_block;
  uint32_t log_block_size;
  uint32_t log_frag_size;
  uint32_t blocks_per_group;
  uint32_t frags_per_group;
  uint32_t inodes_per_group;
  uint32_t mtime;
  uint32_t wtime;
  uint16_t mnt_count;
  uint16_t max_mnt_count;
  uint16_t magic;
  uint16_t state;
  uint16_t errors;
  uint16_t minor_rev_level;
  uint32_t lastcheck;
  uint32_t checkinterval;
  uint32_t creator_os;
  uint32_t rev_level;
  uint16_t def_resuid;
  uint16_t def_resgid;
  /*uint32_t first_ino;*/
  /*uint16_t inode_size;*/
  /*uint16_t block_group_nr;*/
  /*uint32_t feature_compat;*/
  /*uint32_t feature_incompat;*/
  /*uint32_t feature_ro_compat;*/
  /*uint8_t uuid[16];*/
  /*char volume_name[16];*/
  /*char last_mounted[64];*/
  /*uint32_t algo_bitmap;*/
  /*uint8_t prealloc_blocks;*/
  /*uint8_t prealloc_dir_blocks;*/
  /*uint16_t padding;*/
  /*uint8_t journal_uuid[16];*/
  /*uint32_t journal_inum;*/
  /*uint32_t journal_dev;*/
  /*uint32_t last_orphan;*/
  /*uint32_t hash_seed[4];*/
  /*uint8_t def_hash_version;*/
  /*uint8_t padding2;*/
  /*uint16_t padding3;*/
  /*uint32_t default_mount_options;*/
  /*uint32_t first_meta_bg;*/
  /*uint8_t unused[760];*/
} __attribute__((packed)) ext2_superblock_t;

#endif
