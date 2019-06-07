#ifndef __CPP_CONCURRENCY_IN_ACTION_STUDY_H__
#define __CPP_CONCURRENCY_IN_ACTION_STUDY_H__
#include <vector>
#include <thread>
#include <algorithm>
#include <numeric>
#include <list>
#include <mutex>
#include <exception>
#include <memory> // For std::shared_ptr<>
#include <stack>

template<typename Iterator, typename T>
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = std::accumulate(first, last, result);
	}
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	unsigned long const length = std::distance(first, last);
	if (!length) // 1
		return init;
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads =
		(length + min_per_thread - 1) / min_per_thread; // 2
	unsigned long const hardware_threads =
		std::thread::hardware_concurrency();
	unsigned long const num_threads = 
		std::min(hardware_threads != 0 ? hardware_threads : 2,
			max_threads);// 3
	unsigned long const block_size = length / num_threads; // 4
	std::vector<T> results(num_threads);
	std::vector<std::thread> threads(num_threads - 1); // 5
	Iterator block_start = first;
	for (unsigned long i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size); // 6
		threads[i] = std::thread( // 7
			accumulate_block<Iterator, T>(),
			block_start, block_end, std::ref(results[i]));
		block_start = block_end; // 8
	}
	accumulate_block<Iterator, T>()(
		block_start, last, results[num_threads - 1]); // 9
	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join)); // 10
	return std::accumulate(results.begin(), results.end(), init); //11
}


std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(some_mutex); // 3
	some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex); // 4
	return
		std::find(some_list.begin(), some_list.end(), value_to_find) !=
		some_list.end();
}


struct empty_stack : std::exception
{
	const char* what() const throw() {
		return "empty stack!";
	};
};
template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m;
public:
	threadsafe_stack()
		: data(std::stack<T>()) {}
	threadsafe_stack(const threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data; // 1 在构造函数体中的执行拷贝
	}
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}
	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack(); // 在调用pop前，检查栈是否 为空
			std::shared_ptr<T> const res(std::make_shared<T>
			(data.top())); // 在修改堆栈前，分配出返回值
		data.pop();
		return res;
	}
	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		value = data.top();
		data.pop();
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};

#endif
 

