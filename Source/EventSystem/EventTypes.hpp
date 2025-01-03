#pragma once
#include <functional>

using EventID        = int32_t;
using FunctionHandle = int32_t;
using Callback       = std::function<void(void*)>;
