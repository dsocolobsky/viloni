#ifndef _GDT_H_
#define _GDT_H_

#include "defines.h"

#define GDT_DESC_NULL 0
#define GDT_DESC_CODE 1
#define GDT_DESC_DATA 2

typedef struct gdt_descriptor {
    u16 length;
    u64 addr;
} __attribute__((__packed__)) gdt_descriptor;

typedef struct gdt_entry {
    u16 limit_0_15;
    u16 base_0_15;
    u8  base_16_23;
    u8  ac:1;
    u8  rw:1;
    u8  dc:1;
    u8  ex:1;
    u8  s:1;
    u8  dpl:2;
    u8  p:1;
    u8  limit_16_19:4;
    u8  avl:1;
    u8  l:1;
    u8  db:1;
    u8  g:1;
    u8  base_24_31;
} __attribute__((__packed__, aligned (8))) gdt_entry;

extern gdt_entry gdt[3];
extern gdt_descriptor GDT_DESC;

#endif