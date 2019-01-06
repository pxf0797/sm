#!usr/bin/env python3
#coding: utf-8
#sm.py

import sys
import datetime

class smTemplate:
    """文件生成脚本
    使用方法：python sm.py stateMachineName stateList
    脚本至少需要3个参数，状态机名称stateMachineName根据需要选取
    stateList是多个参数，目前配置状态机时至少需要给定1个状态"""
    __encoding = 'gb2312' #'utf-8' 'gb2312' ''
    __fileName = ' '
    __sourceName = ' '
    __headerName = ' '
    __timeFormatFull = datetime.datetime.now().strftime('%Y/%m/%d %H:%M:%S')
    __timeFormatShort = datetime.datetime.now().strftime('%y%m%d')
    __fileComments = {'@copyright':':Copyright(C), 2019, pxf, person.',
                      '@file':':',
                      '@author':':pxf',
                      '@version':':v1.0',
                      '@date':':'+__timeFormatFull,
                      '@brief':':',
                      '@others':':',
                      '@history':':'+__timeFormatShort+' pxf 初建立',
    }
    __functionComments = {'@function':':',
                      '@description':':',
                      '@input':':',
                      '@output':':',
                      '@calls':':',
                      '@calledBy':':',
                      '@others':':',
    }
    __functionComments2 = {'名称':':无',
                      '输入':':无',
                      '输出':':无',
                      '其他':':无',
    }

    __fCommentsOrder = ('@copyright','@file','@author','@version','@date','@brief','@others','@history')
    __funcCommentsOrder = ('@function','@description','@input','@output','@calls','@calledBy','@others')
    __funcCommentsOrder2 = ('名称','输入','输出','其他')
    
    __sta_list = []

    #def __init__(self,s):
    #    """根据输入参数初始化参数

    #    主要功能：1.生成文件名称"""
    #    self.__fileName = s
    #    self.__sourceName = s + ".c"
    #    self.__headerName = s + '.h'
    def __init__(self,sys_args):
        """根据输入参数初始化参数

        主要功能：1.生成文件名称"""
        self.__fileName = sys_args[1]
        self.__sourceName = sys_args[1] + ".c"
        self.__headerName = sys_args[1] + '.h'
        
        self.__sta_list = sys_args[2:]
        #print(self.__sta_list)

    #========================================================
    # 文件基础生成函数
    #--------------------------------------------------------
    def generateFileHeadComment(self,name):
        """生成文件头注释"""
        #set filename for every file generate
        self.__fileComments['@file'] = ':'+name
        comments = ('/**************************************************************************\n')
        #find max length of string
        maxLen = 0
        for s in self.__fCommentsOrder:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__fCommentsOrder:
            alignSpaceAmount = maxLen - len(k) + 4
            alignSpace = alignSpaceAmount * ' '
            comments += ('* '+ k + alignSpace + self.__fileComments[k] + '\n')
        comments += ('***************************************************************************/\n\n')
        return comments

    def generateFileEndComment(self):
        """生成文件尾注释"""
        return ("/**************************** Copyright(C) pxf ****************************/\n")

    def generateFunctionComment(self,name):
        """生成函数头注释"""
        #set function name for every function generate
        self.__functionComments['@function'] = ':'+name
        comments = ('/***********************************************************\n')
        #find max length of string
        maxLen = 0
        for s in self.__funcCommentsOrder:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__funcCommentsOrder:
            alignSpaceAmount = maxLen - len(k) + 4
            alignSpace = alignSpaceAmount * ' '
            comments += ('* '+ k + alignSpace + self.__functionComments[k] + '\n')
        comments += ('***********************************************************/\n')
        return comments

    def generateFunctionComment2(self,name,input,output,others):
        """生成函数头注释类型2"""
        #set function name for every function generate
        self.__functionComments2['名称'] = ':'+name
        self.__functionComments2['输入'] = ':'+input
        self.__functionComments2['输出'] = ':'+output
        self.__functionComments2['其他'] = ':'+others
        comments = ('')
        #find max length of string
        maxLen = 0
        for s in self.__funcCommentsOrder2:
            if(len(s) > maxLen):
                maxLen = len(s)
        #align space generate line
        for k in self.__funcCommentsOrder2:
            alignSpaceAmount = maxLen - len(k) + 1
            alignSpace = alignSpaceAmount * ' '
            if(k == '名称'):
                comments += ('/*'+ k + alignSpace + self.__functionComments2[k] + '\n')
            else:
                comments += ('* '+ k + alignSpace + self.__functionComments2[k] + '\n')
        comments += ('***********************************************/\n')
        return comments
    #========================================================


    #========================================================
    # 状态机专用生成函数
    #--------------------------------------------------------
    def generateSmStaList(self):
        """生成状态机状态序列"""
        #find max length of string
        maxLen = len('#define %s_LIST(_)' %self.__fileName.upper())
        for sta in self.__sta_list:
            sta_len = len('    _(%s, %s)' %(self.__fileName,sta))
            if(sta_len > maxLen):
                maxLen = sta_len
        alignSpaceAmount = maxLen - len('#define %s_LIST(_)' %self.__fileName.upper()) + 4
        alignSpace = alignSpaceAmount * ' '
        comments = ('/*状态机%s状态序列定义\n* 注意其中%s_init,%s_default未在此定义，默认会给出\n' %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('***********************************************/\n')
        comments += ('#define %s_LIST(_)' %self.__fileName.upper())
        comments += alignSpace+'\\\n'
        for sta in self.__sta_list:
            alignSpaceAmount = maxLen - len('    _(%s, %s)' %(self.__fileName,sta)) + 4
            alignSpace = alignSpaceAmount * ' '
            if(sta == self.__sta_list[-1]):
                comments += ('    _(%s, %s)\n' %(self.__fileName,sta))
            else:
                comments += ('    _(%s, %s)' %(self.__fileName,sta))
                comments += alignSpace+'\\\n'
        #comments += ("\n"*1)
        return comments
        
    def generateSmDeclaration(self):
        """生成状态机声明"""
        comments = ('/*状态机%s声明\n* 已给出状态记录next,及上一状态last，其他参数需自行添加\n' %self.__fileName)
        comments += ('***********************************************/\n')
        comments += ('SMDC(%s, %s_LIST){\n' %(self.__fileName,self.__fileName.upper()))
        comments += ('    sta next; // 运行状态记录\n')
        comments += ('    sta last; // 上一状态记录\n')
        comments += ('    // TODO\n};')
        return comments
        
    def generateSmDefine(self):
        """生成状态机定义"""
        comments = ('/*状态机%s定义\n* 配置状态机相关处理状态\n' %self.__fileName)
        comments += ('***********************************************/\n')
        comments += ('SMDF(%s, %s_LIST);\n' %(self.__fileName,self.__fileName.upper()))
        return comments
        
    def generateSmStaActionDefine(self):
        """生成状态机各状态操作定义"""
        comments = self.generateFunctionComment2(self.__fileName+'_act_init()',self.__fileName+'Rec - 状态记录参数指针','无','初始状态操作函数')
        comments += ("void %s_act_init(void *%sRec){\n" %(self.__fileName,self.__fileName))
        comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('    // TODO\n\n')
        comments += ('    hRec->next = %s_sta_default;\n' %self.__fileName)
        comments += ('    hRec->last = %s_sta_init;\n}\n' %self.__fileName)
        comments += ("\n"*1)
        comments += self.generateFunctionComment2(self.__fileName+'_act_default()',self.__fileName+'Rec - 状态记录参数指针','无','默认状态操作函数')
        comments += ("void %s_act_default(void *%sRec){\n" %(self.__fileName,self.__fileName))
        comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('    // TODO\n\n')
        comments += ('    hRec->next = %s_sta_default;\n' %self.__fileName)
        comments += ('    hRec->last = %s_sta_default;\n}\n' %self.__fileName)
        comments += ("\n"*1)
        for sta in self.__sta_list:
            comments += self.generateFunctionComment2(self.__fileName+'_act_'+sta+'()',self.__fileName+'Rec - 状态记录参数指针','无','状态'+sta+'操作函数')
            comments += ("void %s_act_%s(void *%sRec){\n" %(self.__fileName,sta,self.__fileName))
            comments += ("    h%sRec hRec = (h%sRec)%sRec;\n\n" %(self.__fileName,self.__fileName,self.__fileName))
            comments += ('    // TODO\n\n')
            comments += ('    hRec->next = %s_sta_default;\n' %self.__fileName)
            comments += ('    hRec->last = %s_sta_%s;\n}\n' %(self.__fileName,sta))
            comments += ("\n"*1)
        return comments
        
    def generateSmUseExample(self):
        """生成状态机使用示例"""
        comments = ('/*状态机%s使用示例：\n* 当前状态机已在SMDF中定义出实体%s，需要做的只是让其运行起来\n' %(self.__fileName,self.__fileName))
        comments += ('* 状态机运行方式有两种直接给时钟驱动的SMR和使用自定义记录状态后进驱动的SMRE\n')
        comments += ('***********************************************\n')
        comments += ('* SMR方式\n')
        comments += ('***********************************************\n')
        comments += ('void test(void){\n')
        comments += ('    while(1){SMR(%s);};\n}\n' %self.__fileName)
        comments += ('***********************************************\n')
        comments += ('* SMRE方式\n')
        comments += ('***********************************************\n')
        comments += ('void test2(void){\n')
        comments += ('    static %sRec %sRunRec = {%s_sta_init};\n' %(self.__fileName,self.__fileName,self.__fileName))
        comments += ('    while(1){SMRE(%s, %sRunRec);};\n}\n' %(self.__fileName,self.__fileName))
        comments += ('***********************************************/\n')
        return comments
    #========================================================


    #========================================================
    # 模板生成源文件及头文件控制函数
    #--------------------------------------------------------
    def createSource(self):
        """生成源文件"""
        fh = open(self.__sourceName,mode = 'w',encoding=self.__encoding)
        self.__fileComments['@brief'] = ':状态机'+self.__fileName+'定义及各状态动作定义源文件'
        cm = self.generateFileHeadComment(self.__sourceName)
        cm += ("#include \"%s\"\n" %self.__headerName)
        cm += ("\n"*1)
        cm += self.generateSmDefine()
        cm += ("\n"*2)
        cm += self.generateSmStaActionDefine()
        cm += self.generateFileEndComment()
        cm += ("\n"*1)
        fh.write(cm)
        fh.close()

    def createHeader(self):
        """生成头文件"""
        fh = open(self.__headerName,mode = 'w',encoding=self.__encoding)
        self.__fileComments['@brief'] = ':状态机'+self.__fileName+'声明及状态机使用示例头文件'
        cm = self.generateFileHeadComment(self.__headerName)
        cm += "#ifndef %s_H_\n" %self.__fileName.upper()
        cm += "#define %s_H_\n" %self.__fileName.upper()
        cm += ("\n/*头文件包含*/\n")
        cm += ('#include "sm.h"\n')
        cm += ("\n"*1)
        cm += self.generateSmUseExample()
        cm += ("\n"*2)
        cm += self.generateSmStaList()
        cm += ("\n"*2)
        cm += self.generateSmDeclaration()
        cm += ("\n"*2)
        cm += "#endif /*%s_H_*/\n\n" %self.__fileName.upper()
        cm += self.generateFileEndComment()
        fh.write(cm)
        fh.close()

    def createTemplate(self):
        """模板生成"""
        self.createSource()
        self.createHeader()
    #========================================================

if __name__ == '__main__':
    if len(sys.argv) <= 2:
        sys.stderr.write("please input no less than 3 parameter !!!")
    else:
        sm = smTemplate(sys.argv)
        sm.createTemplate()