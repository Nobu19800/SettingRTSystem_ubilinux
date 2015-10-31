/*!
* @file  RobotArm.cpp
* @brief サインスマート製4自由度ロボットアーム制御クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "RobotArm.h"

#define ArmLength0 0.05
#define ArmLength1 0.05
#define ArmLength2 0.14
#define ArmLength3 0.152

#define HandLength 0.01
#define FingerLength 0.02

#define ArmMath0 0.1
#define ArmMath1 0.1
#define ArmMath2 0.1
#define ArmMath3 0.1

#define HandMath 0.1
#define FingerMath 0.01



#define ArmWidth 0.01
#define FingerWidth 0.005
#define ArmHeight 0.01
#define FingerHeight 0.005
#define HandRadius 0.016

#define MOTOR_UPPER__LIMIT_0 M_PI*90/180+0.001
#define MOTOR_UPPER__LIMIT_1 M_PI*105/180+0.001
#define MOTOR_UPPER__LIMIT_2 M_PI*90/180+0.001
#define MOTOR_UPPER__LIMIT_3 M_PI/2+0.001

#define MOTOR_LOWER__LIMIT_0 -M_PI*90/180-0.001
#define MOTOR_LOWER__LIMIT_1 -0.001
#define MOTOR_LOWER__LIMIT_2 -0.001
#define MOTOR_LOWER__LIMIT_3 -M_PI/2-0.001


#define MOTOR_OFFSET_0 M_PI*90/180
#define MOTOR_OFFSET_1 M_PI*20/180
#define MOTOR_OFFSET_2 M_PI*105/180
#define MOTOR_OFFSET_3 M_PI/2


//std::ofstream ofs( "test.txt" );

/**
*@brief 手先位置(もしくは関節角度)の目標位置、初期位置、到達時間等を格納するクラスのコンストラクタ
*/
TargetPos::TargetPos()
{
	time = 0;
	
}

/**
*@brief 目標手先位置を設定
* @param t 到達時間(0以下に設定した場合は初期位置と目標位置との距離から自動的に計算)
* @param t_p 手先位置
* @param the 手先姿勢
*/
void TargetPos::setPoint(double t, Vector3d t_p,  double the)
{

	target_pos(0) = t_p(0);
	target_pos(1) = t_p(1);
	target_pos(2) = t_p(2);
	target_theta = the;
	type = Point;

	end_time = t;
}

/**
*@brief 初期手先位置を設定
* @param s_p 初期手先位置
* @param the 初期手先姿勢
* @param maxSpeedCartesianTrans 手先の最大速度
* @param maxSpeedCartesianRot 手先姿勢の最大速度
* @param minTime 到達時間の最小値
*/
void TargetPos::setStartPoint(Vector3d s_p, double the, double maxSpeedCartesianTrans, double maxSpeedCartesianRot, double minTime)
{
	start_pos(0) = s_p(0);
	start_pos(1) = s_p(1);
	start_pos(2) = s_p(2);

	start_theta = the;

	if(end_time <= 0)
	{


		double dx = target_pos(0)-start_pos[0];
		double dy = target_pos(1)-start_pos[1];
		double dz = target_pos(2)-start_pos[2];

		double ST = sqrt(dx*dx+dy*dy+dz*dz);

		end_time = ST/maxSpeedCartesianTrans;

		double dt = target_theta-start_theta;
		dt = sqrt(dt*dt)/maxSpeedCartesianRot;
		if(end_time < dt)
			end_time = dt;

		

		if(end_time < minTime)
			end_time = minTime;
		
		std::cout << end_time << std::endl;
	}
}

/**
*@brief 目標関節角度を設定
* @param t 到達時間(0以下に設定した場合は初期関節角度と目標関節角度との距離から自動的に計算)
* @param t_p 関節角度
*/
void TargetPos::setJointPos(double t, double *t_p)
{
	for(int i=0;i < 4;i++)
	{

		target_joint_pos[i] = t_p[i];
	}
	type = Joint;

	end_time = t;
}

/**
*@brief 目標関節角度を設定
* @param t 到達時間
* @param t_p 関節角度
*/
void TargetPos::setStartJointPos(double *s_p, double *maxSpeedJoint, double minTime)
{
	for(int i=0;i < 4;i++)
	{
		start_joint_pos[i] = s_p[i];

	}

	if(end_time <= 0)
	{
		
		
		for(int i=0;i < 4;i++)
		{
			double tmp = target_joint_pos[i]-start_joint_pos[i];
			tmp = sqrt(tmp*tmp)/maxSpeedJoint[i];
			if(end_time < tmp)
				end_time = tmp;
		}

		

		if(end_time < minTime)
			end_time = minTime;
		
		std::cout << end_time << std::endl;
	}
}

/**
*@brief サインスマート製4自由度ロボットアーム制御クラスのコンストラクタ
*/
RobotArm::RobotArm()
{
	jl = new Vector3d[4];
	pl = new Vector3d[4];
	l[0] = ArmLength0;
	l[1] = ArmLength1;
	l[2] = ArmLength2;
	l[3] = ArmLength3;
	lh = HandLength;
	lf = FingerLength;
	m[0] = ArmMath0;
	m[1] = ArmMath1;
	m[2] = ArmMath2;
	m[3] = ArmMath3;
	mh = HandMath;
	mf = FingerMath;
	wi = ArmWidth;
	wf = FingerWidth;
	hi = ArmHeight;
	hf = FingerHeight;
	rh = HandRadius;
	jl[0](0) = 0;
	jl[0](1) = 0;
	jl[0](2) = 0;
	pl[0](0) = jl[0](0);
	pl[0](1) = jl[0](1);
	pl[0](2) = jl[0](2)+l[0]/2;
	jl[1](0) = pl[0](0);
	jl[1](1) = pl[0](1);
	jl[1](2) = pl[0](2)+l[0]/2;
	pl[1](0) = jl[1](0);
	pl[1](1) = jl[1](1);
	pl[1](2) = jl[1](2)+l[1]/2;
	jl[2](0) = pl[1](0);
	jl[2](1) = pl[1](1);
	jl[2](2) = pl[1](2)+l[1]/2;
	pl[2](0) = jl[2](0);
	pl[2](1) = jl[2](1);
	pl[2](2) = jl[2](2)+l[2]/2;
	jl[3](0) = pl[2](0);
	jl[3](1) = pl[2](1);
	jl[3](2) = pl[2](2)+l[2]/2;
	pl[3](0) = jl[3](0);
	pl[3](1) = jl[3](1)+l[3]/2;
	pl[3](2) = jl[3](2);
	jh(0) = pl[3](0);
	jh(1) = pl[3](1)+l[3]/2;
	jh(2) = pl[3](2);
	ph(0) = jh(0);
	//pyh = jyh+lh/2;
	ph(1) = jh(1);
	ph(2) = jh(2);
	jf(0) = ph(0);
	//jyf = pyh+lh/2;
	jf(1) = ph(1);
	jf(2) = ph(2);
	pf(0) = jf(0);
	pf(1) = jf(1);
	pf(2) = jf(2)-lf/2;
	hw = 0.02;

	setAngle(0, 0, 0, 0);


	dt = 0.01;
	//endTime = -1;
	//time = 0;
	/*targetPoint(0) = 0;
	targetPoint(1) = 0;
	targetPoint(2) = 0;

	startPoint(0) = 0;
	startPoint(1) = 0;
	startPoint(2) = 0;*/

	setOffset(0,0,0,0);

	Kp = 10;
	Kjp = 10;
	
	openGripper();

	maxSpeedCartesian = Vector3d(1000, 1000, 1000);
	maxSpeedJoint[0] = 1000;
	maxSpeedJoint[1] = 1000;
	maxSpeedJoint[2] = 1000;
	maxSpeedJoint[3] = 1000;

	softUpperLimitCartesian = Vector3d(1000, 1000, 1000);
	softLowerLimitCartesian = Vector3d(-1000, -1000, -1000);

	pauseFalg = false;
	stopFalg = false;

	//homePosition = Vector3d(0, 0, 0);
	


	softUpperLimitJoint[0] = MOTOR_UPPER__LIMIT_0;
	softUpperLimitJoint[1] = MOTOR_UPPER__LIMIT_1;
	softUpperLimitJoint[2] = MOTOR_UPPER__LIMIT_2;
	softUpperLimitJoint[3] = MOTOR_UPPER__LIMIT_3;

	softLowerLimitJoint[0] = MOTOR_LOWER__LIMIT_0;
	softLowerLimitJoint[1] = MOTOR_LOWER__LIMIT_1;
	softLowerLimitJoint[2] = MOTOR_LOWER__LIMIT_2;
	softLowerLimitJoint[3] = MOTOR_LOWER__LIMIT_3;

	serbo = true;

	manifactur = "SainSmart";
	type = "DIY 4-Axis Servos Control Palletizing Robot Arm";
	axisNum = 4;
	cmdCycle = 50;
	isGripper = false;

	//speedPoint = 10;
	//speedJointPos = 1;

	MaxSpeedJoint[0] = 2;
	MaxSpeedJoint[1] = 2;
	MaxSpeedJoint[2] = 2;
	MaxSpeedJoint[3] = 2;
	MaxSpeedCartesianTrans = 0.5;
	MaxSpeedCartesianRot = 2;

	MinTime = dt;

	jointOffset[0] = MOTOR_OFFSET_0;
	jointOffset[1] = MOTOR_OFFSET_1;
	jointOffset[2] = MOTOR_OFFSET_2;
	jointOffset[3] = MOTOR_OFFSET_3;
	

}

/**
*@brief ホームポジションに移動
*/
void RobotArm::goHomePosition()
{
	//homePosition = calcKinematics(theta);

	//targetPoint = homePosition;

	//addTargetJointPos(homeTheta, -1);
	setStartPos(homeTheta[0], homeTheta[1], homeTheta[2], homeTheta[3]);
	

	//startPoint = homePosition;
	
}

/**
*@brief ホームポジションの設定
* @param jp ホームポジション
*/
void RobotArm::setHomePosition(double *jp)
{
	for(int i=0;i < 4;i++)
	{
		homeTheta[i] = jp[i];
	}

	//homePosition = calcKinematics(theta);
	//homePosition = calcKinematics(theta);
}

/**
*@brief グリッパーを開く
*/
void RobotArm::openGripper()
{
	gripperPos = 0;
}

/**
*@brief グリッパーを閉じる
*/
void RobotArm::closeGripper()
{
	gripperPos = hw - hf;
}


/**
*@brief 更新
* @param st 刻み幅
*/
void RobotArm::update(double st)
{
	
	if(pauseFalg || stopFalg || !serbo)
		return;
	//std::cout << targetPoint.end_time << "\t" << targetPoint.time << std::endl;
	if(targetPoint.end_time < targetPoint.time)
	{
		if(targetPoint.type == Point)
		{
			Vector3d pos = calcKinematics(theta);

			double dPx = Kp*(targetPoint.target_pos(0)-pos(0));
			double dPy = Kp*(targetPoint.target_pos(1)-pos(1));
			double dPz = Kp*(targetPoint.target_pos(2)-pos(2));

			Vector3d dthe = calcJointVel(Vector3d(dPx, dPy, dPz));

			updatePos(dthe(0), dthe(1), dthe(2), 0);
			theta[3] = targetPoint.target_theta;
			
			
		}
		else
		{
			for(int i=0;i < 4;i++)
			{
				theta[i] = targetPoint.target_joint_pos[i];
			}
			if (!judgeSoftLimitJoint(theta))stop();
		}

		
		setTargetPos();

		

		return;
	}
	else
	{
		if(targetPoint.type == Point)
		{
			double td = calcVel(targetPoint.target_theta, targetPoint.start_theta, targetPoint.end_time, targetPoint.time, theta[3]);

			dt = st;
			MinTime = dt;

			double dx = targetPoint.target_pos(0)-targetPoint.start_pos(0);
			double dy = targetPoint.target_pos(1)-targetPoint.start_pos(1);
			double dz = targetPoint.target_pos(2)-targetPoint.start_pos(2);

			double ST = sqrt(dx*dx+dy*dy+dz*dz);
			if(ST < 0.001)
			{
				updatePos(0, 0, 0, td);
				targetPoint.time += dt;
				return;
			}

			double A = 2*M_PI*ST/(targetPoint.end_time*targetPoint.end_time);

			double s = A*targetPoint.end_time/(2*M_PI)*(targetPoint.time - targetPoint.end_time/(2*M_PI)*sin(2*M_PI/targetPoint.end_time*targetPoint.time));

			double Px = s*dx/ST + targetPoint.start_pos(0);
			double Py = s*dy/ST + targetPoint.start_pos(1);
			double Pz = s*dz/ST + targetPoint.start_pos(2);


			double ds = A*targetPoint.end_time/(2*M_PI)*(1 - cos(2*M_PI/targetPoint.end_time*targetPoint.time));

			Vector3d pos = calcKinematics(theta);

			double dPx = ds*dx/ST + Kp*(Px-pos(0));
			double dPy = ds*dy/ST + Kp*(Py-pos(1));
			double dPz = ds*dz/ST + Kp*(Pz-pos(2));

		
			//ofs << ds << "\t" << s << std::endl;
			//std::cout << pos << std::endl;

			

			Vector3d dthe = calcJointVel(Vector3d(dPx, dPy, dPz));


			
			

			updatePos(dthe(0), dthe(1), dthe(2), td);
		}
		else
		{
			double dthe[4];
			
			for(int i=0;i < 4;i++)
			{
				
				dthe[i] = calcVel(targetPoint.target_joint_pos[i], targetPoint.start_joint_pos[i], targetPoint.end_time, targetPoint.time, theta[i]);


				
			}

			updatePos(dthe[0], dthe[1], dthe[2], dthe[3]);

			
			
		}
		targetPoint.time += dt;
	}
	
}

/**
*@brief 関節角度のホームポジションを設定
* @param o1 関節角速度(関節1)
* @param o2 関節角速度(関節2)
* @param o3 関節角速度(関節3)
* @param o4 関節角速度(関節4)
*/
void RobotArm::setOffset(double o1, double o2, double o3, double o4)
{
	offset[0] = o1;
	offset[1] = o2;
	offset[2] = o3;
	offset[2] = o4;

	setAngle(o1,o2,o3,o4);

	double hp[4] = {o1, o2, o3, o4};
	setHomePosition(hp);
	//goHomePosition();
}

/**
*@brief 目標位置追加
* @param p 目標手先位置
* @param the 目標手先姿勢
* @param T 到達時間
*/
void RobotArm::addTargetPos(Vector3d p, double the, double T)
{
	TargetPos tp;
	tp.setPoint(T, p, the);
	targetPoints.push_back(tp);
}

/**
*@brief 目標関節角度追加
* @param p 目標関節角度
* @param T 到達時間
*/
void RobotArm::addTargetJointPos(double *p, double T)
{
	TargetPos tp;
	tp.setJointPos(T, p);
	targetPoints.push_back(tp);
}

/**
*@brief 目標位置のリストの0番目に初期位置、到達時間を設定
*/
void RobotArm::setTargetPos()
{
	
	if(targetPoints.size() == 0)
	{
		return;
	}
	
	//std::cout << "test" << std::endl;
	
	/*time = 0;
	targetPoint(0) = targetPoints[0].pos(0);
	targetPoint(1) = targetPoints[0].pos(1);
	targetPoint(2) = targetPoints[0].pos(2);*/


	if(targetPoints[0].type == Point)
	{
		Vector3d pos = calcKinematics(theta);
		/*startPoint(0) = pos(0);
		startPoint(1) = pos(1);
		startPoint(2) = pos(2);*/

		targetPoints[0].setStartPoint(pos,theta[3],MaxSpeedCartesianTrans,MaxSpeedCartesianRot,MinTime);
	}

	else if(targetPoints[0].type == Joint)
	{
		targetPoints[0].setStartJointPos(theta, MaxSpeedJoint,MinTime);

		
	}

	targetPoint = targetPoints[0];

	

	targetPoints.erase(targetPoints.begin());

	

	return;
}

/**
*@brief 関節角度を入力
* @param t1 関節角度(関節1)
* @param t2 関節角度(関節2)
* @param t3 関節角度(関節3)
* @param t4 関節角度(関節4)
*/
void RobotArm::setAngle(double t1, double t2, double t3, double t4)
{
	theta[0] = t1;
	theta[1] = t2;
	theta[2] = t3;
	theta[3] = t4;

	if (!judgeSoftLimitJoint(theta))stop();
}

/**
*@brief 手先位置取得
*@param the 関節角度
* @return 手先位置
*/
Vector3d RobotArm::calcKinematics(double *the)
{
	Vector3d A;
	double S1 = sin(the[0]);
	double S2 = sin(the[1]);
	double C1 = cos(the[0]);
	double C2 = cos(the[1]);
	double S23 = sin(the[1]+the[2]);
	double C23 = cos(the[1]+the[2]);

	A(0) = -S1*C2*l[2] - S1*S23*l[3];
	A(1) = C1*C2*l[2] + C1*S23*l[3];
	
	A(2) = l[0] + l[1] + S2*l[2] - C23*l[3];

	return A;
}

/**
*@brief ヤコビ行列取得
*@param the 関節角度
* @return ヤコビ行列
*/
Matrix3d RobotArm::calcJacobian(double *the)
{

	double S1 = sin(the[0]);
	double S2 = sin(the[1]);
	double C1 = cos(the[0]);
	double C2 = cos(the[1]);
	double S23 = sin(the[1]+the[2]);
	double C23 = cos(the[1]+the[2]);


	Matrix3d A;
	A(0,0) = -C1*C2*l[2] - C1*S23*l[3];
	A(0,1) = S1*S2*l[2] - C1*C23*l[3];
	A(0,2) = -S1*C23*l[3];
	A(1,0) = -S1*C2*l[2] - S1*S23*l[3];
	A(1,1) = -C1*S2*l[2] + C1*C23*l[3];
	A(1,2) = C1*C23*l[3];
	A(2,0) = 0;
	A(2,1) = C2*l[2] + S23*l[3];
	A(2,2) = S23*l[3];

	return A;

}

/**
*@brief 手先速度から関節角速度を取得
* @param v 手先速度
* @return 関節角速度
*/
Vector3d RobotArm::calcJointVel(Vector3d v)
{
	Matrix3d J = calcJacobian(theta);
	Matrix3d Jinv = J.inverse();

	Vector3d vf(v(0), v(1), v(2));
	

	Vector3d A = Jinv * vf;

	//std::cout << Jinv << std::endl << std::endl;
	
	return A;

}

/**
*@brief 関節、手先位置がソフトリミット内かを判定する
*@param the 関節角度
*@return 範囲内の場合true
*/
bool RobotArm::judgeSoftLimitJoint(double *the)
{
	for(int i=0;i < 4;i++)
	{
		double mpos = the[i];
		if(i == 2)
			mpos = the[2] + the[1];

		
		
		if(mpos > softUpperLimitJoint[i])
		{
			
			if(i == 2)
				the[2] = softUpperLimitJoint[i] - the[1];
			else
				the[i] = softUpperLimitJoint[i];
			
			return false;
			
		}
		else if(mpos < softLowerLimitJoint[i])
		{
			if(i == 2)
				the[2] = softLowerLimitJoint[i] - the[1];
			else
				the[i] = softLowerLimitJoint[i];
			return false;
			
		}
	}

	Vector3d pos = calcKinematics(the);

	if(!judgeSoftLimitPos(pos))return false;

	
	return true;
}



/**
*@brief 手先位置がソフトリミット内かを判定する
*@param pos 手先位置
*@return 範囲内の場合true
*/
bool RobotArm::judgeSoftLimitPos(Vector3d pos)
{
	

	for(int i=0;i < 3;i++)
	{
		if(pos(i) > softUpperLimitCartesian(i))
		{
			return false;
		}
		else if(pos(i) < softLowerLimitCartesian(i))
		{
			return false;
		}
	}
	return true;
}

/**
*@brief 関節角速度の入力から関節角度を更新
* @param v1 関節角速度(関節1)
* @param v2 関節角速度(関節2)
* @param v3 関節角速度(関節3)
* @param v4 関節角速度(関節4)
*/
void RobotArm::updatePos(double v1, double v2, double v3, double v4)
{

	/*std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;*/

	theta[0] = theta[0] + v1*dt;
	theta[1] = theta[1] + v2*dt;
	theta[2] = theta[2] + v3*dt;
	theta[3] = theta[3] + v4*dt;

	if (!judgeSoftLimitJoint(theta))stop();

	

	
}

/**
*@brief ベースオフセットの設定
* @param bo ベースオフセット
*/
void RobotArm::setBaseOffset(double *bo)
{
	for(int i=0;i < 12;i++)
	{
		baseOffset[i] = bo[i];
	}
	
}

/**
*@brief 手先最大速度の設定
* @param msc 手先最大速度
*/
void RobotArm::setMaxSpeedCartesian(Vector3d msc)
{
	maxSpeedCartesian = msc;
}

/**
*@brief 関節最大角速度の設定
* @param msj 関節最大角速度
*/
void RobotArm::setMaxSpeedJoint(double *msj)
{
	maxSpeedJoint[0] = msj[0];
	maxSpeedJoint[1] = msj[1];
	maxSpeedJoint[2] = msj[2];
	maxSpeedJoint[3] = msj[3];
}

/**
*@brief 手先のソフトリミット値の設定
* @param usl ソフトリミットの最大値
* @param lsl ソフトリミットの最小値
*/
void RobotArm::setSoftLimitCartesian(Vector3d usl, Vector3d lsl)
{
	softUpperLimitCartesian = usl;
	softLowerLimitCartesian = lsl;
}

/**
*@brief 一時停止
*/
void RobotArm::pause()
{
	pauseFalg = true;
}

/**
*@brief 再開
*/
void RobotArm::resume()
{
	pauseFalg = false;
}

/**
*@brief 停止
*/
void RobotArm::stop()
{
	stopFalg = true;
}

/**
*@brief 関節のソフトリミット値の設定
* @param usl ソフトリミットの最大値
* @param lsl ソフトリミットの最小値
*/
void RobotArm::setSoftLimitJoint(double *usl, double *lsl)
{
	softUpperLimitJoint[0] = usl[0];
	softUpperLimitJoint[1] = usl[1];
	softUpperLimitJoint[2] = usl[2];
	softUpperLimitJoint[3] = usl[3];

	softLowerLimitJoint[0] = lsl[0];
	softLowerLimitJoint[1] = lsl[1];
	softLowerLimitJoint[2] = lsl[2];
	softLowerLimitJoint[3] = lsl[3];
}

/**
*@brief サーボをオン、オフにする
* @param state trueでオン、falseでオフ
*/
void RobotArm::setSerbo(bool state)
{
	serbo = state;
}

/**
*@brief 手先の関節(関節4)の関節角度設定
* @param hjp 関節角度
*/
void RobotArm::setHandJointPosition(double hjp)
{
	theta[3] = hjp;
}

/**
*@brief 初期の手先位置設定
* @param j1 関節角度(関節1)
* @param j1 関節角度(関節2)
* @param j1 関節角度(関節3)
* @param j1 関節角度(関節4)
*/
void RobotArm::setStartPos(double j1, double j2, double j3, double j4)
{
	double hp[4] = {j1, j2,j3, j4};
	setAngle(j1, j2,j3, j4);
	setHomePosition(hp);
	homePosition = calcKinematics(theta);
	targetPoint.setJointPos(1, hp);
	targetPoint.setStartJointPos(hp, MaxSpeedJoint,MinTime);
	targetPoint.time = 1000;
	//targetPoint = homePosition;
	//startPoint = homePosition;

	targetPoints.clear();
	//if(targetPoints.size() > 0)
	//	targetPoints.erase(targetPoints.begin());
	//endTime = -1;

	start();
}

/**
*@brief 開始
*/
void RobotArm::start()
{
	stopFalg = false;
}

/**
*@brief 目標関節角速度を計算
* @param target_theta 目標関節角度
* @param start_theta 初期関節角度
* @param end_time 到達時間
* @param time 現在の時間
* @param angle 現在の関節角度
* @return 目標関節角速度
*/
double RobotArm::calcVel(double target_theta, double start_theta, double end_time, double time, double angle)
{
	double d = target_theta - start_theta;
	double A = 2*M_PI*d/(end_time*end_time);
	double s = A*end_time/(2*M_PI)*(time - end_time/(2*M_PI)*sin(2*M_PI/end_time*time));
	double ds = A*end_time/(2*M_PI)*(1 - cos(2*M_PI/end_time*time));
	double the = s + start_theta;
		
	
	return ds + Kjp*(the-angle);

	
}

/**
*@brief モーターの角度を取得
* @return モーターの角度
*/
double* RobotArm::getMotorPosition()
{
	
	motorAngle[0] = theta[0] + jointOffset[0];
	motorAngle[1] = theta[1] + jointOffset[1];
	motorAngle[2] = - theta[2] - theta[1] + jointOffset[2];
	motorAngle[3] = theta[3] + jointOffset[3];

	return motorAngle;
}