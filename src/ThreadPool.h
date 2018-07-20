#pragma once
#include <list>
#include <memory>
#include <mutex>
#include "Thread.h"
#include "Work.h"

using std::list;
using std::shared_ptr;
using std::mutex;
using std::lock_guard;
using std::make_shared;

namespace AThreadPool{

/*
һ���ӵ�����ʱ���̳߳��������̣�
1���жϺ����߳����Ƿ����������δ�����򴴽�һ�����߳�ִ�У���������һ���̣�
2���ж���������Ƿ���������δ������������������У�������������һ���̣�
3���ж��Ƿ�ﵽ����߳��������δ�����򴴽�һ�����߳�ִ�У���������һ���̣�
4�������쳣���Դ���

�����쳣������ԣ�
1�����񲻴�����������ֱ�ӱ����أ�
2��ʹ�õ������߳���ִ�и�����
3�����������������һ�����񣬸�Ϊִ�е�ǰ����
*/

	enum AbnormalStrategy{
		RETURN_ERROR = 0,//������
		EXCUTE_DIRECT = 1//ʹ�õ������߳�ִ�и�����
	};

class ThreadPool
{
private:
	ThreadPool();
	~ThreadPool();

public:
	static ThreadPool& GetInstance();
	static void DestroyInstance();

	//��ȡ���߳���
	int GetAllThreadCout();
	//��ȡ�����߳���
	int GetIdleThreadCout();
	//��ȡ�����߳���
	int GetWorkThreadCout();
	//��ȡ�����߳���
	int GetCoreThreadCount();
	//���ú����߳���
	bool SetCoreThreadCount(unsigned int core_thread_count);
	//��ȡ����߳���
	int GetMaxThreadCount();
	//��������߳���
	bool SetMaxThreadCount(unsigned int max_thread_count);
	//��ȡ�������֧�������������
	int GetMaxTaskCount();
	//�����������֧�������������
	bool SetMaxTaskCount(unsigned int max_task_count);

	//��������
	bool ExcuteTask(shared_ptr<Work> work, AbnormalStrategy abnormal = RETURN_ERROR);

private:
	void Init();

	//ֱ��ִ�п����߳�
	bool ExcuteIdleThread(shared_ptr<Work> work);
	//�����������
	bool PushTask(shared_ptr<Work> work);
	//ִ���쳣����
	bool ExcuteAbnormal(shared_ptr<Work> work, AbnormalStrategy abnormal);

private:
	static ThreadPool* thread_pool_;

	unsigned int core_thread_count_;//�̳߳غ����߳���
	unsigned int max_thread_count_;//�̳߳�����߳���
	unsigned int max_task_count_;//�������֧�ֵ������������
	
	static mutex threadpool_mutex_;//�̳߳ض�����
	static mutex idle_mutex_;//�����̶߳�����
	static mutex work_mutex_;//�����̶߳�����
	static mutex task_mutex_;//���������

	list<shared_ptr<Thread>> thread_list_idle_;//�����̶߳���
	list<shared_ptr<Thread>> thread_list_work_;//�����̶߳���
		
	list<shared_ptr<Work>> thread_list_task_;//�������

	shared_ptr<Thread> thread_task_;//����ַ��߳�
};
}


