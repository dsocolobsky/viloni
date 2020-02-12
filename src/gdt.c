#include "gdt.h"

gdt_entry gdt[3] = {
    [GDT_DESC_NULL] = (gdt_entry) {
        (u16)   0x0000, /* limit[0:15]  */
        (u16)   0x0000, /* base[0:15]   */
        (u8)    0x00,   /* base[23:16]  */
        (u8)    0x00,   /* ac           */
        (u8)    0x00,   /* rw           */
        (u8)    0x00,   /* dc           */
        (u8)    0x00,   /* ex           */
        (u8)    0x00,   /* s            */
        (u8)    0x00,   /* dpl          */
        (u8)    0x00,   /* p            */
        (u8)    0x00,   /* limit[16:19] */
        (u8)    0x00,   /* avl          */
        (u8)    0x00,   /* l            */
        (u8)    0x00,   /* db           */
        (u8)    0x00,   /* g            */
        (u8)    0x00,   /* base[31:24]  */
    },

    [GDT_DESC_CODE] = (gdt_entry) {
        (u16)   0xFFFF, /* limit[0:15]  */
        (u16)   0x0000, /* base[0:15]   */
        (u8)    0x00,   /* base[23:16]  */
        (u8)    0x00,   /* ac           */
        (u8)    0x01,   /* rw           */
        (u8)    0x00,   /* dc           */
        (u8)    0x01,   /* ex           */
        (u8)    0x01,   /* s            */
        (u8)    0x00,   /* dpl          */
        (u8)    0x01,   /* p            */
        (u8)    0xF,   /* limit[16:19] */
        (u8)    0x00,   /* avl          */
        (u8)    0x01,   /* l            */
        (u8)    0x00,   /* db           */
        (u8)    0x01,   /* g            */
        (u8)    0x00,   /* base[31:24]  */
    },

    [GDT_DESC_DATA] = (gdt_entry) {
        (u16)   0xFFFF, /* limit[0:15]  */
        (u16)   0x0000, /* base[0:15]   */
        (u8)    0x00,   /* base[23:16]  */
        (u8)    0x00,   /* ac           */
        (u8)    0x01,   /* rw           */
        (u8)    0x00,   /* dc           */
        (u8)    0x00,   /* ex           */
        (u8)    0x01,   /* s            */
        (u8)    0x00,   /* dpl          */
        (u8)    0x01,   /* p            */
        (u8)    0xF,   /* limit[16:19] */
        (u8)    0x00,   /* avl          */
        (u8)    0x01,   /* l            */
        (u8)    0x00,   /* db           */
        (u8)    0x01,   /* g            */
        (u8)    0x00,   /* base[31:24]  */
    },
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (u64) &gdt
};
