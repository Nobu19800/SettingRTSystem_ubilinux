//defreturnid.h
#ifndef __DEFRETURNID_H__
#define __DEFRETURNID_H__


#define ID_RETURNID_OK 0
#define ID_RETURNID_NG -1
#define ID_RETURNID_STATUS_ERR -2
#define ID_RETURNID_VALUE_ERR -3
#define ID_RETURNID_NOT_SV_ON_ERR -4
#define ID_RETURNID_FULL_MOTION_QUEUE_ERR -5
#define ID_RETURNID_NOT_IMPLEMENTED -6


static JARA_ARM::RETURN_ID* SetID(int id,const char* comment)
{
	JARA_ARM::RETURN_ID_var rid;

	 rid=new JARA_ARM::RETURN_ID;
	 rid->id=id; 
	 rid->comment=comment; 
	 return rid._retn();
}
#define RETURNID(id,comment) { return SetID(id,comment);}

#define RETURNID_OK RETURNID(ID_RETURNID_OK,"オペレーションを正常に受け付け.")
#define RETURNID_NG RETURNID(ID_RETURNID_NG,"オペレーション拒否.")
#define RETURNID_STATUS_ERR RETURNID(ID_RETURNID_STATUS_ERR,"オペレーションを受け付け可能な状態でない.")
#define RETURNID_VALUE_ERR RETURNID(ID_RETURNID_VALUE_ERR,"引数が不正.")
#define RETURNID_NOT_SV_ON_ERR RETURNID(ID_RETURNID_NOT_SV_ON_ERR,"全ての軸のサーボが入っていない.")
#define RETURNID_NOT_IMPLEMENTED RETURNID(ID_RETURNID_NOT_IMPLEMENTED,"未実装のコマンド.")

#define M_PI       3.14159265358979323846

#endif//__DEFRETURNID_H__