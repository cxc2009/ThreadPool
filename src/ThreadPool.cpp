#include "ThreadPool.h"

namespace AThreadPool{

ThreadPool* ThreadPool::thread_pool_ = nullptr;
mutex ThreadPool::threadpool_mutex_;
mutex ThreadPool::idle_mutex_;
mutex ThreadPool::work_mutex_;
mutex ThreadPool::task_mutex_;

const unsigned int kInitThreadCount = 10;//初始线程数
const unsigned int kMaxThreadCount = 1000;//最大线程数
const unsigned int kMaxTaskCount = 10000;//最大任务数

ThreadPool::ThreadPool()
{
		
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::Init()
{
	for (int i = 0; i < kInitThreadCount; i++)
	{
		thread_list_idle_.push_back(make_shared<Thread>());
	}

	//启动任务分发线程
	thread_task_ = make_shared<Thread>(
		[](){
			
		}
		)
}

inline ThreadPool& ThreadPool::GetInstance()
{
	if (thread_pool_ == nullptr)
	{
		lock_guard<mutex> lock(threadpool_mutex_);
		if (thread_pool_ == nullptr)
		{
			thread_pool_ = new ThreadPool;
			thread_pool_->Init();
		}				
	}			
	return *thread_pool_;
}

inline void ThreadPool::DestroyInstance()
{
	if (thread_pool_)
	{
		lock_guard<mutex> lock(threadpool_mutex_);
		delete thread_pool_;
		thread_pool_ = nullptr;
	}
}

inline int ThreadPool::GetAllThreadCout()
{
	return thread_list_idle_.size() + thread_list_work_.size();
}

inline int ThreadPool::GetIdleThreadCout()
{
	return thread_list_idle_.size();
}

inline int ThreadPool::GetWorkThreadCout()
{
	return thread_list_work_.size();
}

inline int ThreadPool::GetCoreThreadCount()
{
	return core_thread_count_;
}

inline bool ThreadPool::SetMaxThreadCount(unsigned int core_thread_count)
{
	if (core_thread_count > kMaxThreadCount)
		return false;
	max_thread_count_ = max_thread_count;
	return true;
}

inline int ThreadPool::GetMaxThreadCount()
{
	return max_thread_count_;
}

inline bool ThreadPool::SetMaxThreadCount(unsigned int max_thread_count)
{
	if (max_thread_count > kMaxThreadCount)
		return false;
	max_thread_count_ = max_thread_count;
	return true;
}

inline int ThreadPool::GetMaxTaskCount()
{
	return max_task_count_;
}

inline bool ThreadPool::SetMaxTaskCount(unsigned int max_task_count)
{
	if (max_task_count > kMaxTaskCount)
		return false;
	max_task_count_ = max_task_count;
	return true;
}

bool ThreadPool::ExcuteTask(shared_ptr<Work> work, AbnormalStrategy abnormal)
{
	if (ExcuteIdleThread(work))
		return true;
	if (PushTask(work))
		return true;
	if (ExcuteAbnormal(work, abnormal))
		return true;
	return false;
}



bool ThreadPool::ExcuteIdleThread(shared_ptr<Work> work)
{
	shared_ptr<Thread> idle_thread;
	{
		lock_guard<mutex> lock(idle_mutex_);
		if (thread_list_idle_.empty())
			return false;
		idle_thread = thread_list_idle_.front();
		thread_list_idle_.pop_front();
	}
	if (!idle_thread)
		return false;
	idle_thread->Start(work);
	return true;
}

bool ThreadPool::PushTask(shared_ptr<Work> work)
{
	if (work->IsAdvanced())
	{

	}
	else
	{

	}
	return true;
}

bool ThreadPool::ExcuteAbnormal(shared_ptr<Work> work, AbnormalStrategy abnormal)
{
	if (abnormal == RETURN_ERROR)
		return false;
	if (!work->Excute())
		return false;
	return true;
}

}