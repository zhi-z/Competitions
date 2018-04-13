/*******************************************************************************
* �ļ��� : ultrasonic.h
* ʵ�ֹ���:
* �汾     ����            ����            ˵��
* V1.0     Njh          2015/08/5      ��ʼ�汾

* ����   : MCU: STC89c52     ����: 11.0592   MHz
           
*******************************************************************************/

#ifndef __ultrasonic_H_
#define __ultrasonic_H_

#include "intrins.h"
#include "reg52.h"

sbit Trig = P3^5;
sbit Echo = P3^3;

extern int ultrasonic();	  //���������������س�����������ֵ


#endif