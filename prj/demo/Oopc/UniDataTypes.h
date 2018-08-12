/*
* UniDataTypes.h
* pxf.160611
*/
#ifndef _UNIDATATYPES_H_
#define _UNIDATATYPES_H_

// 基本数据类型定义
#ifndef FALSE
#define FALSE    0
#endif
#ifndef TRUE
#define TRUE     1
#endif
#ifndef NULL
#define NULL     ((void *)0)
#endif

// 整型
typedef char                  i8;
typedef short                 i16;
typedef long                  i32;
typedef long long             i64;

// 无符整型
typedef unsigned char         u8;
typedef unsigned short        u16;
typedef unsigned long         u32;
typedef unsigned long long    u64;

// 浮点
typedef float                 f32;
typedef double                f64;


// 0起始各位数据操作
typedef struct{
    u8 b0  : 1;
    u8     : 7;
}bit01;
typedef struct{
    u8 b01 : 2;
    u8     : 6;
}bit02;
typedef struct{
    u8 b02 : 3;
    u8     : 5;
}bit03;
typedef struct{
    u8 b03 : 4;
    u8     : 4;
}bit04;
typedef struct{
    u8 b04 : 5;
    u8     : 3;
}bit05;
typedef struct{
    u8 b05 : 6;
    u8     : 2;
}bit06;
typedef struct{
    u8 b06 : 7;
    u8     : 1;
}bit07;
// 1起始各位数据操作
typedef struct{
    u8     : 1;
    u8 b1  : 1;
    u8     : 6;
}bit11;
typedef struct{
    u8     : 1;
    u8 b12 : 2;
    u8     : 5;
}bit12;
typedef struct{
    u8     : 1;
    u8 b13 : 3;
    u8     : 4;
}bit13;
typedef struct{
    u8     : 1;
    u8 b14 : 4;
    u8     : 3;
}bit14;
typedef struct{
    u8     : 1;
    u8 b15 : 5;
    u8     : 2;
}bit15;
typedef struct{
    u8     : 1;
    u8 b16 : 6;
    u8     : 1;
}bit16;
typedef struct{
    u8     : 1;
    u8 b17 : 7;
}bit17;
// 2起始各位数据操作
typedef struct{
    u8     : 2;
    u8 b2  : 1;
    u8     : 5;
}bit21;
typedef struct{
    u8     : 2;
    u8 b23 : 2;
    u8     : 4;
}bit22;
typedef struct{
    u8     : 2;
    u8 b24 : 3;
    u8     : 3;
}bit23;
typedef struct{
    u8     : 2;
    u8 b25 : 4;
    u8     : 2;
}bit24;
typedef struct{
    u8     : 2;
    u8 b26 : 5;
    u8     : 1;
}bit25;
typedef struct{
    u8     : 2;
    u8 b27 : 6;
}bit26;
// 3起始各位数据操作
typedef struct{
    u8     : 3;
    u8 b3  : 1;
    u8     : 4;
}bit31;
typedef struct{
    u8     : 3;
    u8 b34 : 2;
    u8     : 3;
}bit32;
typedef struct{
    u8     : 3;
    u8 b35 : 3;
    u8     : 2;
}bit33;
typedef struct{
    u8     : 3;
    u8 b36 : 4;
    u8     : 1;
}bit34;
typedef struct{
    u8     : 3;
    u8 b37 : 5;
}bit35;
// 4起始各位数据操作
typedef struct{
    u8     : 4;
    u8 b4  : 1;
    u8     : 3;
}bit41;
typedef struct{
    u8     : 4;
    u8 b45 : 2;
    u8     : 2;
}bit42;
typedef struct{
    u8     : 4;
    u8 b46 : 3;
    u8     : 1;
}bit43;
typedef struct{
    u8     : 4;
    u8 b47 : 4;
}bit44;
// 5起始各位数据操作
typedef struct{
    u8     : 5;
    u8 b5  : 1;
    u8     : 2;
}bit51;
typedef struct{
    u8     : 5;
    u8 b56 : 2;
    u8     : 1;
}bit52;
typedef struct{
    u8     : 5;
    u8 b57 : 3;
}bit53;
// 6起始各位数据操作
typedef struct{
    u8     : 6;
    u8 b6  : 1;
    u8     : 1;
}bit61;
typedef struct{
    u8     : 6;
    u8 b67 : 2;
}bit62;
// 7起始各位数据操作
typedef struct{
    u8     : 7;
    u8 b7  : 1;
}bit71;

// 位操作数据
typedef struct{
    union{
        bit01 bit01;
        bit02 bit02;
        bit03 bit03;
        bit04 bit04;
        bit05 bit05;
        bit06 bit06;
        bit07 bit07;

        bit11 bit11;
        bit12 bit12;
        bit13 bit13;
        bit14 bit14;
        bit15 bit15;
        bit16 bit16;
        bit17 bit17;

        bit21 bit21;
        bit22 bit22;
        bit23 bit23;
        bit24 bit24;
        bit25 bit25;
        bit26 bit26;

        bit31 bit31;
        bit32 bit32;
        bit33 bit33;
        bit34 bit34;
        bit35 bit35;

        bit41 bit41;
        bit42 bit42;
        bit43 bit43;
        bit44 bit44;

        bit51 bit51;
        bit52 bit52;
        bit53 bit53;

        bit61 bit61;
        bit62 bit62;

        bit71 bit71;
    };
}tBits;
typedef struct{
    union{
        u8 byte;
        tBits bits;
    };
}tByte;
typedef struct{
    union{
        u16 word;
        struct{
            tByte bytel;
            tByte byteh;
        };
    };
}tWord;
typedef struct{
    union{
        u32 dword;
        struct{
            tWord wordl;
            tWord wordh;
        };
    };
}tDWord;
typedef struct{
    union{
        u64 qword;
        struct{
            tDWord dwordl;
            tDWord dwordh;
        };
    };
}tQWord;

#endif
