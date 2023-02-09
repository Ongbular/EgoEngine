#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <memory>

//--------------------------------------------------------------------------------------
// Aliases of Smart Pointers
//--------------------------------------------------------------------------------------
template <typename T>
using TUniquePtr = std::unique_ptr<T>;

template <typename T, typename... TArgs>
constexpr TUniquePtr<T> MakeUnique(TArgs... args)
{
	return std::make_unique<T>(std::forward<TArgs>(args)...);
}

template <typename T>
using TSharedPtr = std::shared_ptr<T>;

template <typename T, typename... TArgs>
constexpr TSharedPtr<T> MakeShared(TArgs... args)
{
	return std::make_shared<T>(std::forward<TArgs>(args)...);
}

template <typename T>
using TWeakPtr = std::weak_ptr<T>;

template <typename T>
using TSharedFromThis = std::enable_shared_from_this<T>;

//--------------------------------------------------------------------------------------
// Aliases of Containers
//--------------------------------------------------------------------------------------
template <typename T>
using TArray = std::vector<T>;

template <typename T>
using TQueue = std::queue<T>;

template <typename T>
using TStack = std::stack<T>;

template <typename T>
using TSet = std::unordered_set<T>;

template <typename T>
using TMultiSet = std::unordered_multiset<T>;

template <typename TKey, typename TValue>
using TMap = std::unordered_map<TKey, TValue>;

template <typename TKey, typename TValue>
using TMultiMap = std::unordered_multimap<TKey, TValue>;
