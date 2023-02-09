#pragma once

#ifndef LOGGER_API
#ifdef Logger_EXPORT
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif
#endif
