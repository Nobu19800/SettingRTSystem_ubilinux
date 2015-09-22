/*!
* @file  CalcOrientation.h
* @brief �����x�A�n���C�A�p���x����p���v�Z���邽�߂̃N���X
*
*/

#ifndef CalcOrientation_H
#define CalcOrientation_H

#include <coil/Time.h>
#include <coil/TimeMeasure.h>


/**
* @class CalcOrientation
*@brief �����x�A�n���C�A�p���x����p���v�Z���邽�߂̃N���X
*/
class CalcOrientation
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param ar �����x�Z���T�̌v���l�ł�IIR�t�B���^�̌W��
	* @param mr �n���C�Z���T�̌v���l�ł�IIR�t�B���^�̌W��
	* @param gr �W���C���Z���T�̌v���l�ł�IIR�t�B���^�̌W��
	* @param r ����t�B���^�̌W��
	*/
	CalcOrientation(double ar = 0.2, double mr = 0.2, double gr = 1.0, double r = 0.8);
	/**
	*@brief �p�����[�^�Đݒ�
	* @param ar �����x�Z���T�̌v���l�ł�IIR�t�B���^�̌W��
	* @param mr �n���C�Z���T�̌v���l�ł�IIR�t�B���^�̌W��
	* @param gr �W���C���Z���T�̌v���l�ł�IIR�t�B���^�̌W��
	* @param r ����t�B���^�̌W��
	*/
	void setParam(double ar = 0.2, double mr = 0.2, double gr = 1.0, double r = 0.8);
	/**
	*@brief ������
	*/
	void reset();
	/**
	*@brief �p���p���o(�����x�Z���T�A�n���C�Z���T�̌v���l�𗘗p)
	* @param ax �����x(X)
	* @param ay �����x(Y)
	* @param az �����x(Z)
	* @param mx �n���C(X)
	* @param my �n���C(Y)
	* @param mz �n���C(Z)
	* @param rx �p���p(X)
	* @param ry �p���p(Y)
	* @param rz �p���p(Z)
	*/
	void calc(double ax, double ay, double az, double mx, double my, double mz, double &rx, double &ry, double &rz);
	/**
	*@brief �p���p���o(�����x�Z���T�A�n���C�Z���T�A�W���C���Z���T�̌v���l�𗘗p)
	* @param ax �����x(X)
	* @param ay �����x(Y)
	* @param az �����x(Z)
	* @param mx �n���C(X)
	* @param my �n���C(Y)
	* @param mz �n���C(Z)
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	* @param avz �p���x(Z)
	* @param rx �p���p(X)
	* @param ry �p���p(Y)
	* @param rz �p���p(Z)
	*/
	void calc(double ax, double ay, double az, double mx, double my, double mz, double avx, double avy, double avz, double &rx, double &ry, double &rz);
	/**
	*@brief �����x�A�n���C�ɂ��p���p�̓��o
	* @param ax �����x(X)
	* @param ay �����x(Y)
	* @param az �����x(Z)
	* @param mx �n���C(X)
	* @param my �n���C(Y)
	* @param mz �n���C(Z)
	* @param rx �p���p(X)
	* @param ry �p���p(Y)
	* @param rz �p���p(Z)
	*/
	void calcOrientation(double ax, double ay, double az, double mx, double my, double mz, double &rx, double &ry, double &rz);
	/**
	*@brief �����x�Z���T�̌v���l��IIR�t�B���^�ɒʂ�
	* @param ax �����x(X)
	* @param ay �����x(Y)
	* @param az �����x(Z)
	*/
	void calcAcceleration(double ax, double ay, double az);
	/**
	*@brief �n���C�Z���T�̌v���l��IIR�t�B���^�ɒʂ�
	* @param mx �n���C(X)
	* @param my �n���C(Y)
	* @param mz �n���C(Z)
	*/
	void calcMagnetic(double mx, double my, double mz);
	/**
	*@brief �W���C���Z���T�̌v���l��IIR�t�B���^�ɒʂ�
	* @param avx �p���x(X)
	* @param avy �p���x(Y)
	* @param avz �p���x(Z)
	*/
	void calcGyro(double avx, double avy, double avz);
	/**
	*@brief ���Ԃ��X�V
	* @return �O��v���������ԂƂ̍���
	*/
	double updateTime();
private:

	double m_r;
	double m_ar, m_mr, m_gr;
	double last_ax, last_ay, last_az;
	double last_mx, last_my, last_mz;
	double last_avx, last_avy, last_avz;
	coil::TimeValue first_time;
	double last_time;
	int lv_count;
	double last_rx, last_ry, last_rz;
};



#endif
