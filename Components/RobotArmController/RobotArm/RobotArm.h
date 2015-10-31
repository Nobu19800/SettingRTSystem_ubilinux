/*!
* @file  RobotArm.h
* @brief サインスマート製4自由度ロボットアーム制御クラス
*
*/


#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

using namespace Eigen;



enum MoveType { Joint = 0, Point = 1, };

/**
* @class TargetPos
*@brief 手先位置(もしくは関節角度)の目標位置、初期位置、到達時間等を格納するクラス
*/
class TargetPos
{
public:
	/**
	*@brief コンストラクタ
	*/
	TargetPos();
	double end_time;
	double time;
	MoveType type;
	Vector3d start_pos;
	Vector3d target_pos;
	double start_joint_pos[4];
	double target_joint_pos[4];
	double target_theta;
	double start_theta; 

	/**
	*@brief 目標手先位置を設定
	* @param t 到達時間(0以下に設定した場合は初期位置と目標位置との距離から自動的に計算)
	* @param t_p 手先位置
	* @param the 手先姿勢
	*/
	void setPoint(double t, Vector3d t_p, double the);
	/**
	*@brief 目標関節角度を設定
	* @param t 到達時間(0以下に設定した場合は初期関節角度と目標関節角度との距離から自動的に計算)
	* @param t_p 関節角度
	*/
	void setJointPos(double t, double *t_p);
	/**
	*@brief 初期手先位置を設定
	* @param s_p 初期手先位置
	* @param the 初期手先姿勢
	* @param maxSpeedCartesianTrans 手先の最大速度
	* @param maxSpeedCartesianRot 手先姿勢の最大速度
	* @param minTime 到達時間の最小値
	*/
	void setStartPoint(Vector3d s_p, double the, double maxSpeedCartesianTrans, double maxSpeedCartesianRot, double minTime);
	/**
	*@brief 目標関節角度を設定
	* @param t 到達時間
	* @param t_p 関節角度
	*/
	void setStartJointPos(double *s_p, double *maxSpeedJoint, double minTime);

	
};


/**
* @class RobotArm
*@brief サインスマート製4自由度ロボットアーム制御クラス
*/
class RobotArm
{
public:
	/**
	*@brief コンストラクタ
	*/
	RobotArm();
	/**
	*@brief 手先位置取得
	*@param the 関節角度
	* @return 手先位置
	*/
	Vector3d calcKinematics(double *the);
	/**
	*@brief 関節角度を入力
	* @param t1 関節角度(関節1)
	* @param t2 関節角度(関節2)
	* @param t3 関節角度(関節3)
	* @param t4 関節角度(関節4)
	*/
	void setAngle(double t1, double t2, double t3, double t4);
	/**
	*@brief ヤコビ行列取得
	*@param the 関節角度
	* @return ヤコビ行列
	*/
	Matrix3d calcJacobian(double *the);
	/**
	*@brief 手先速度から関節角速度を取得
	* @param v 手先速度
	* @return 関節角速度
	*/
	Vector3d calcJointVel(Vector3d v);
	/**
	*@brief 関節角速度の入力から関節角度を更新
	* @param v1 関節角速度(関節1)
	* @param v2 関節角速度(関節2)
	* @param v3 関節角速度(関節3)
	* @param v4 関節角速度(関節4)
	*/
	void updatePos(double v1, double v2, double v3, double v4);
	/**
	*@brief 関節角度のホームポジションを設定
	* @param o1 関節角速度(関節1)
	* @param o2 関節角速度(関節2)
	* @param o3 関節角速度(関節3)
	* @param o4 関節角速度(関節4)
	*/
	void setOffset(double o1, double o2, double o3, double o4);
	/**
	*@brief 目標位置のリストの0番目に初期位置、到達時間を設定
	*/
	void setTargetPos();
	/**
	*@brief 更新
	* @param st 刻み幅
	*/
	void update(double st);
	/**
	*@brief グリッパーを開く
	*/
	void openGripper();
	/**
	*@brief グリッパーを閉じる
	*/
	void closeGripper();
	/**
	*@brief 目標位置追加
	* @param p 目標手先位置
	* @param the 目標手先姿勢
	* @param T 到達時間
	*/
	void addTargetPos(Vector3d p, double the, double T);
	/**
	*@brief 目標関節角度追加
	* @param p 目標関節角度
	* @param T 到達時間
	*/
	void addTargetJointPos(double *p, double T);


	double l[4],lh,lf;
	double m[4],mh,mf;
	double wi, wf;
	double hi, hf;
	double rh;
	Vector3d *jl;
	Vector3d jh;
	Vector3d jf;
	Vector3d *pl;
	Vector3d ph;
	Vector3d pf;
	double hw;

	double theta[4];
	double homeTheta[4];

	double dt;
	//double endTime;
	double time;
	//Vector3d targetPoint;
	//Vector3d startPoint;

	double offset[4];

	double Kp;
	double Kjp;

	double gripperPos;

	std::vector<TargetPos> targetPoints;
	TargetPos targetPoint;

	/**
	*@brief ベースオフセットの設定
	* @param bo ベースオフセット
	*/
	void setBaseOffset(double *bo);
	/**
	*@brief 手先最大速度の設定
	* @param msc 手先最大速度
	*/
	void setMaxSpeedCartesian(Vector3d msc);
	/**
	*@brief 関節最大角速度の設定
	* @param msj 関節最大角速度
	*/
	void setMaxSpeedJoint(double *msj);
	/**
	*@brief 手先のソフトリミット値の設定
	* @param usl ソフトリミットの最大値
	* @param lsl ソフトリミットの最小値
	*/
	void setSoftLimitCartesian(Vector3d usl, Vector3d lsl);
	/**
	*@brief 一時停止
	*/
	void pause();
	/**
	*@brief 再開
	*/
	void resume();
	/**
	*@brief 停止
	*/
	void stop();
	/**
	*@brief 関節のソフトリミット値の設定
	* @param usl ソフトリミットの最大値
	* @param lsl ソフトリミットの最小値
	*/
	void setSoftLimitJoint(double *usl, double *lsl);
	/**
	*@brief ホームポジションに移動
	*/
	void goHomePosition();
	/**
	*@brief ホームポジションの設定
	* @param jp ホームポジション
	*/
	void setHomePosition(double *jp);
	/**
	*@brief サーボをオン、オフにする
	* @param state trueでオン、falseでオフ
	*/
	void setSerbo(bool state);
	/**
	*@brief 関節、手先位置がソフトリミット内かを判定する
	*@param the 関節角度
	*@return 範囲内の場合true
	*/
	bool judgeSoftLimitJoint(double *the);
	/**
	*@brief 手先位置がソフトリミット内かを判定する
	*@param pos 手先位置
	*@return 範囲内の場合true
	*/
	bool judgeSoftLimitPos(Vector3d pos);
	


	double baseOffset[12];
	Vector3d maxSpeedCartesian;
	double maxSpeedJoint[4];
	Vector3d softUpperLimitCartesian;
	Vector3d softLowerLimitCartesian;
	bool pauseFalg;
	bool stopFalg;
	Vector3d homePosition;
	double softUpperLimitJoint[4];
	double softLowerLimitJoint[4];
	double jointOffset[4];
	double motorAngle[4];
	bool serbo;
	std::string manifactur;
	std::string type;
	int axisNum;
	int cmdCycle;
	bool isGripper;

	//double speedPoint;
	//double speedJointPos;

	/**
	*@brief 手先の関節(関節4)の関節角度設定
	* @param hjp 関節角度
	*/
	void setHandJointPosition(double hjp);
	/**
	*@brief 初期の手先位置設定
	* @param j1 関節角度(関節1)
	* @param j1 関節角度(関節2)
	* @param j1 関節角度(関節3)
	* @param j1 関節角度(関節4)
	*/
	void setStartPos(double j1, double j2, double j3, double j4);
	/**
	*@brief 開始
	*/
	void start();
	/**
	*@brief モーターの角度を取得
	* @return モーターの角度
	*/
	double* getMotorPosition();
	/**
	*@brief 目標関節角速度を計算
	* @param target_theta 目標関節角度
	* @param start_theta 初期関節角度
	* @param end_time 到達時間
	* @param time 現在の時間
	* @param angle 現在の関節角度
	* @return 目標関節角速度
	*/
	double calcVel(double target_theta, double start_theta, double end_time, double time, double angle);

	double MaxSpeedJoint[4], MaxSpeedCartesianTrans, MaxSpeedCartesianRot;
	double MinTime;
};



#endif