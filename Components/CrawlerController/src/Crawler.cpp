/*!
* @file  Crawler.cpp
* @brief �N���[���[����̃N���X
*
*/
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Crawler.h"


/**
*@brief �N���[���[����̃N���X�̃R���X�g���N�^
* @param frontRangeSensor �O���ɋ����Z���T�����t����ꍇ��true
* @param backRangeSensor ����ɋ����Z���T�����t����ꍇ��true
* @param bias �l���傫���Ȃ�قǐ��񂵂₷���Ȃ�p�����[�^
* @param frontDistance ����^�����J�n�����Q���܂ł̍Œ�����
* @param backDistance ����^�����J�n�����Q���܂ł̍ŒZ����
* @param filter �]���ɉ���^��������p�����[�^
* @param rotCorVal �p���̕ω����������ɍR�������ɉ�]����␳�ւ̌W��
*/
Crawler::Crawler(int frontRangeSensor, int backRangeSensor, double bias, double frontDistance, double backDistance, double filter, double rotCorVal)
{
	setParam(frontRangeSensor, backRangeSensor, bias, frontDistance, backDistance, filter, rotCorVal);
}


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
void Crawler::setParam(int frontRangeSensor, int backRangeSensor, double bias, double frontDistance, double backDistance, double filter, double rotCorVal)
{
	m_frontRangeSensor = frontRangeSensor;
	m_backRangeSensor = backRangeSensor;
	m_bias = bias;
	m_frontDistance = frontDistance;
	m_backDistance = backDistance;
	m_filter = filter;

	m_rotCorVal = rotCorVal;
}

/**
*@brief ������
*/
void Crawler::reset()
{
	crawlerVol0 = 0;
	crawlerVol1 = 0;

	last_bias0 = 0;
	last_bias1 = 0;

	lv_count = 0;

	first_time = coil::TimeValue(coil::gettimeofday());
}

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
double Crawler::calc(double &input_crawlerVol0, double &input_crawlerVol1, double rn0, double rn1, double rn2, double rn3, double rz)
{
	double drz = calcAV(rz);
	
	const double lv = 0.01;

	if(sqrt(crawlerVol0*crawlerVol0) < lv && sqrt(crawlerVol1*crawlerVol1) < lv)
	{
		input_crawlerVol0 = 0;
		input_crawlerVol1 = 0;
		return 0;
	}

	input_crawlerVol0 = crawlerVol0;
	input_crawlerVol1 = crawlerVol1;

	double trans_speed = (input_crawlerVol0 + input_crawlerVol1)/2;
	double rot_speed = (input_crawlerVol0 - input_crawlerVol1)/2;

	if(m_frontRangeSensor==1 || m_backRangeSensor==1)
	{
		double p = 0.1;
		double sqrt_ts = sqrt(trans_speed*trans_speed);
		double sqrt_rs = sqrt(rot_speed*rot_speed);

		Crawler_Direction dir = C_Stop;
		
		if(sqrt_ts < p && sqrt_rs < p)
		{
			dir = C_Stop;
		}
		else if(trans_speed > 0 && sqrt_rs < p)
		{
			dir = C_Forword;
		}
		else if(trans_speed < 0 && sqrt_rs < p)
		{
			dir = C_Back;
		}
		else if(sqrt_ts < p && rot_speed > 0 )
		{
			dir = C_Right;
		}
		else if(sqrt_ts < p && rot_speed < 0 )
		{
			dir = C_Left;
		}
		else if(trans_speed > 0 && rot_speed < 0 )
		{
			dir = C_Forword_Left;
		}
		else if(trans_speed > 0 && rot_speed > 0 )
		{
			dir = C_Forword_Right;
		}
		else if(trans_speed < 0 && rot_speed < 0 )
		{
			dir = C_Back_Left;
		}
		else if(trans_speed < 0 && rot_speed > 0 )
		{
			dir = C_Back_Right;
		}

		if(m_frontRangeSensor==1)
		{
			if(rn0 > m_frontDistance)
				rn0 = m_frontDistance;
			if(rn1 > m_frontDistance)
				rn1 = m_frontDistance;
			if(rn0 < m_backDistance)
				rn0 = m_backDistance;
			if(rn1 < m_backDistance)
				rn1 = m_backDistance;

			double bias0 = (m_frontDistance-rn0)/(m_frontDistance-m_backDistance);
			double bias1 = (m_frontDistance-rn1)/(m_frontDistance-m_backDistance);

			

			if(last_bias0 > bias0)
			{
				bias0 = (1-m_filter)*last_bias0 + m_filter*bias0;
			}
			if(last_bias1 > bias1)
			{
				bias1 = (1-m_filter)*last_bias1 + m_filter*bias1;
			}

			last_bias0 = bias0;
			last_bias1 = bias1;
			

			double trans_bias = 0;
			bool rot_type;
			if(bias0 < bias1)
			{
				trans_bias = bias1;
				rot_type = false;
			}
			else
			{
				trans_bias = bias0;
				rot_type = true;
			}

			if(dir == C_Forword || dir == C_Forword_Left || dir == C_Forword_Right)
			{
				trans_speed *= (1-trans_bias*trans_bias*trans_bias);
				if(trans_speed < 0)
					trans_speed = 0;
				
				if(rot_type)
					rot_speed -= trans_bias*trans_bias*trans_bias*m_bias;
				else
					rot_speed += trans_bias*trans_bias*trans_bias*m_bias;

				input_crawlerVol0 = trans_speed + rot_speed;
				input_crawlerVol1 = trans_speed - rot_speed;
				
			}
		}


		
	}

	const double pm = 0.01;
	
	double dfv = input_crawlerVol0 - input_crawlerVol1;
	if(sqrt(dfv*dfv) < pm)
	{
		input_crawlerVol0 += drz*m_rotCorVal;
		input_crawlerVol1 -= drz*m_rotCorVal;
	}

	return trans_speed;

}

/**
*@brief �p���p�̕ω��ʌv�Z
* @param rz Z���̎p���p
* @return �p���p�̕ω���
*/
double Crawler::calcAV(double rz)
{
	coil::TimeValue t0(coil::gettimeofday());
	double now_time = (double)(t0-first_time);
	double drz = 0;
	if(lv_count > 0)
	{
		double dt = now_time - last_time;
		drz = (rz - last_rz)/dt;
	}
	last_rz = rz;
	last_time = now_time;

	lv_count += 1;

	return drz;
}

/**
*@brief �e���[�^�[�ւ̏o�̖͂ڕW�l�ݒ�
* @param v0 �����[�^�[�h���C�o�̃f���[�e�B�[��
* @param v1 �E���[�^�[�h���C�o�̃f���[�e�B�[��
*/
void Crawler::setVol(double v0, double v1)
{
	crawlerVol0 = v0;
	crawlerVol1 = v1;
}