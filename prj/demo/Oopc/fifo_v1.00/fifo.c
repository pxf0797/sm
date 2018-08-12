/*************************************************
 * Copyright © person
 * File name    : fifo.c
 * Author       : pxf
 * Version      : v1.0
 * Created on   : 2018/3/9
 * Description  : 本文件内定义了队列类；
 *                队列主要提供以下几个功能：
 *                1.队列存储数据使用push函数
 *                2.队列使用堆栈功能弹出后进数据使用pop函数
 *                3.队列获取先进数据使用fout函数
 *                4.队列还提供某类数据删除功能使用del函数
 * Others       : 无
 * History      : 180309 pxf 初次建立
 ************************************************/

#include "fifo.h"

// 文件内函数声明-------------------------------------------------
static int16 Fifo_push(hFifo t, void *data);
static int16 Fifo_pop(hFifo t, void *data);
static int16 Fifo_fout(hFifo t, void *data);
static int16 Fifo_del(hFifo t, void *data, void *fifoObjTempBuff);
static hFifo Fifo_init(hFifo cthis, void *listBuffer, int16 listBuffSize, int16 fifoObjSize);

/*************************************************
 * Function     : Fifo_push()
 * Description  : 函数压入存储对象到队列中
 * Calls        : 无
 * Called By    : Fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中存储对象，大小由t->fifoObjSize定义
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，当前只返回TRUE/FALSE
 * Others       : 无
 ************************************************/
static int16 Fifo_push(hFifo t, void *data)
{
    int16 rtv = TRUE;
    int8 *srcPtr = (int8 *)data;
    int8 *desPtr = NULL;
    int16 i = 0;

    if (t->currLen < t->saveObjMaxLen)
    {
        // 计算存储位置并存储
        desPtr = (t->listBuffer + (t->top * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++)
        {
            *desPtr++ = *srcPtr++;
        }

        // 更新标志
        t->currLen++;
        t->top++;
        if (t->top >= t->saveObjMaxLen)
        {
            t->top = 0;
        }
        else
        {
            ;
        }

        rtv = TRUE;
    }
    else
    {
        rtv = FALSE;
    }

    return rtv;
}

/*************************************************
 * Function     : Fifo_pop()
 * Description  : 函数从对列中弹出最一个进入对列中的存储对象
 * Calls        : 无
 * Called By    : Fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，当前只返回TRUE/FALSE
 * Others       : 无
 ************************************************/
static int16 Fifo_pop(hFifo t, void *data)
{
    int16 rtv = TRUE;
    int8 *srcPtr = NULL;
    int8 *desPtr = (int8 *)data;
    int16 i = 0;

    if (t->currLen > 0)
    {
        // 计算存储位置并存储
        srcPtr = (t->listBuffer + (t->top * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++)
        {
            *desPtr++ = *srcPtr++;
        }

        // 更新标志
        t->currLen--;
        t->top--;
        if (t->top <= 0)
        {
            t->top = (t->fifoObjSize - 1);
        }
        else
        {
            ;
        }

        rtv = TRUE;
    }
    else
    {
        rtv = FALSE;
    }

    return rtv;
}

/*************************************************
 * Function     : Fifo_fout()
 * Description  : 函数从对列中获取第一个进入对列中的存储对象
 * Calls        : 无
 * Called By    : Fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，当前只返回TRUE/FALSE
 * Others       : 无
 ************************************************/
static int16 Fifo_fout(hFifo t, void *data)
{
    int16 rtv = TRUE;
    int8 *srcPtr = NULL;
    int8 *desPtr = (int8 *)data;
    int16 i = 0;

    if (t->currLen > 0)
    {
        // 计算存储位置并存储
        srcPtr = (t->listBuffer + (t->bottom * t->fifoObjSize));
        for (i = 0; i < t->fifoObjSize; i++)
        {
            *desPtr++ = *srcPtr++;
        }

        // 更新标志
        t->currLen--;
        t->bottom++;
        if (t->bottom >= t->saveObjMaxLen)
        {
            t->bottom = 0;
        }
        else
        {
            ;
        }

        rtv = TRUE;
    }
    else
    {
        rtv = FALSE;
    }

    return rtv;
}

/*************************************************
 * Function     : Fifo_del()
 * Description  : 函数从队列中删除某类存储对象
 * Calls        : 无
 * Called By    : Fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 *                fifoObjTempBuff - 用于删除存储对象临时提供的缓存空间
 * Output       : TRUE/FALSE
 * Return       : 返回值返回类型为int16，当前只返回TRUE/FALSE
 * Others       : 无
 ************************************************/
static int16 Fifo_del(hFifo t, void *data, void *fifoObjTempBuff)
{
    int16 rtv = TRUE;
    int8 *srcPtr = (int8 *)data;
    int8 *desPtr = (int8 *)fifoObjTempBuff;
    int16 i = 0;
    int16 j = t->currLen;
    int16 lastMaxLen = t->currLen;

    if (t->currLen > 0)
    {
        // 全队列查找数据，找到就删除
        for (j = t->currLen; j > 0; j--)
        {
            // 读取数据
            if (TRUE == t->fout(t, fifoObjTempBuff))
            {
                // 判断数据是否相同，相同则删除，不同则存回队列
                srcPtr = (int8 *)data;
                desPtr = (int8 *)fifoObjTempBuff;
                for (i = 0; i < t->fifoObjSize; i++)
                {
                    if (*desPtr++ != *srcPtr++)
                    {
                        break;
                    }
                    else
                    {
                        ;
                    }
                }

                if (i < t->fifoObjSize)
                {
                    // 非查找数据存回队列
                    if (TRUE != t->push(t, fifoObjTempBuff))
                    {
                        rtv = FALSE;
                    }
                    else
                    {
                        rtv = TRUE;
                    }
                }
                else
                {
                    rtv = TRUE;
                }
            }
            else
            {
                rtv = FALSE;
            }

            if (FALSE == rtv)
            {
                break;
            }
            else
            {
                ;
            }
        }

        // 判断是否找到并删除数据，并返回操作结果
        if ((TRUE == rtv) && (t->currLen < lastMaxLen))
        {
            rtv = TRUE;
        }
        else
        {
            rtv = FALSE;
        }
    }
    else
    {
        rtv = FALSE;
    }

    return rtv;
}

/*************************************************
 * Function     : Fifo_init()
 * Description  : 函数为队列类进行参数初始化
 * Calls        : 无
 * Called By    : Fifo_ctor()
 * Input        : t - 队列类指针
 *                data - 存储到队列中对象，大小由t->fifoObjSize定义
 * Output       : cthis/OOPC_NULL
 * Return       : 返回值返回类型为hFifo，当前只返回cthis/OOPC_NULL
 * Others       : 无
 ************************************************/
static hFifo Fifo_init(hFifo cthis, void *listBuffer, int16 listBuffSize, int16 fifoObjSize)
{
    cthis->listBuffer = (int8 *)listBuffer;
    cthis->listBuffSize = listBuffSize;
    cthis->fifoObjSize = fifoObjSize;

    cthis->saveObjMaxLen = (cthis->listBuffSize / cthis->fifoObjSize);

    return cthis;
}

/*************************************************
 * Function     : Fifo_ctor()
 * Description  : 队列类实例化时的构造函数
 * Calls        : 无
 * Called By    : Fifo_new()
 * Input        : cthis - 队列类指针
 * Output       : cthis/OOPC_NULL
 * Return       : 返回值返回类型为hFifo，当前只返回cthis/OOPC_NULL
 * Others       : 无
 ************************************************/
CC(Fifo)
{
    FS(init, Fifo_init);
    FS(push, Fifo_push);
    FS(pop, Fifo_pop);
    FS(fout, Fifo_fout);
    FS(del, Fifo_del);

    cthis->listBuffer = NULL;
    cthis->listBuffSize = 0;
    cthis->fifoObjSize = 0;

    cthis->saveObjMaxLen = 0;
    cthis->currLen = 0;
    cthis->top = 0;
    cthis->bottom = 0;

    return cthis;
}

/*************************************************
 * Function     : Fifo_dtor()
 * Description  : 队列类内存释放时的析构函数
 * Calls        : 无
 * Called By    : Fifo_delete()
 * Input        : cthis - 队列类指针
 * Output       : OOPC_TRUE/OOPC_FALSE
 * Return       : 返回值返回类型为int，当前只返回OOPC_TRUE/OOPC_FALSE
 * Others       : 无
 ************************************************/
CD(Fifo)
{
    return OOPC_TRUE;
}
