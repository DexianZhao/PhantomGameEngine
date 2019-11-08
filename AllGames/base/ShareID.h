#ifndef __SHARE_ID_H__
#define	__SHARE_ID_H__

enum{
	MsgID_RequestRun	=	1,//��������
	MsgID_SendFileBegin,//��ʼ����ĳ���ļ�,��������ļ���Ϣ�����·�����������ȡ�
	MsgID_SendFileData,//�����ļ�����
	MsgID_SendFileEnd,//ĳ���ļ����ͽ���
	MsgID_RequestAuth,//��֤��Ȩ�룬��ʱ���ӷ����������Ȩ�룬�����Ȩ��֮��ֱ������
	MsgID_RequestAuthFail,//��ȡ��֤�����
	MsgID_LogMessage,//������־��Ϣ
	MsgID_UpdateFileOK,//�ļ������������
	MsgID_ResetServer,//�ļ������������
    MsgID_DeviceName,
	MsgID_FileListItem,//�ļ����ָ���
	MsgID_FileListOK,
	MsgID_Exit,
};

#define	SVR_PORT	16168

#pragma pack(push, 1)
struct FileTime{
    unsigned int dwLowDateTime;
    unsigned int dwHighDateTime;
};
struct	FileInfo
{
	char		file[128];
	FileTime	w;
	int			length;
	char		bMustUpdate;
};
#pragma pack(pop)


#endif
