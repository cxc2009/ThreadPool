#pragma once

namespace AThreadPool{

class Work
{
public:
	//执行任务
	virtual bool Excute() = 0;
	//是否高级任务，具有优先执行权
	virtual bool IsAdvanced() = 0;
	//获取最新错误码
	virtual int GetLastError() = 0;
};
}