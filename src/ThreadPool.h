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
一、接到任务时，线程池运行流程：
1、判断核心线程数是否已满，如果未满，则创建一个新线程执行，否则，走下一流程；
2、判断任务队列是否已满，若未满，则把任务插入队列中，若满，则走下一流程；
3、判断是否达到最大线程数，如果未满，则创建一个新线程执行，否则，走下一流程；
4、按照异常策略处理。

二、异常处理策略：
1、任务不处理、丢弃掉，直接报错返回；
2、使用调用者线程来执行该任务；
3、丢掉队列里最近的一个任务，改为执行当前任务。
*/

	enum AbnormalStrategy{
		RETURN_ERROR = 0,//报错返回
		EXCUTE_DIRECT = 1//使用调用者线程执行该任务
	};

class ThreadPool
{
private:
	ThreadPool();
	~ThreadPool();

public:
	static ThreadPool& GetInstance();
	static void DestroyInstance();

	//获取总线程数
	int GetAllThreadCout();
	//获取空闲线程数
	int GetIdleThreadCout();
	//获取工作线程数
	int GetWorkThreadCout();
	//获取核心线程数
	int GetCoreThreadCount();
	//设置核心线程数
	bool SetCoreThreadCount(unsigned int core_thread_count);
	//获取最大线程数
	int GetMaxThreadCount();
	//设置最大线程数
	bool SetMaxThreadCount(unsigned int max_thread_count);
	//获取任务队列支持最大任务数量
	int GetMaxTaskCount();
	//设置任务队列支持最大任务数量
	bool SetMaxTaskCount(unsigned int max_task_count);

	//插入任务
	bool ExcuteTask(shared_ptr<Work> work, AbnormalStrategy abnormal = RETURN_ERROR);

private:
	void Init();

	//直接执行空闲线程
	bool ExcuteIdleThread(shared_ptr<Work> work);
	//插入任务队列
	bool PushTask(shared_ptr<Work> work);
	//执行异常处理
	bool ExcuteAbnormal(shared_ptr<Work> work, AbnormalStrategy abnormal);

private:
	static ThreadPool* thread_pool_;

	unsigned int core_thread_count_;//线程池核心线程数
	unsigned int max_thread_count_;//线程池最大线程数
	unsigned int max_task_count_;//任务队列支持的最大任务数量
	
	static mutex threadpool_mutex_;//线程池对象锁
	static mutex idle_mutex_;//空闲线程队列锁
	static mutex work_mutex_;//工作线程队列锁
	static mutex task_mutex_;//任务队列锁

	list<shared_ptr<Thread>> thread_list_idle_;//空闲线程队列
	list<shared_ptr<Thread>> thread_list_work_;//工作线程队列
		
	list<shared_ptr<Work>> thread_list_task_;//任务队列

	shared_ptr<Thread> thread_task_;//任务分发线程
};
}


