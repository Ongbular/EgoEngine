#pragma once

#ifndef CORE_API
#ifdef __Core
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif
#endif
