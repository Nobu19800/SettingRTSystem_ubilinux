/*!
* @file  Crawler.h
* @brief �N���[���[����̃N���X
*
*/

#ifndef CRAWLER_H
#define CRAWLER_H


#include <stdio.h>
#include <coil/Time.h>
#include <coil/TimeMeasure.h>

enum Crawler_Direction { C_Forword, C_Forword_Left, C_Forword_Right, C_Left, C_Right, C_Back, C_Back_Left, C_Back_Right, C_Stop };



/**
* @class Crawler
*@brief �N���[���[����̃N���X
*/
class Crawler
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param frontRangeSensor �O���ɋ����Z���T�����t����ꍇ��true
	* @param backRangeSensor ����ɋ����Z���T�����t����ꍇ��true
	* @param bias �l���傫���Ȃ�قǐ��񂵂₷���Ȃ�p�����[�^
	* @param frontDistance ����^�����J�n�����Q���܂ł̍Œ�����
	* @param backDistance ����^�����J�n�����Q���܂ł̍ŒZ����
	* @param filter �]���ɉ���^��������p�����[�^
	* @param rotCorVal �p���̕ω����������ɍR�������ɉ�]����␳�ւ̌W��
	*/
	Crawler(int frontRangeSensor = 1, int backRangeSensor = 1, double bias = 1.0, double frontDistance = 0.5, double backDistance = 0.1, double filter = 0.05,  double rotCorVal = 0.3);
	/**
	*@brief �e�p�����[�^�Đݒ�
	* @param frontRangeSensor �O���ɋ����Z���T�����t����ꍇ��true
	* @param backRangeSensor ����ɋ����Z���T�����t����ꍇ��true
	* @param bias �l���傫���Ȃ�قǐ��񂵂₷���Ȃ�p�����[�^
	* @param frontDistance ����^�����J�n�����Q���܂ł̍Œ�����
	* @param backDistance ����^�����J�n�����Q���܂ł̍ŒZ����
	* @param filter �]���ɉ���^��������p�����[�^
	* @param rotCorVal �p���̕ω����������ɍR�������ɉ�]����␳�ւ̌W��
	*/
	void setParam(int frontRangeSensor = 1, int backRangeSensor = 1, double bias = 1.0, double frontDistance = 0.5, double backDistance = 0.1, double filter = 0.05, double rotCorVal = 15);
	/**
	*@brief ������
	*/
	void reset();
	/**
	*@brief ���[�^�[�ւ̏o�͌v�Z
	* @param input_crawlerVol0 �����[�^�[�h���C�o�̃f���[�e�B�[��
	* @param input_crawlerVol1 �E���[�^�[�h���C�o�̃f���[�e�B�[��
	* @param rn0 �����Z���T(�E�O)�̌v���l
	* @param rn1 �����Z���T(���O)�̌v���l
	* @param rn2 �����Z���T(�E��)�̌v���l
	* @param rn3 �����Z���T(����)�̌v���l
	* @return ���i���x
	*/
	double calc(double &input_crawlerVol0, double &input_crawlerVol1, double rn0 = 0, double rn1 = 0, double rn2 = 0, double rn3 = 0, double rz = 0);
	/**
	*@brief �p���p�̕ω��ʌv�Z
	* @param rz Z���̎p���p
	* @return �p���p�̕ω���
	*/
	double calcAV(double rz);
	/**
	*@brief �e���[�^�[�ւ̏o�̖͂ڕW�l�ݒ�
	* @param v0 �����[�^�[�h���C�o�̃f���[�e�B�[��
	* @param v1 �E���[�^�[�h���C�o�̃f���[�e�B�[��
	*/
	void setVol(double v0, double v1);
private:
	int m_frontRangeSensor, m_backRangeSensor;
	double m_bias, m_frontDistance, m_backDistance, m_filter, m_rotCorVal;
	double crawlerVol0;
	double crawlerVol1;

	double last_bias0;
	double last_bias1;


	double last_rz;

	int lv_count;
	coil::TimeValue last_time, first_time;
};
#endif
