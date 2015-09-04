/*!
* @file  LoadRTCs.h
* @brief RTC�ǂݍ��݊֘A�̃N���X�A�֘A
*
*/



#ifndef LOADRTCS_H
#define LOADRTCS_H



#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <coil/DynamicLib.h>
 
typedef void (*RTCInitFunction)(RTC::Manager* pManager);


/**
* @class compParam
*@brief ���I�����N���C�u��������ǂݍ���RTC�̊e�����i�[����N���X
*/

class compParam
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param name RTC��
	* @param filename �t�@�C����
	* @param filepath �f�B���N�g���p�X
	* @param func �������֐�
	* @param compList RTC�I�u�W�F�N�g�̃��X�g
	*/
	compParam(std::string name, std::string filename, std::string filepath, RTCInitFunction func, std::vector<RTC::RtcBase *> compList);
	std::string m_name;
	std::string m_filename;
	std::string m_filepath;
	RTCInitFunction m_func;
	std::vector<RTC::RtcBase *> m_compList;
};

/**
* @class LoadRTCs
*@brief RTC���[�h�֘A�̊֐������N���X
*/
class LoadRTCs
{
 
 public:
  /**
  *@brief �R���X�g���N�^
  * @param manager �}�l�[�W���I�u�W�F�N�g
  */
  LoadRTCs(RTC::Manager* manager);
  /**
  *@brief �f�X�g���N�^
  */
  virtual ~LoadRTCs();

  /**
  *@brief �폜�\��
  */
   void updateCompList();
   
   /**
   *@brief RTC�N���̊֐�
   * @param name RTC��
   * @param filename �t�@�C����
   * @param filepath �f�B���N�g���p�X
   * @return ������True�A���s��False
   */
   bool createComp(const char* name, const char* filename, const char* filepath);

   /**
   *@brief RTC�폜�̊֐�(�����RTC�𕡐��N�����Ă���ꍇ�͈�ԍŌ�ɋN������RTC���I��)
   * @param name RTC��
   * @return ������True�A���s��False
   */
   bool removeComp(const char* name);
   
   /**
   *@brief RTC������RTC�̊e�����擾
   * @param name RTC��
   * @return RTC�̊e���
   */
   compParam *getCompFromName(std::string name);
   /**
   *@brief �t�@�C��������RTC�̏������֐����擾
   * @param filename �t�@�C����
   * @param filepath �f�B���N�g���p�X
   * @return RTC�̏������֐�
   */
   RTCInitFunction getFunc(std::string filename,std::string filepath);
   /**
   *@brief �t�@�C������N������RTC�̃��X�g��ǂݍ���ŊeRTC���N��
   */
   void openFile();

   /**
   *@brief �v���p�e�B����w�肵���L�[�̒l���擾
   * @param prop �v���p�e�B
   * @param key �L�[
   * @param value �l
   */
  template <class T>
    void getProperty(coil::Properties& prop, const char* key, T& value)
    {
    if (prop.findNode(key) != 0)
      {
        T tmp;
        if (coil::stringTo(tmp, prop[key].c_str()))
          {
            value = tmp;
          }
      }
    }


	std::vector<coil::DynamicLib*> dllList;
	std::vector<compParam> compList;
	RTC::Manager* mgr;

private:

};


/**
* @class RTC_FinalizeListener
*@brief RTC�I������RTC�̃��X�g����폜����̃��X�i
*/
class RTC_FinalizeListener
	: public RTC::PostComponentActionListener
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param rtc RTC�I�u�W�F�N�g
	* @param list RTC�̊e���
	*/
	RTC_FinalizeListener(RTC::RtcBase * rtc, compParam *list);
	/**
	*@brief RTC�I������RTC�̃��X�g����폜����
	* @param ec_id ���s�R���e�L�X�g��ID
	* @param list RTC::ReturnCode_t
	*/
	void operator()(RTC::UniqueId ec_id, RTC::ReturnCode_t ret);
	RTC::RtcBase * m_rtc;
	compParam *m_list;
};



#endif // RTCCONTROLSVC_IMPL_H


