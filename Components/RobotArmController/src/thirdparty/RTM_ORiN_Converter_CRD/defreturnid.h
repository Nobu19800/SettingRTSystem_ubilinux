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

#define RETURNID_OK RETURNID(ID_RETURNID_OK,"�I�y���[�V�����𐳏�Ɏ󂯕t��.")
#define RETURNID_NG RETURNID(ID_RETURNID_NG,"�I�y���[�V��������.")
#define RETURNID_STATUS_ERR RETURNID(ID_RETURNID_STATUS_ERR,"�I�y���[�V�������󂯕t���\�ȏ�ԂłȂ�.")
#define RETURNID_VALUE_ERR RETURNID(ID_RETURNID_VALUE_ERR,"�������s��.")
#define RETURNID_NOT_SV_ON_ERR RETURNID(ID_RETURNID_NOT_SV_ON_ERR,"�S�Ă̎��̃T�[�{�������Ă��Ȃ�.")
#define RETURNID_NOT_IMPLEMENTED RETURNID(ID_RETURNID_NOT_IMPLEMENTED,"�������̃R�}���h.")

#define M_PI       3.14159265358979323846

#endif//__DEFRETURNID_H__