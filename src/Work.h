#pragma once

namespace AThreadPool{

class Work
{
public:
	//ִ������
	virtual bool Excute() = 0;
	//�Ƿ�߼����񣬾�������ִ��Ȩ
	virtual bool IsAdvanced() = 0;
	//��ȡ���´�����
	virtual int GetLastError() = 0;
};
}